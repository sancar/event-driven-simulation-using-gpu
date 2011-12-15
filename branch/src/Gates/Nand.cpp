/*
 * NNand.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#include "Nand.h"

Nand::Nand(int delay,int numberOfGates, int numberOfInputs,string name)
:BaseGate(delay,numberOfGates, numberOfInputs,name){}
bool Nand::operation(bool* inputs){
	bool result = true;
	for(int i = 0 ; i < _numOfInputs ; i++){
		result = result & inputs[i];
	}
	return !result;
}

Nand::~Nand(){
	delete []_outputGates;
		delete []_inputGates;

}