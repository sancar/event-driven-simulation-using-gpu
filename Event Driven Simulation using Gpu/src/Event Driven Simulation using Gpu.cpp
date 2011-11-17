//============================================================================
// Name        : Event.cpp
// Author      : Ervin Domazet - M.Sancar Koyunlu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "InputVector.h"

#ifndef GATES
#define GATES
#include "Gates/BaseGate.h"
#include "Gates/And.h"
#include "Gates/FlipFlop.h"
#include "Gates/Nand.h"
#include "Gates/Nor.h"
#include "Gates/Not.h"
#include "Gates/Or.h"
#include "Gates/Xnor.h"
#include "Gates/Xor.h"
#endif

#include "Input/MapReader.h"

using namespace std;

//TODO for debugging only, can be deleted
void printInput(InputVectorList& myvector){
	vector<InputVector*>::iterator it;

	cout << "input list contains:" << endl;
	for ( it=myvector.begin() ; it != myvector.end(); it++ )
	    cout << (*it)->get_gate() <<" " << (*it)->get_time_unit() << " " << (*it)->get_switches_to() << endl;
}
//TODO for debugging only, can be deleted
void printCircuit(BaseGate* cGate , int index){//prints rest of the circuit starting from given gate

	int n = cGate->getNumberOfGates_Output();
	cout.width (index*5);
	cout << right;
	if(cGate->isDefined()){
		cout << "(" << cGate << "-" << cGate->getSignal()  << ")" << endl;
	}else{
		cout << "(" << cGate << "-" << "undefined"  << ")" << endl;
	}
	index++;
	for(int i = 0 ; i < n ; i++){
		printCircuit((cGate->getOutputGates())[i] ,index );
	}
}
void printCircuit(BaseGate** gates, int inputSize){//prints all circuit
	for(int i = 0 ; i < inputSize ; i++){
		printCircuit(gates[i], 0);
	}
}

int main() {

	MapReader* reader = new MapReader("circuit.xml","input.xml");
	BaseGate** all_gates = new BaseGate* [reader->getNumOfGates()];
	reader->readMap(all_gates);

	//reader->printMap(); //for debugging

	//printCircuit(all_gates,reader->getNumOfInputGates());

	InputVector** inputs = new InputVector* [reader->getNumOfInputs()];
	InputVectorList inputList;

	reader->readInput(inputList, inputs);

	//printInput(inputList); //for debugging

	cout << reader->getGcdDelay() << endl;
	cout << "the end" << endl;
	return 0;
}

