/*
 * Not.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#include "Not.h"

Not::Not(int delay){
	_delay = delay;
}
bool Not::operation(bool* inputs){
	return !inputs[0];
}


