/*
 * Xor.h
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#ifndef XOR_H_
#define XOR_H_
#include "BaseGate.h"

class Xor : public BaseGate{
public:
	Xor(int,int,int);
	~Xor();
	bool operation(bool* inputs);


};


#endif /* XOR_H_ */
