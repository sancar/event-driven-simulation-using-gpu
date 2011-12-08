/*
 * BaseGate.h
 *
 *  Created on: Oct 29, 2011
 *      Author: Mustafa Sancar Koyunlu
 */
#ifndef BASEGATE_H_
#define BASEGATE_H_
#include <string>
using namespace std;

struct BaseGate{
    string _type;
    string _name;
	int _delay;
	bool _currentOutputSignal;
	bool _defined;
	bool _full_I,_full_O;
	int _numberOfGates_Output;
	int _currentNumberOfGates_Output;
	int _numOfInputs;
	int _currentNumberOfGates_Input;
	int _defined_nextSignal;//yeni ekledim
	bool _next_signalvalue;
	BaseGate** _inputGates;
	BaseGate** _outputGates;
};


#endif
