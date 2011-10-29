/*
 * Nor.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#include "Nor.h"

Nor::Nor(int delay){
	_delay = delay;
}
bool Nor::operation(bool* inputs){
	bool result = false;
	for(int i = 0 ; i < _numOfInputs ; i++){
		result = result | inputs[i];
	}
	return !result;
}


