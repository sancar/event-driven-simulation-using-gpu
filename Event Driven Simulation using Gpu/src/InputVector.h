/*
 * InputVector.h
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#ifndef INPUTVECTOR_H_
#define INPUTVECTOR_H_

#include "Interconnection.h"
class InputVector {
public:
	InputVector(Interconnection *, int, bool);
	InputVector(int, bool);
	virtual ~InputVector();
	bool get_switches_to();
	int get_time_unit();
	Interconnection* get_interconnection();

private:
	Interconnection *ptr_interconnection;
	int at_time_unit;
	bool switches_to;
};

#endif /* INPUTVECTOR_H_ */
