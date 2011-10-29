/*
 * NotGate.h
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#ifndef NOT_H_
#define NOT_H_
#include "BaseGate.h"

class Not : public BaseGate{
public:
	Not(int);
	~Not();
private:
	bool operation(bool* inputs);
};



#endif /* NOT_H_ */
