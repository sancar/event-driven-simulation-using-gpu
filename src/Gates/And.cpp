/*
 * And.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#include "And.h"

And::And(int delay){
	_delay = delay;
}
bool And::operation(bool* inputs){
	bool result = true;
	for(int i = 0 ; i < _numOfInputs ; i++){
		result = result & inputs[i];
	}
	return result;
}
