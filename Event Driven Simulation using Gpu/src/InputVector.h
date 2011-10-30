/*
 * InputVector.h
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#ifndef INPUTVECTOR_H_
#define INPUTVECTOR_H_

#include "Gates/BaseGate.h"
class InputVector {
public:
	InputVector(BaseGate *, int, bool);
	InputVector(int, bool);
	~InputVector();
	bool get_switches_to();
	int get_time_unit();
	BaseGate* get_gate();

private:
	BaseGate *ptr_gate;
	int at_time_unit;
	bool switches_to;
};

#endif /* INPUTVECTOR_H_ */
