/*
 * MapReader.cpp
 *
 *  Created on: Nov 10, 2011
 *      Author: msk
 */

#include <iostream>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <assert.h>
#include "MapReader.h"
#include "pugixml.hpp"

#ifndef GATES
#define GATES
#include "../Gates/BaseGate.h"
#include "../Gates/And.h"
#include "../Gates/FlipFlop.h"
#include "../Gates/Nand.h"
#include "../Gates/Nor.h"
#include "../Gates/Not.h"
#include "../Gates/Or.h"
#include "../Gates/Xnor.h"
#include "../Gates/Xor.h"
#endif

using namespace std;
using namespace pugi;
//TODO for debugging only, can be deleted
void print_hash(map<string,BaseGate*>* mymap){
	map<string,BaseGate*>::iterator it;
	for ( it=mymap->begin() ; it != mymap->end(); it++ )
	    cout << (*it).first << "=>" << (*it).second << endl;
	cout << endl;
}
/**
 *  Loads the file
 *  checks the format of the file,
 *  counts the number of total gates in circuit, this number can be obtained by calling  int MapReader::getNumOfGates()
 *
 */
MapReader::MapReader(char* circuit_file_name , char* input_file_name){

	xml_parse_result result1 = _doc_circuit.load_file(circuit_file_name);
	xml_parse_result result2 = _doc_input.load_file(input_file_name);

	cout << "Circuit file load result: " << result1.description() << endl;
	cout << "Input file load result: " << result2.description() << endl;

	xml_node gates = _doc_circuit.child("circuit").child("gates");

	int numOfGates = 0;
	this->_max_delay=0;
	//count the number of gates
	for (xml_node gate = gates.first_child(); gate; gate = gate.next_sibling())
	{
		numOfGates++;
	}
	_numOfGates = numOfGates;

	_numOfInputGates = 0;
	_gcd_delay = 0;

	xml_node inputs = _doc_input.child("inputs");

	int numOfInputs = 0;
	//count the number of gates
	for (xml_node input = inputs.first_child(); input; input = input.next_sibling())
	{
		numOfInputs++;
	}
	_numOfInputs = numOfInputs;



}
MapReader::~MapReader(){
	//TODO write the destructor
}
int MapReader::getNumOfGates(){
	return _numOfGates;
}
int MapReader::getMaxDelay(){
	return _max_delay;
}
int MapReader::getNumOfInputGates(){
	return _numOfInputGates;
}
int MapReader::getNumOfInputs(){
	return _numOfInputs;
}
int MapReader::getGcdDelay(){
	return _gcd_delay;
}
int MapReader::gcd(int u,int v){
    if(u == v || u == 0 || v == 0)
        return u|v;
    if(u%2 == 0){ // if u is even
        if(v%2 == 0) // if u and v are even
            return (2*gcd(u/2, v/2));
        else // u is even and v is odd
            return  gcd(u/2, v);
    }
    else if(v%2 == 0) // if u is odd and v is even
        return gcd(u, v/2);
    else{ // both are odd
        if(u > v)
            return gcd((u-v)/2, v);
        else
            return gcd((v-u)/2, u);
    }
}
/**
 * Constructs all circuit from given file
 * fills the "circuit" array , first n gates or inputs of the circuit
 * n can be obtained by calling int getNumOfInputsToCircuit();
 */
void MapReader::readMap(BaseGate** circuit){
	int currentNumOfGates = 0;

	xml_node gates = _doc_circuit.child("circuit").child("gates");
	for (xml_node gate = gates.first_child(); gate; gate = gate.next_sibling())
	{
		int delay = atoi(gate.child_value("delay"));
		//find max delay
        if(_max_delay < delay)
        	_max_delay=delay;

        //find greatest common divisor of delays
        _gcd_delay = gcd(_gcd_delay,delay);

		//count number of outputs
		int numberOfOutputs = 0;
		for(xml_node outGate  = gate.child("outGates").child("name") ; outGate ; outGate = outGate.next_sibling()){
			numberOfOutputs++;
		}

		//count number of inputs
		int numberOfInputs = 0;
		for(xml_node inGate  = gate.child("inGates").child("name") ; inGate ; inGate = inGate.next_sibling()){
			numberOfInputs++;
		}


		//initialize the gates according to its type
		string type = gate.child_value("type");
		if(!type.compare("INPUT")){

			circuit[currentNumOfGates] = new FlipFlop(delay, numberOfOutputs, numberOfInputs);
			_numOfInputGates++;
		}else if(!type.compare("AND")){
			circuit[currentNumOfGates] = new And(delay, numberOfOutputs, numberOfInputs);
		}else if(!type.compare("NAND")){
			circuit[currentNumOfGates] = new Nand(delay, numberOfOutputs, numberOfInputs);
		}else if(!type.compare("OR")){
			circuit[currentNumOfGates] = new Or(delay, numberOfOutputs, numberOfInputs);
		}else if(!type.compare("NOR")){
			circuit[currentNumOfGates] = new Nor(delay, numberOfOutputs, numberOfInputs);
		}else if(!type.compare("XOR")){
			circuit[currentNumOfGates] = new Xor(delay, numberOfOutputs, numberOfInputs);
		}else if(!type.compare("XNOR")){
			circuit[currentNumOfGates] = new Xnor(delay, numberOfOutputs, numberOfInputs);
		}else if(!type.compare("NOT")){
			 circuit[currentNumOfGates] = new Not(delay, numberOfOutputs, numberOfInputs);
		}else if(!type.compare("FLIPFLOP")){
			circuit[currentNumOfGates] = new FlipFlop(delay, numberOfOutputs, numberOfInputs);
		}else{
			cerr << "Error : no matching gate type is found " << endl ;
			assert(0);
		}


		//set value if is defined
		string value = gate.child_value("signal");
		if(!value.compare("undefined")){
			;
		}else if(!value.compare("0")){
			circuit[currentNumOfGates]->define_and_set_signal(0);
		}else if(!value.compare("1")){
			circuit[currentNumOfGates]->define_and_set_signal(1);
		}else{
			cerr << "Error : invalid signal type at gate " << gate.child_value("name") << endl;
			assert(0);
		}

		//save the pointer for later use
		_gate_address[string(gate.child_value("name"))] = circuit[currentNumOfGates];

		currentNumOfGates++;

		if(currentNumOfGates > _numOfGates){
			cout << "Error at readMap function of MapReader.cpp" << endl;
			assert(0);
		}

	}

	//add input and output gates
	for (xml_node gate = gates.first_child(); gate; gate = gate.next_sibling())
	{
		BaseGate* currentGate = _gate_address[string(gate.child_value("name"))];
		for(xml_node outGate  = gate.child("outGates").child("name") ; outGate ; outGate = outGate.next_sibling()){

			BaseGate* outputGate = _gate_address[outGate.child_value()] ;
			//print_hash(&_gate_address);
			currentGate->addGate_Output(outputGate);
		}

	}
}
/*
 * Reads Input from input files whose name given in constructor as input_file_name
 * and construct an InputVectorList
 */
void MapReader::readInput(InputVectorList& inputList,InputVector** inputs){

	xml_node inputs_xml = _doc_input.child("inputs");

	int numOfInputs = 0;
	for (xml_node input = inputs_xml.first_child(); input; input = input.next_sibling()){

		int value = atoi(input.child_value("value"));
		int time  = atoi(input.child_value("time"));

		string name = input.child_value("name");
		//print_hash(&_gate_address);

		inputs[numOfInputs] = new InputVector(_gate_address[name] ,time, (value == 1) );
		//cout << inputs[numOfInputs]->get_gate() << "-" << _gate_address.find(name)->second << endl;

		assert(inputs[numOfInputs]->get_gate() == _gate_address[name]);

		inputList.push_back(inputs[numOfInputs]);

		numOfInputs++;
		if(numOfInputs > _numOfInputs){
			cerr << "there is something wrong in readInput of MapReader" << endl;
			assert(0);
		}
	}

	sortInputs(inputList);

}
// utilized in sortInputs function
bool compareInputs(InputVector* a, InputVector* b){
	return ( b->get_time_unit() < a->get_time_unit() );
}
/*
 * Sorts given InputVectorList in descending order
 */
void MapReader::sortInputs(InputVectorList& inputList){
	sort(inputList.begin() , inputList.end(), compareInputs );
}

/**
 *  human readable output to stdout
 *  TODO for debugging only, can be deleted
 */
void MapReader::printMap(){
	xml_node gates = _doc_circuit.child("circuit").child("gates");
	for (xml_node gate = gates.first_child(); gate; gate = gate.next_sibling())
	{
		cout << "Gate:";
		cout << "name = (" << gate.child_value("name") << ") ";
		cout << "delay = (" << gate.child_value("delay") << " )";
		cout << "signal = (" << gate.child_value("signal") << ") ";
		cout << "name = (" << gate.child_value("type") << ") ";

		cout << "OutGates => " ;

		for(xml_node outGate  = gate.child("outGates").child("name") ; outGate ; outGate = outGate.next_sibling()){
			cout << "( name =" << outGate.child_value() << ")";
		}

		cout << "InGates => " ;

		for(xml_node inGate  = gate.child("inGates").child("name") ; inGate ; inGate = inGate.next_sibling()){
			cout << "( name =" << inGate.child_value() << ")";
		}

		cout << endl;
	}

}
