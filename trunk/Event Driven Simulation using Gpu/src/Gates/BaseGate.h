/*
 * BaseGate.h
 *
 *  Created on: Oct 29, 2011
 *      Author: Mustafa Sancar Koyunlu
 */
#ifndef BASEGATE_H_
#define BASEGATE_H_
#include "../Interconnection.h"

class BaseGate{
public:
	BaseGate();
	BaseGate(int);
	~BaseGate();
protected:
	int _delay;
	//Interconnection* inputConnections;
	int _numOfInputs;
	//Interconnection* outputConnections;
};


#endif /* BASEGATE_H_ */
