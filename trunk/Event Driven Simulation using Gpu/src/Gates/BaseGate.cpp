/*
 * BaseGate.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: msk
 */

#include "BaseGate.h"
#include <iostream>
using namespace std;

BaseGate::BaseGate(int delay,int numberOfGates, int numberOfInputs,string name){
	_name = name;
	_currentNumberOfGates_Output = 0;
	_currentNumberOfGates_Input=0;
	_numberOfGates_Output = numberOfGates;
	_defined = false;
	_full_O = false;
	_full_I=false;
	_numOfInputs=numberOfInputs;
	_defined_nextSignal=false;
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
BaseGate::~BaseGate(){
}
void BaseGate::define_and_set_signal(bool signal){
	_defined=true;
	_currentOutputSignal = signal;
}
void BaseGate::define_and_set_nextSignal(bool signal){
	_defined_nextSignal=true;
	_next_signalvalue = signal;
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
bool BaseGate::isDefined_NewSignal(){
	return _defined_nextSignal;
}
bool BaseGate::getNextSignalValue(){
	return _next_signalvalue;
}
void BaseGate::addGate_Output(BaseGate* newGate){
	if(!_full_O){
		_outputGates[_currentNumberOfGates_Output] = newGate;
		_currentNumberOfGates_Output++;
		newGate->addGate_Input(this);
		if(_currentNumberOfGates_Output == _numberOfGates_Output ){
			_full_O = true;
		}
	}else{
		cerr<< "Error(Output): You are trying add more gates than specified to an Interconnection " << endl;
	}
}
void BaseGate::addGate_Input(BaseGate* newGate){
	if(!_full_I){
		_inputGates[_currentNumberOfGates_Input] = newGate;
		_currentNumberOfGates_Input++;
		if(_currentNumberOfGates_Input == _numOfInputs){
			_full_I = true;
		}
	}else{
		cerr<< "Error(Input): You are trying add more gates than specified to an Interconnection " << endl;
	}
}
// TODO for debugging only, can be deleted
int BaseGate::getNumberOfGates_Output(){
	return _numberOfGates_Output;
}
int BaseGate::getNumberOfGates_Input(){
	return _currentNumberOfGates_Input;
}
// TODO for debugging only, can be deleted
BaseGate** BaseGate::getOutputGates(){
	return _outputGates;
}
BaseGate** BaseGate::getInputGates(){
	return _inputGates;
}
int BaseGate::getDelay(){
	return _delay;
}
string BaseGate::getName(){
	return _name;
}
