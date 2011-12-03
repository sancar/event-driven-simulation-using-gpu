/*
 * OrGate.h
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#ifndef OR_H_
#define OR_H_
#include "BaseGate.h"

class Or : public BaseGate{
public:
	Or(int,int,int,string);
	~Or();

	bool operation(bool* inputs);

};



#endif /* OR_H_ */
