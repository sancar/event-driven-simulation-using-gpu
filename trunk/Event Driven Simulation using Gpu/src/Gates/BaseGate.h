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
void addGate_Input(BaseGate *gate,BaseGate& newGate);
void BaseGate_Constructor(BaseGate & gate,int delay,int numberOfGates, int numberOfInputs,string name,string type){
	gate._type=type;
	gate._name = name;
	gate._currentNumberOfGates_Output = 0;
	gate._currentNumberOfGates_Input=0;
	gate._numberOfGates_Output = numberOfGates;
	gate._defined = false;
	gate._full_O = false;
	gate._full_I=false;
	gate._numOfInputs=numberOfInputs;
	gate._defined_nextSignal=false;
	if(numberOfGates!=0){//eger o ise en son output demektir!
		gate._outputGates = new BaseGate*[gate._numberOfGates_Output];
	}
	else
	{
		gate._full_O=true;
		gate._outputGates=NULL;
	}
	if(numberOfInputs!=0){//eger 0 ise en bastaki input demektir
		gate._inputGates=new BaseGate*[gate._numOfInputs];
	}
	else
	{
		 gate._full_I=true;
		 gate._inputGates=NULL;
	}
	gate._delay = delay;
}
void define_and_set_signal(BaseGate & gate , bool signal){
	gate._defined=true;
	gate._currentOutputSignal = signal;
}
void define_and_set_nextSignal(BaseGate & gate,bool signal){
	gate._defined_nextSignal=true;
	gate._next_signalvalue = signal;
}

void addGate_Output(BaseGate & gate, BaseGate* newGate){
	if(!gate._full_O){
		gate._outputGates[gate._currentNumberOfGates_Output] = newGate;
		gate._currentNumberOfGates_Output++;
		addGate_Input(newGate,gate);
		if(gate._currentNumberOfGates_Output == gate._numberOfGates_Output ){
			gate._full_O = true;
		}
	}else{
		cerr<< "Error(Output): You are trying add more gates than specified to an Interconnection " << endl;
	}
}
void addGate_Input(BaseGate *gate,BaseGate& newGate){
	if(!gate->_full_I){
		gate->_inputGates[gate->_currentNumberOfGates_Input] = newGate;
		gate->_currentNumberOfGates_Input++;
		if(gate->_currentNumberOfGates_Input == gate->_numOfInputs){
			gate->_full_I = true;
		}
	}else{
		cerr<< "Error(Input): You are trying add more gates than specified to an Interconnection " << endl;
	}
}

bool operation(BaseGate & gate, bool* inputs){
				if(!gate._type.compare("INPUT")){
					  return inputs[0];
				}else if(!gate._type.compare("AND")){
						bool result = true;
						for(int i = 0 ; i < gate._numOfInputs ; i++){
							result = result & inputs[i];
						}
						return result;
				}else if(!gate._type.compare("NAND")){
					bool result = true;
						for(int i = 0 ; i < gate._numOfInputs ; i++){
							result = result & inputs[i];
						}
						return !result;
				}else if(!gate._type.compare("OR")){
						bool result = false;
						for(int i = 0 ; i < gate._numOfInputs ; i++){
							result = result || inputs[i];
						}
						return result;
				}else if(!gate._type.compare("NOR")){
					bool result = false;
						for(int i = 0 ; i < gate._numOfInputs ; i++){
							result = result | inputs[i];
						}
						return !result;
				}else if(!gate._type.compare("XOR")){
						bool result = false;
						for(int i = 0 ;  i < gate._numOfInputs ; i++){
							result = result ^ inputs[i];
						}
						return result;
				}else if(!gate._type.compare("XNOR")){
						bool result = false;
						for(int i = 0 ;  i < gate._numOfInputs ; i++){
							result = result ^ inputs[i];
						}
						return !result;
				}else if(!gate._type.compare("NOT")){
					return !inputs[0];
				}else if(!gate._type.compare("FLIPFLOP")){
					return inputs[0];
				}
				return true;
}
