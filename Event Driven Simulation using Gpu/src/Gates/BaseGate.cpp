/*
 * BaseGate.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#include "BaseGate.h"
#include <iostream>
using namespace std;

BaseGate::BaseGate(int delay,int numberOfGates, int numberOfInputs){
	_currentNumberOfGates_Output = 0;
	_currentNumberOfGates_Input=0;
	_numberOfGates_Output = numberOfGates;
	_defined = false;
	_full_O = false;
	_full_I=false;
	_numOfInputs=numberOfInputs;
	if(numberOfGates!=0){//eger o ise en son output demektir!
		_outputGates = new BaseGate*[_numberOfGates_Output];
	}
	else
	{
		_full_O=true;
		_outputGates=NULL;
	}
	if(numberOfInputs!=0){//eger 0 ise en bastaki input demektir
		_inputGates=new BaseGate*[_numOfInputs];
	}
	else
	{
		 _full_I=true;
		_inputGates=NULL;
	}
	_delay = delay;
}
void BaseGate::define_and_set_signal(bool signal){
	_defined=true;
	_currentOutputSignal = signal;
}
void BaseGate::setSignal(bool signal){
	_currentOutputSignal = signal;
}
bool BaseGate::getSignal(){
	return _currentOutputSignal;
}

bool BaseGate::isDefined(){
	return _defined;
}
void BaseGate::addGate_Output(BaseGate* newGate){
	if(_full_O){
		_outputGates[_currentNumberOfGates_Output] = newGate;
		_currentNumberOfGates_Output++;
		newGate->addGate_Input(this);
		if(_currentNumberOfGates_Output == _numberOfGates_Output ){
			_full_O = true;
		}
	}else{
		cerr<< "Error: You are trying add more gates than specified to an Interconnection " << endl;
	}
}
void BaseGate::addGate_Input(BaseGate* newGate){
	if(_full_I){
		_outputGates[_currentNumberOfGates_Input] = newGate;
		_currentNumberOfGates_Input++;
		if(_currentNumberOfGates_Input == _numOfInputs){
			_full_I = true;
		}
	}else{
		cerr<< "Error: You are trying add more gates than specified to an Interconnection " << endl;
	}
}
BaseGate::~BaseGate(){
	delete []_outputGates;
	delete []_inputGates;
}
