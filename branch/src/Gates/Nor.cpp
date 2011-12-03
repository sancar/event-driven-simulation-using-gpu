/*
 * Nor.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#include "Nor.h"
#include "BaseGate.h"
Nor::Nor(int delay_,int numberOfGates_, int numberOfInputs_,string name):BaseGate(delay_,numberOfGates_,numberOfInputs_,name)
{
}
bool Nor::operation(bool* inputs){
	bool result = false;
	for(int i = 0 ; i < _numOfInputs ; i++){
		result = result | inputs[i];
	}
	return !result;
}
Nor::~Nor(){
	delete []_outputGates;
		delete []_inputGates;

}

