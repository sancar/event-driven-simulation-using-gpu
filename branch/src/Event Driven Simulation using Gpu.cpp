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
#include "Gates/And.h"
#include "Gates/FlipFlop.h"
#include "Gates/Nand.h"
#include "Gates/Nor.h"
#include "Gates/Not.h"
#include "Gates/Or.h"
#include "Gates/Xnor.h"
#include "Gates/Xor.h"
#endif
#include <sys/time.h> // timer for linux ,
										// see http://stackoverflow.com/questions/2150291/how-do-i-measure-a-time-interval-in-c

#include "Input/MapReader.h"
#include "FutureEventList.h"
#include "FutureEvent.h"

using namespace std;
//function declarations
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
void printInput(InputVectorList& myvector){
	vector<InputVector*>::iterator it;

	cout << "input list contains:" << endl;
	for ( it=myvector.begin() ; it != myvector.end(); it++ )
	    cout << (*it)->get_gate()->getName() <<" " << (*it)->get_time_unit() << " " << (*it)->get_switches_to() << endl;
}
//TODO for debugging only, can be deleted
void printCircuit(BaseGate* cGate , int index){//prints rest of the circuit starting from given gate

	int n = cGate->getNumberOfGates_Output();
	cout.width (index*5);
	cout << right;
	if(cGate->isDefined()){
		cout << "(" << cGate->getName() << "-" << cGate->getSignal()  << ")" << endl;
	}else{
		cout << "(" << cGate->getName() << "-" << "undefined"  << ")" << endl;
	}
	index++;
	for(int i = 0 ; i < n ; i++){
		printCircuit((cGate->getOutputGates())[i] ,index );
	}
}
void printCircuit(BaseGate** gates, int inputSize){//prints all circuit
	for(int i = 0 ; i < inputSize ; i++){
		printCircuit(gates[i], 0);
	}
}
void simulate(BaseGate* current_output_gate){
				    int no_inputs=current_output_gate->getNumberOfGates_Input();// get the number of inputs to XX
					bool *inputs=new bool[no_inputs];
					bool current_old_signal=current_output_gate->getSignal();// get the current signal of the gate XX
					for(int j=0; j<no_inputs; j++){// get all the signals to gate XX
						inputs[j]=current_output_gate->getInputGates()[j]->getSignal();
					}
					bool current_new_signal=current_output_gate->operation(inputs);
					if(current_new_signal != current_old_signal){// then this gate should be added to FEL
									 current_output_gate->setSignal(current_new_signal);
					}
}
void simulate_DFS(BaseGate* currentGate)
{
	for(int i=0; i<currentGate->getNumberOfGates_Output() ;i++){
		simulate(currentGate->getOutputGates()[i]);
		simulate_DFS(currentGate->getOutputGates()[i]);
	}
}
void simulate_all_the_circuit_with_default_values_to_inputs(BaseGate ** all_gates,int no_gates)
{
	int i=0;
	for( i=0;i<no_gates;i++){
		all_gates[i]->define_and_set_signal(false);
	}
	for(i=0;i<no_gates;i++){
		simulate_DFS(all_gates[i]);
	}
}
void event_driven_simulation(InputVectorList & inputList,
														BaseGate** all_gates,
														int number_of_input_gates,
														int max_delay,
														int time_increments,
														int no_gates)
{
	    //TODO normally reader->_gcd_delay should be 1 , according to the current circuit, but it returns 4
		 time_increments=1;  //TODO sancar time incrementi 4 olarak donuyor, oysa 1 olmasi lazim

		 FutureEventList  future_event_list(max_delay,time_increments);
		 int current_time=0;
		 int max_size=future_event_list.getSize();
		 int counter_top=0;
	  	 int next_input_time=0;
	  	 if(!inputList.empty()){
					 InputVector *next=inputList.back();
													 inputList.pop_back(); //get the first element from the back of input vector list
					 FutureEvent f_event(next->get_gate(),next->get_switches_to()); // construct an event for that vector
					 int  time_unit_input = next->get_time_unit(); //get its time unit
					 current_time=time_unit_input;                     // set it as current time

					 //get the "current_time % max_size"'th  futureEvent vector
					 future_event_list.get_future_event_list()->operator [](current_time % max_size).push_back(f_event);
					 //while consuming all the inputVector List

					 //while(! inputList.empty() && ){
					 while(!(counter_top==max_size && inputList.empty())){
							 if(!inputList.empty()){
										 next=inputList.back(); //get the last from the input list
										 inputList.pop_back();
										 next_input_time=next->get_time_unit();//get its time unit of change
										 while(next_input_time==current_time){
											 FutureEvent f_event_new(next->get_gate(),next->get_switches_to()); //construct a new FE
											 future_event_list.get_future_event_list()-> operator[]( next_input_time % max_size).push_back(f_event_new);
											 next=inputList.back(); //get the last from the input list
											 inputList.pop_back();
											 next_input_time=next->get_time_unit();//get its time unit of change
										 }
										 FutureEvent f_event_new(next->get_gate(),next->get_switches_to()); //construct a new FE
										 future_event_list.get_future_event_list()-> operator[]( next_input_time % max_size).push_back(f_event_new);//Push it to its place
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
									if( future_event_list.get_future_event_list()->operator [](current_time %max_size).empty()){
											counter_top++;
									}
									else
									{
											counter_top=0;
									}
									//TODO additionally: THIS PART SHOULD BE PARALLELIZED USING CUDA !
									 while(! future_event_list.get_future_event_list()->operator [](current_time %max_size).empty()){
										 	 //burda back()degil de begin() den almasi lazim ki algoritma tam anlamiyla dogru calissin
											 FutureEvent new_event=future_event_list.get_future_event_list()->operator [](current_time %max_size).front();
											 future_event_list.get_future_event_list()->operator [](current_time %max_size).erase(future_event_list.get_future_event_list()->operator [](current_time %max_size).begin());
											 bool new_value=new_event.getNewValue();
											 // every output gate of this gate is searched, and if needed pushed to the FEL
											 find_all_affected_gates_and_add_to_FEL( current_time , max_size, new_value,future_event_list, new_event.getBaseGate() );
									}
									 current_time=current_time + time_increments;
}
void  find_all_affected_gates_and_add_to_FEL(int current_time ,
																			 int max_size,
																			 bool new_value,
																			 FutureEventList &future_event_list,
																			 BaseGate * gate)
{
	bool old_signal=gate->getSignal();
	//if old and new signals are equal than do not consider this !
	if(old_signal!=new_value){
		gate->setSignal(new_value); //set the new signal for the gate
		int no_outputs=gate->getNumberOfGates_Output();
		int i,j;

		for(i=0;i<no_outputs;i++){//for all the output gates...
			BaseGate* current_output_gate=gate->getOutputGates()[i];//take the next output gate, call it XX
			bool current_new_signal;
			if(current_output_gate->isDefined()){//TODO if the gate is not defined WHAT TO DO?, WHEN &HOW to set it to defined!?
																	    /*
																	     * I think that, initially all the Input gates, should be 0,
																	     * and according to that we should set the initial values
																	     * of all the remainding, nonInput gates
																	     * */
				int no_inputs=current_output_gate->getNumberOfGates_Input();// get the number of inputs to XX
				bool *inputs=new bool[no_inputs];
				bool current_old_signal=current_output_gate->getSignal();// get the current signal of the gate XX
				for(j=0; j<no_inputs; j++){// get all the signals to gate XX
					inputs[j]=current_output_gate->getInputGates()[j]->getSignal();
				}
				current_new_signal=current_output_gate->operation(inputs);
				if(current_new_signal != current_old_signal ||
								(current_output_gate->isDefined_NewSignal() &&
											current_new_signal !=current_output_gate->getNextSignalValue())){// then this gate should be added to FEL

					             current_output_gate->define_and_set_nextSignal(current_new_signal); //YENI SIGNAL HAKKINDA BILGI
								 FutureEvent f_event_new(current_output_gate, current_new_signal);
								 int next_input_time=current_time + current_output_gate->getDelay();// assign the time
								 future_event_list.get_future_event_list()-> operator[]( next_input_time % max_size).push_back(f_event_new);
				}
			}
		}
	}
}

int main() {
	MapReader* reader = new MapReader("circuit.xml","input.xml");
	BaseGate** all_gates = new BaseGate* [reader->getNumOfGates()];
	reader->readMap(all_gates);
	InputVector** inputs = new InputVector* [reader->getNumOfInputs()];
	InputVectorList inputList;
	reader->readInput(inputList, inputs);
	printInput(inputList); //for debugging
	timeval start, finish;
	double elapsedTime;
	//--------------------------- START

	gettimeofday(&start, NULL);
	simulate_all_the_circuit_with_default_values_to_inputs(all_gates,reader->getNumOfGates());
    event_driven_simulation(inputList , all_gates, reader->getNumOfInputGates(), reader->getMaxDelay(), reader->getGcdDelay(),reader->getNumOfGates());
    gettimeofday(&finish, NULL);
    //----------------------------FINISH

    elapsedTime = (finish.tv_sec - start.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (finish.tv_usec - start.tv_usec) ;   // us to ms
    cout << elapsedTime << " ms.\n";
    //printCircuit(all_gates,reader->getNumOfGates());
	return 0;
}