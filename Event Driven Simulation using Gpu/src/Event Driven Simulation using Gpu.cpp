//============================================================================
// Name        : Event.cpp
// Author      : Ervin Domazet - M.Sancar Koyunlu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "InputVector.h"

#ifndef GATES
#define GATES
#include "Gates/BaseGate.h"
#endif

#include "Input/MapReader.h"
#include "FutureEventList.h"
#include "FutureEvent.h"

using namespace std;

BaseGate* all_gates;
//function declarations
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
void define_and_set_signal(BaseGate & gate , bool signal){
	gate._defined=true;
	gate._currentOutputSignal = signal;
}
void define_and_set_nextSignal(BaseGate & gate,bool signal){
	gate._defined_nextSignal=true;
	gate._next_signalvalue = signal;
}
void  find_all_affected_gates_and_add_to_FEL(int current_time ,
																			 int max_size,
																			 bool new_value,
																			 FutureEventList &future_event_list,
																			 BaseGate * gate);
void compute_the_rest(int & counter_top,
											FutureEventList &future_event_list,
											int& current_time,
											int& max_size,
											int& time_increments);
//---------------------------------------------------------------------------------------------

//TODO for debugging only, can be deleted
/*
void printInput(InputVectorList& myvector){
	vector<InputVector*>::iterator it;

	cout << "input list contains:" << endl;
	for ( it=myvector.begin() ; it != myvector.end(); it++ )
	    cout << (*it)->_ptr_gate->_name <<" " << (*it)->_at_time_unit << " " << (*it)->_switches_to << endl;
}*/
//TODO for debugging only, can be deleted
void printCircuit(BaseGate* cGate , int index){//prints rest of the circuit starting from given gate

	int n = cGate->_currentNumberOfGates_Output;
	cout.width (index*5);
	cout << right;
	if(cGate->_defined){
		cout << "(" << cGate->_name << "-" << cGate->_currentOutputSignal  << ")" << endl;
	}else{
		cout << "(" << cGate->_name  << "-" << "undefined"  << ")" << endl;
	}
	index++;
	for(int i = 0 ; i < n ; i++){
		printCircuit(&all_gates[cGate->_outputGates[i]] ,index );
	}
}
void printCircuit( int inputSize){//prints all circuit
	for(int i = 0 ; i < inputSize ; i++){
		printCircuit(&all_gates[i], 0);
	}
}
void simulate(int current_output_gate){
				    int no_inputs=all_gates[current_output_gate]._currentNumberOfGates_Input;// get the number of inputs to XX
					bool *inputs=new bool[no_inputs];
					bool current_old_signal=all_gates[current_output_gate]._currentOutputSignal;// get the current signal of the gate XX
					for(int j=0; j<no_inputs; j++){// get all the signals to gate XX
						inputs[j]=all_gates[all_gates[current_output_gate]._inputGates[j]]._currentOutputSignal;
					}
					bool current_new_signal=operation(all_gates[current_output_gate],inputs);
					if(current_new_signal != current_old_signal){// then this gate should be added to FEL
									 all_gates[current_output_gate]._currentOutputSignal=current_new_signal;
					}
}
void simulate_DFS(int k)
{
	for(int i=0; i<all_gates[k]._currentNumberOfGates_Output ;i++){
		simulate(all_gates[k]._outputGates[i]);
		simulate_DFS(all_gates[k]._outputGates[i]);
	}
}
void simulate_all_the_circuit_with_default_values_to_inputs(int no_gates)
{
	int i=0;
	for( i=0;i<no_gates;i++){
		define_and_set_signal(all_gates[i],false);
	}
	for(i=0;i<no_gates;i++){
		simulate_DFS(i);
	}
}
void event_driven_simulation(InputVector *& inputList,
														int number_of_input_gates,
														int max_delay,
														int time_increments,
														int no_gates,
														int no_InputList)
{
	    //TODO normally reader->_gcd_delay should be 1 , according to the current circuit, but it returns 4
		 time_increments=1;  //TODO sancar time incrementi 4 olarak donuyor, oysa 1 olmasi lazim


		 FutureEventList  future_event_list;
		 FutureEventList_Constructor(future_event_list,max_delay,time_increments);

		 int current_time=0;
		 int max_size=future_event_list.size;
		 int counter_top=0;
		 int counter_inputList=0;
	  	 int next_input_time=0;
	  	 if(counter_inputList < no_InputList){
					 InputVector *next=&inputList[counter_inputList];
					 counter_inputList++;
					 FutureEvent f_event;
					 FutureEvent_Constructor(f_event,next->_ptr_gate,next->_switches_to); // construct an event for that vector
					 int  time_unit_input = next->_at_time_unit; //get its time unit
					 current_time=time_unit_input;                     // set it as current time

					 //get the "current_time % max_size"'th  futureEvent vector
					 future_event_list.future_event_list->operator [](current_time % max_size).push_back(f_event);
					 //while consuming all the inputVector List

					 //while(! inputList.empty() && ){
					 while(!(counter_top==max_size && counter_inputList >= no_InputList)){
							 if(counter_inputList < no_InputList){
										 next=&inputList[counter_inputList]; //get the last from the input list
										 counter_inputList++;
										 next_input_time=next->_at_time_unit;//get its time unit of change
										 while(next_input_time==current_time){
											 FutureEvent f_event_new;
											 FutureEvent_Constructor(f_event_new,next->_ptr_gate,next->_switches_to); //construct a new FE
											 future_event_list.future_event_list-> operator[]( next_input_time % max_size).push_back(f_event_new);
											 next=&inputList[counter_inputList];//get the last from the input list
											 counter_inputList++;
											 next_input_time=next->_at_time_unit;//get its time unit of change
										 }
										 FutureEvent f_event_new;
										 FutureEvent_Constructor(f_event_new,next->_ptr_gate,next->_switches_to); //construct a new FE
										 future_event_list.future_event_list-> operator[]( next_input_time % max_size).push_back(f_event_new);//Push it to its place
										 counter_top=0;
										 while(current_time<next_input_time && counter_top<max_size ){//loop until time becomes=next_input_time
															/*
															 * get the vector of Future events, of the "current_time %max_size"th element of FEL
															 * and loop untill all the FE's being processed
															 */
															compute_the_rest(counter_top,future_event_list,current_time,max_size,time_increments);
															cout<<"Time: "<<current_time-1<<endl;
															printCircuit(all_gates,no_gates);
														    cout<<endl;
										 }
										 //not needed maybe, but for being sure!
										 current_time=next_input_time;

							 }
							 else//make one plus loop to see the rest gates
							 {
										 counter_top=0;
										 while(counter_top<max_size ){//loop until time becomes=next_input_time
													 compute_the_rest(counter_top,future_event_list,current_time,max_size,time_increments);
													 cout<<"Time: "<<current_time-1<<endl;
													 printCircuit(all_gates,no_gates);
													 cout<<endl;
										 }
							 }
					 }
	  	 }
}
void compute_the_rest(int & counter_top,
											FutureEventList &future_event_list,
											int& current_time,
											int& max_size,
											int& time_increments)
{
									if( future_event_list.future_event_list->operator [](current_time %max_size).empty()){
											counter_top++;
									}
									else
									{
											counter_top=0;
									}
									//TODO additionally: THIS PART SHOULD BE PARALLELIZED USING CUDA !
									 while(! future_event_list.future_event_list->operator [](current_time %max_size).empty()){
										 	 //burda back()degil de begin() den almasi lazim ki algoritma tam anlamiyla dogru calissin
											 FutureEvent new_event=future_event_list.future_event_list->operator [](current_time %max_size).front();
											 future_event_list.future_event_list->operator [](current_time %max_size).erase(future_event_list.future_event_list->operator [](current_time %max_size).begin());
											 bool new_value=new_event.new_value;
											 // every output gate of this gate is searched, and if needed pushed to the FEL
											 find_all_affected_gates_and_add_to_FEL( current_time , max_size, new_value,future_event_list, new_event.base_gate );
									}
									 current_time=current_time + time_increments;
}
void  find_all_affected_gates_and_add_to_FEL(int current_time ,
																			 int max_size,
																			 bool new_value,
																			 FutureEventList &future_event_list,
																			 BaseGate * gate)
{
	bool old_signal=gate->_currentOutputSignal;
	//if old and new signals are equal than do not consider this !
	if(old_signal!=new_value){
		gate->_currentOutputSignal=new_value; //set the new signal for the gate
		int no_outputs=gate->_currentNumberOfGates_Output;
		int i,j;

		for(i=0;i<no_outputs;i++){//for all the output gates...
			BaseGate* current_output_gate=&all_gates[gate->_outputGates[i]];//take the next output gate, call it XX
			bool current_new_signal;
			if(current_output_gate->_defined){//TODO if the gate is not defined WHAT TO DO?, WHEN &HOW to set it to defined!?
																	    /*
																	     * I think that, initially all the Input gates, should be 0,
																	     * and according to that we should set the initial values
																	     * of all the remainding, nonInput gates
																	     * */
				int no_inputs=current_output_gate->_currentNumberOfGates_Input;// get the number of inputs to XX
				bool *inputs=new bool[no_inputs];
				bool current_old_signal=current_output_gate->_currentOutputSignal;// get the current signal of the gate XX
				for(j=0; j<no_inputs; j++){// get all the signals to gate XX
					inputs[j]=all_gates[current_output_gate->_inputGates[j]]._currentOutputSignal;
				}
				current_new_signal=operation(*current_output_gate,inputs);
				if(current_new_signal != current_old_signal ||
								(current_output_gate->_defined_nextSignal &&
											current_new_signal !=current_output_gate->_next_signalvalue)){// then this gate should be added to FEL

					             define_and_set_nextSignal(*current_output_gate,current_new_signal); //YENI SIGNAL HAKKINDA BILGI
								 FutureEvent f_event_new;
								 FutureEvent_Constructor(f_event_new,current_output_gate, current_new_signal);
								 int next_input_time=current_time + current_output_gate->_delay;// assign the time
								 future_event_list.future_event_list-> operator[]( next_input_time % max_size).push_back(f_event_new);
				}
			}
		}
	}
}


int main() {
	MapReader* reader = new MapReader("circuit.xml","input.xml");
	all_gates = new BaseGate [reader->getNumOfGates()];
	reader->readMap(all_gates);
	InputVector* inputs = new InputVector[reader->getNumOfInputs()];
	reader->readInput(inputs,all_gates);

//	printInput(inputs); //for debugging

	//timeval start, finish;
	//double elapsedTime;
	//--------------------------- START

	//gettimeofday(&start, NULL);

	simulate_all_the_circuit_with_default_values_to_inputs(reader->getNumOfGates());

	//TODO inputList yerine inputs g�nderilecek, ve inputs size'� g�nderilecek(reader->getNumOfInputs())

	event_driven_simulation(inputs , reader->getNumOfInputGates(), reader->getMaxDelay(), reader->getGcdDelay(),reader->getNumOfGates(),reader->getNumOfInputs());
    //gettimeofday(&finish, NULL);
    //----------------------------FINISH
	/*
    elapsedTime = (finish.tv_sec - start.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (finish.tv_usec - start.tv_usec) ;   // us to ms
    cout << elapsedTime << " ms.\n";*/
    //printCircuit(all_gates,reader->getNumOfGates());
	return 0;
}
