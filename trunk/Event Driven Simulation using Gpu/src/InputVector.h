/*
 * InputVector.h
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#ifndef INPUTVECTOR_H_
#define INPUTVECTOR_H_

#include "Gates/BaseGate.h"
struct InputVector {

	//InputVector(int, bool);
	BaseGate *ptr_gate;
	int at_time_unit;
	bool switches_to;
};
void InputVector_Constructor(InputVector& iv  , BaseGate* gate, int time, bool vale){
	iv.ptr_gate = gate;
	iv.switches_to = value;
	iv.at_time_unit = time;
}

#endif /* INPUTVECTOR_H_ */
