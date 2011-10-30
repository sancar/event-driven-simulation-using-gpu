/*
 * FlipFlop.h
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#ifndef FLIPFLOP_H_
#define FLIPFLOP_H_
#include "BaseGate.h"

class FlipFlop : public BaseGate{
public:
	FlipFlop(int,int,int);
	~FlipFlop();

	bool operation(bool* inputs);
};

#endif /* FLIPFLOP_H_ */
