/*
 * InputVector.cpp
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */
#include "Gates/BaseGate.h"
#include "InputVector.h"
/*interconnection * ptr,*/
InputVector::InputVector(BaseGate * ptr, int time, bool value) {
	this->ptr_gate=ptr;
	this->switches_to = value;
	this->at_time_unit = time;
}
//deney amacli
InputVector::InputVector(int time, bool value) {
	this->switches_to = value;
	this->at_time_unit = time;
}
InputVector::~InputVector() {
	//delete this->ptr_interconnection;
	// TODO Auto-generated destructor stub
}
bool InputVector::get_switches_to() {
	return this->switches_to;
}
int InputVector::get_time_unit() {
	return this->at_time_unit;
}
BaseGate* InputVector::get_gate() {
	return this->ptr_gate;
}
