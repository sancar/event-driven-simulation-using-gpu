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
	And(int);
	~And();
private:
	bool operation(bool* inputs);

};


#endif /* AND_H_ */
