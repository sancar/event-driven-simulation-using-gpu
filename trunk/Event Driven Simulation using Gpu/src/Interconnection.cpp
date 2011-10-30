/*
 * InterConnection.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: Mustafa Sancar Koyunlu
 */

#include "Interconnection.h"
#include <iostream>
using namespace std;

Interconnection::Interconnection(int numberOfGates){

	_currentNumberOfGates = 0;
	_numberOfGates = numberOfGates;
	_defined = true;
	_full = false;
	_fanouts = new BaseGate*[_numberOfGates];
}

void Interconnection::setSignal(bool signal){
	_currentSignal = signal;
}

bool Interconnection::getSignal(){
	return _currentSignal;
}

bool Interconnection::isDefined(){
	return _defined;
}

void Interconnection::addGate(BaseGate* newGate){
	if(_full){
		_fanouts[_currentNumberOfGates] = newGate;
		_currentNumberOfGates++;
		if(_currentNumberOfGates == _numberOfGates ){
			_full = true;
		}
	}else{
		cerr<< "Error: You are trying add more gates than specified to an Interconnection " << endl;
	}
}
