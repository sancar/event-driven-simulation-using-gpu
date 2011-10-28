/*
 * InputVector.h
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#ifndef INPUTVECTOR_H_
#define INPUTVECTOR_H_

class interconnection;

class InputVector {
public:
	InputVector(interconnection *, int, bool);
	InputVector(int, bool);
	virtual ~InputVector();
	bool get_switches_to();
	int get_time_unit();
	interconnection* get_interconnection();

private:
	interconnection *ptr_interconnection;
	int at_time_unit;
	bool switches_to;
};

#endif /* INPUTVECTOR_H_ */
