/*
 * AndGate.h
 *
 *  Created on: Oct 29, 2011
 *      Author: Mustafa Sancar Koyunlu
 */

#ifndef AND_H_
#define AND_H_
#include "BaseGate.h"

class And : public BaseGate{
public:
	//BaseGate(int delay,int numberOfGates, int numberOfInputs)
	And(int,int,int,string);
	bool operation(bool* inputs);
   ~And();
};


#endif /* AND_H_ */
