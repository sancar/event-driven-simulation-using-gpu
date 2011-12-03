/*
 * And.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#include "And.h"

And::And(int delay,int numberOfGates, int numberOfInputs,string name)
:BaseGate(delay,numberOfGates, numberOfInputs,name)
{}
bool And::operation(bool* inputs){
	bool result = true;
	for(int i = 0 ; i < _numOfInputs ; i++){
		result = result & inputs[i];
	}
	return result;
}
And::~And(){
	delete [] _inputGates;
	delete [] _outputGates;
}
