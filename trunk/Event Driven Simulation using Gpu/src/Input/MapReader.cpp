/*
 * MapReader.cpp
 *
 *  Created on: Nov 10, 2011
 *      Author: msk
 */

#include <iostream>
#include <map>
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
MapReader::MapReader(char* file_name){
	// TODO decide on what will be returned or saved. First idea => an array of input gates and size of array
	// TODO map maybe serialized for efficiency
	xml_parse_result result = _doc.load_file(file_name);

	cout << "Load result: " << result.description() << endl;

	xml_node gates = _doc.child("circuit").child("gates");

	int numOfGates = 0;
	//count the number of gates
	for (xml_node gate = gates.first_child(); gate; gate = gate.next_sibling())
	{
		numOfGates++;
	}
	_numOfGates = numOfGates;
	_numOfInputsToCircuit = 0; //TODO (_numOfInputsToCircuit) not sure if this is necessary, can be deleted later
}
MapReader::~MapReader(){
	//TODO write the destructor
}
int MapReader::getNumOfGates(){
	return _numOfGates;
}
int MapReader::getNumOfInputsToCircuit(){
	return _numOfInputsToCircuit;
}
/**
 * Constructs all circuit from given file
 * fills the "circuit" array , first n gates or inputs of the circuit
 * n can be obtained by calling int getNumOfInputsToCircuit();
 */
void MapReader::readMap(BaseGate** circuit){
	int currentNumOfGates = 0;
	map<string,BaseGate*> gate_address;

	xml_node gates = _doc.child("circuit").child("gates");
	for (xml_node gate = gates.first_child(); gate; gate = gate.next_sibling())
	{
		int delay = atoi(gate.child_value("delay"));

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
			// TODO input gate is saved as FlipFlop ?!?!?
			circuit[currentNumOfGates] = new FlipFlop(delay, numberOfOutputs, numberOfInputs);
			_numOfInputsToCircuit++; //TODO (_numOfInputsToCircuit) not sure this is necessary, can be deleted later
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
		gate_address[string(gate.child_value("name"))] = circuit[currentNumOfGates];

		currentNumOfGates++;

		if(currentNumOfGates > _numOfGates){
			cout << "Error at readMap function of MapReader.cpp" << endl;
			assert(0);
		}

	}

	//add input and output gates
	for (xml_node gate = gates.first_child(); gate; gate = gate.next_sibling())
	{
		BaseGate* currentGate = gate_address[string(gate.child_value("name"))];
		for(xml_node outGate  = gate.child("outGates").child("name") ; outGate ; outGate = outGate.next_sibling()){

			BaseGate* outputGate = gate_address[outGate.child_value()] ;
			//print_hash(&gate_address);
			currentGate->addGate_Output(outputGate);
		}
		// TODO adding input gates to currentGate is done in addGate_Output() currently, decide on where to do ?!?!?
		// if it stays like this, inputGates in xml file are redundant. Otherwise uncomment the following lines

		//for(xml_node inGate  = gate.child("s").child("name") ; inGate ; inGate = inGate.next_sibling()){
			//BaseGate* inputGate =  gate_address[inGate.child_value()];
			//currentGate->addGate_Input(inputGate);
		//}
	}
}
/**
 *  human readable output to stdout
 *  TODO for debugging only, can be deleted
 */
void MapReader::printMap(){
	xml_node gates = _doc.child("circuit").child("gates");
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
