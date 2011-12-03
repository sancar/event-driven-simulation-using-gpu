/*
 * Nor.h
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#ifndef NOR_H_
#define NOR_H_
#include "BaseGate.h"

class Nor : public BaseGate{
public:
	Nor(int,int,int,string);
	~Nor();

	bool operation(bool* inputs);
};



#endif /* NOR_H_ */
