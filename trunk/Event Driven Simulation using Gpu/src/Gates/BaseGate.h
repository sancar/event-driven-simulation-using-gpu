/*
 * BaseGate.h
 *
 *  Created on: Oct 29, 2011
 *      Author: Mustafa Sancar Koyunlu
 */
#ifndef BASEGATE_H_
#define BASEGATE_H_
#include <vector>
using std::vector;

//typedef vector<BaseGate> event;
class BaseGate{
public:
	BaseGate(int,int,int);
    virtual ~BaseGate();
	void define_and_set_signal(bool);
	void setSignal(bool);
	bool getSignal();
	bool isDefined();
	void addGate_Output(BaseGate*);
	void addGate_Input(BaseGate*);
    virtual bool operation(bool*)=0;

protected:
	int _delay;
	bool _currentOutputSignal;
	bool _defined;
	bool _full_I,_full_O;
	int _numberOfGates_Output;
	int _currentNumberOfGates_Output;
	int _numOfInputs;
	int _currentNumberOfGates_Input;
	BaseGate** _inputGates;
	BaseGate** _outputGates;
};


#endif /* BASEGATE_H_ */
