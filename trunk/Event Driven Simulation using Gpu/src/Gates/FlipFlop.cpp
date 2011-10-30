/*
 * FlipFlop.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#include "FlipFlop.h"

FlipFlop::FlipFlop(int delay,int numberOfGates, int numberOfInputs)
:BaseGate(delay,numberOfGates, numberOfInputs){}
bool FlipFlop::operation(bool* inputs){
	return inputs[0];
}
FlipFlop::~FlipFlop(){}

