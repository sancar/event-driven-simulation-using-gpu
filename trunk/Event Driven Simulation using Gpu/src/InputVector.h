/*
 * InputVector.h
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#ifndef INPUTVECTOR_H_
#define INPUTVECTOR_H_

struct BaseGate;

struct InputVector {

	//InputVector(int, bool);
	BaseGate *_ptr_gate;
	int _at_time_unit;
	bool _switches_to;
};


#endif /* INPUTVECTOR_H_ */
