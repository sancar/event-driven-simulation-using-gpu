/*
 * FutureEvent.cpp
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#include "FutureEvent.h"


FutureEvent::FutureEvent(BaseGate* gate, bool event) {
	this->base_gate = gate;
	this->new_value = event;

	// TODO Auto-generated constructor stub
 }
BaseGate* FutureEvent::getBaseGate(){
	return this->base_gate;
}
bool FutureEvent::getNewValue(){
	return this->new_value;
}
FutureEvent::~FutureEvent() {
	// TODO Auto-generated destructor stub
}

