/*
 * Not.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#include "Not.h"

Not::Not(int delay,int numberOfGates, int numberOfInputs):BaseGate(delay,numberOfGates,numberOfInputs)
{
}
bool Not::operation(bool* inputs){
	return !inputs[0];
}
Not::~Not(){

	delete []_outputGates;
		delete []_inputGates;
}
