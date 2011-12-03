/*
 * BaseGate.h
 *
 *  Created on: Oct 29, 2011
 *      Author: Mustafa Sancar Koyunlu
 */
#ifndef BASEGATE_H_
#define BASEGATE_H_
#include <vector>
#include <string>
using std::vector;
using namespace std;
//typedef vector<BaseGate> event;
class BaseGate{
public:
	BaseGate(int,int,int,string);
    virtual ~BaseGate();
	void define_and_set_signal(bool);
	void define_and_set_nextSignal(bool);
	void setSignal(bool);
	void addGate_Output(BaseGate*);
	void addGate_Input(BaseGate*);
	bool getSignal();
	string getName();
	bool isDefined();
	bool isDefined_NewSignal();
	bool getNextSignalValue();
	virtual bool operation(bool*)=0;
	int getDelay();
    // TODO these two for debugging only, can be deleted
    int getNumberOfGates_Output();
    int getNumberOfGates_Input();

    BaseGate** getOutputGates();
    BaseGate** getInputGates();
protected:
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


#endif /* BASEGATE_H_ */
