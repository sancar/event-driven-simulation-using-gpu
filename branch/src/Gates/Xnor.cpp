/*
 * Xnor.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#include "Xnor.h"

Xnor::Xnor(int delay,int numberOfGates, int numberOfInputs,string name):BaseGate(delay,numberOfGates,numberOfInputs,name)
{
}
bool Xnor::operation(bool* inputs){
	bool result = false;
	for(int i = 0 ;  i < _numOfInputs ; i++){
		result = result ^ inputs[i];
	}
	return !result;
}
Xnor::~Xnor(){
	delete []_outputGates;
		delete []_inputGates;
}
