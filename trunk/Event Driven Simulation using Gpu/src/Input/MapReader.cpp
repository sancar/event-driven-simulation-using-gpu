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

enum { INPUT_, AND, NAND, OR, NOR, XOR, XNOR, NOT, FLIPFLOP};
struct BaseGate;
bool operation(BaseGate & gate, bool* inputs);
void addGate_Output(BaseGate & gate, BaseGate* newGate);
void define_and_set_nextSignal(BaseGate & gate,bool signal);
void define_and_set_signal(BaseGate & gate , bool signal);
void addGate_Input(BaseGate *gate,BaseGate& newGate);
void BaseGate_Constructor(BaseGate & gate,int delay,int numberOfGates, int numberOfInputs,string name,string type);

void BaseGate_Constructor(BaseGate & gate,int delay,int numberOfGates, int numberOfInputs,string name,string type,int index){
	gate._index=index;
	
	if(!type.compare("INPUT")){
		gate._type = INPUT_;
    }else if(!type.compare("AND")){
		gate._type = AND;
    }else if(!type.compare("NAND")){
		gate._type = NAND;
    }else if(!type.compare("OR")){
		gate._type = OR;
    }else if(!type.compare("NOR")){
		gate._type = NOR;
    }else if(!type.compare("XOR")){
		gate._type = XOR;
    }else if(!type.compare("XNOR")){
		gate._type = XNOR;
    }else if(!type.compare("NOT")){
		gate._type = NOT;
    }else if(!type.compare("FLIPFLOP")){
		gate._type = FLIPFLOP;
    }

	gate._name = name;
	gate._currentNumberOfGates_Output = 0;
	gate._currentNumberOfGates_Input=0;
	gate._numberOfGates_Output = numberOfGates;
	gate._defined = false;
	gate._full_O = false;
	gate._full_I=false;
	gate._numOfInputs=numberOfInputs;
	gate._defined_nextSignal=false;
	if(numberOfGates!=0){//eger o ise en son output demektir!
		gate._outputGates = new int[gate._numberOfGates_Output];
	}
	else
	{
		gate._full_O=true;
		gate._outputGates=NULL;
	}
	if(numberOfInputs!=0){//eger 0 ise en bastaki input demektir
		gate._inputGates=new int[gate._numOfInputs];
	}
	else
	{
		 gate._full_I=true;
		 gate._inputGates=NULL;
	}
	gate._delay = delay;
}
void InputVector_Constructor(InputVector& iv  , int gate, int time, bool value){
	iv._ptr_gate = gate;
	iv._switches_to = value;
	iv._at_time_unit = time;
}


void addGate_Input(BaseGate *gate,int newGate){
	if(!gate->_full_I){
		gate->_inputGates[gate->_currentNumberOfGates_Input] = newGate;
		gate->_currentNumberOfGates_Input++;
		if(gate->_currentNumberOfGates_Input == gate->_numOfInputs){
			gate->_full_I = true;
		}
	}else{
		cerr<< "Error(Input): You are trying add more gates than specified to an Interconnection " << endl;
	}
}
void addGate_Output(BaseGate & gate, int newGate,BaseGate*& circuit){
	if(!gate._full_O){
		gate._outputGates[gate._currentNumberOfGates_Output] = newGate;
		gate._currentNumberOfGates_Output++;
		addGate_Input(&circuit[newGate],gate._index);
		if(gate._currentNumberOfGates_Output == gate._numberOfGates_Output ){
			gate._full_O = true;
		}
	}else{
		cerr<< "Error(Output): You are trying add more gates than specified to an Interconnection " << endl;
	}
}

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
void MapReader::readMap(BaseGate*& circuit){
	int currentNumOfGates = 0;

	xml_node gates = _doc_circuit.child("circuit").child("gates");
	for (xml_node gate = gates.first_child(); gate; gate = gate.next_sibling())
	{
		int delay = atoi(gate.child_value("delay"));
		string name = gate.child_value("name");
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
			_numOfInputGates++;
		}
//TODO add a type field to the parameters+  change to new BaseGate_Constructor(..)
		BaseGate_Constructor(circuit[currentNumOfGates],delay,numberOfOutputs, numberOfInputs, name,type,currentNumOfGates);




		//set value if is defined
		string value = gate.child_value("signal");
		if(!value.compare("undefined")){
			;
		}else if(!value.compare("0")){
			define_and_set_signal(circuit[currentNumOfGates],0);
		}else if(!value.compare("1")){
			define_and_set_signal(circuit[currentNumOfGates],1);
		}else{
			cerr << "Error : invalid signal type at gate " << gate.child_value("name") << endl;
			assert(0);
		}

		//save the pointer for later use
		_gate_address[string(gate.child_value("name"))] = currentNumOfGates;

		currentNumOfGates++;

		if(currentNumOfGates > _numOfGates){
			cout << "Error at readMap function of MapReader.cpp" << endl;
			assert(0);
		}

	}

	//add input and output gates
	for (xml_node gate = gates.first_child(); gate; gate = gate.next_sibling())
	{
		BaseGate* currentGate =&circuit[_gate_address[string(gate.child_value("name"))]];
		for(xml_node outGate  = gate.child("outGates").child("name") ; outGate ; outGate = outGate.next_sibling()){

			BaseGate* outputGate =&circuit[ _gate_address[outGate.child_value()] ];
			//print_hash(&_gate_address);
			addGate_Output(*currentGate,outputGate->_index,circuit);
		}

	}
}
/*
 * Reads Input from input files whose name given in constructor as input_file_name
 * and construct an InputVectorList
 */
void MapReader::readInput(InputVector*& inputs,BaseGate*& circuit){

	xml_node inputs_xml = _doc_input.child("inputs");

	int numOfInputs = 0;
	for (xml_node input = inputs_xml.first_child(); input; input = input.next_sibling()){

		int value = atoi(input.child_value("value"));
		int time  = atoi(input.child_value("time"));
		_gcd_delay = gcd(_gcd_delay,time % _max_delay);
		string name = input.child_value("name");
		//print_hash(&_gate_address);

		InputVector_Constructor(inputs[numOfInputs],_gate_address[name] ,time, (value == 1) );
		//cout << inputs[numOfInputs]->get_gate() << "-" << _gate_address.find(name)->second << endl;

		//assert(inputs[numOfInputs]._ptr_gate == _gate_address[name]);

		numOfInputs++;
		if(numOfInputs > _numOfInputs){
			cerr << "there is something wrong in readInput of MapReader" << endl;
			assert(0);
		}
	}

	sortInputs(inputs);

}
// utilized in sortInputs function
int compareInputs(const void* a, const void* b){
	if ( ((InputVector*)b)->_at_time_unit <((InputVector*)a)->_at_time_unit )
		return 1;
	else if( ((InputVector*)b)->_at_time_unit  > ((InputVector*)a)->_at_time_unit)
		return -1;
	else
		return 0 ;

}
/*
 * Sorts given InputVectorList in descending order
 */
void MapReader::sortInputs(InputVector*& inputList){
	qsort(inputList, (unsigned long int)_numOfInputs, (unsigned long int) sizeof(InputVector),  compareInputs );
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
