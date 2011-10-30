/*
 * Xnor.h
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#ifndef XNOR_H_
#define XNOR_H_
#include "BaseGate.h"

class Xnor : public BaseGate{
public:
	Xnor(int,int,int);
	~Xnor();

	bool operation(bool* inputs);

};


#endif /* XNOR_H_ */
