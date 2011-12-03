/*
 * FlipFlop.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#include "FlipFlop.h"

FlipFlop::FlipFlop(int delay,int numberOfGates, int numberOfInputs,string name)
:BaseGate(delay,numberOfGates, numberOfInputs, name){}
bool FlipFlop::operation(bool* inputs){
	return inputs[0];
}
FlipFlop::~FlipFlop(){
	delete []_outputGates;
	delete []_inputGates;
}

