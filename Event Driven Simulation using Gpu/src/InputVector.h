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
	BaseGate *_ptr_gate;
	int _at_time_unit;
	bool _switches_to;
};
void InputVector_Constructor(InputVector& iv  , BaseGate* gate, int time, bool value){
	iv.ptr_gate = gate;
	iv.switches_to = value;
	iv.at_time_unit = time;
}

#endif /* INPUTVECTOR_H_ */
