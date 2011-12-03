/*
 * NandGate.h
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#ifndef NAND_H_
#define NAND_H_
#include "BaseGate.h"
class Nand : public BaseGate{
public:
	Nand(int,int,int,string);
	 ~Nand();

	bool operation(bool* inputs);
};



#endif /* NANDGATE_H_ */
