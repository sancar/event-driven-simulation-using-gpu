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
    And ervin(4,3,2);
    Or harun(2,2,2);
    ervin.addGate_Output(&harun);

    //BaseGate *deneme=&ervin;
	//InputVector *a = new InputVector(deneme,15, true);
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	MapReader* reader = new MapReader("circuit.xml");
	BaseGate** all_gates = new BaseGate* [reader->getNumOfGates()];
	//reader->printMap(); for debugging
	reader->readMap(all_gates);
	//reader->printMap();
	/*cout<<reader->getNumOfInputsToCircuit()<<endl;
	cout<<all_gates[1]->getNumberOfGates_Output()<<endl;
	cout<<(all_gates[2]->getInputGates())[0]->getOutputGates()[0]<<endl;
	cout<<(all_gates[2]->getInputGates())[1]->getOutputGates()[0]<<endl;*/
	printCircuit(all_gates,reader->getNumOfInputsToCircuit());
	cout << "the end" << endl;
	return 0;
}

