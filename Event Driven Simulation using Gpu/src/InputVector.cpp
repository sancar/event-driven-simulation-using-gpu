/*
 * InputVector.cpp
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */
#include "Interconnection.h"
#include "InputVector.h"
/*interconnection * ptr,*/
InputVector::InputVector(Interconnection * ptr, int time, bool value) {
	this->ptr_interconnection = ptr;
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
Interconnection* InputVector::get_interconnection() {
	return this->ptr_interconnection;
}
