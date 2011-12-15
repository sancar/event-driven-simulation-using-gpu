//============================================================================
// Name        : Event.cpp
// Author      : Ervin Domazet - M.Sancar Koyunlu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#define FEL_SIZE 10//can be made larger
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "InputVector.h"

#ifndef GATES
#define GATES
#include "Gates/BaseGate.h"
#endif

#include "Input/MapReader.h"
#include "FutureEventList.h"
#include "FutureEvent.h"
#include <vector>
#include <cutil.h>
#include <cutil_inline.h>
#include <shrQATest.h>
#include <shrUtils.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
								

using namespace std;
enum { INPUT_, AND, NAND, OR, NOR, XOR, XNOR, NOT, FLIPFLOP};
BaseGate* all_gates;
//function declarations
__device__ bool operation(int type, bool* inputs,int numOfInputs){
	if(type == INPUT_ ){
			return inputs[0];
	}else if(type == AND){
			bool result = true;
			for(int i = 0 ; i < numOfInputs ; i++){
				result = result & inputs[i];
			}
			return result;
	}else if(type == NAND){
		bool result = true;
			for(int i = 0 ; i < numOfInputs ; i++){
				result = result & inputs[i];
			}
			return !result;
	}else if(type == OR){
			bool result = false;
			for(int i = 0 ; i < numOfInputs ; i++){
				result = result || inputs[i];
			}
			return result;
	}else if(type == NOR){
		bool result = false;
			for(int i = 0 ; i < numOfInputs ; i++){
				result = result | inputs[i];
			}
			return !result;
	}else if(type == XOR){
			bool result = false;
			for(int i = 0 ;  i < numOfInputs ; i++){
				result = result ^ inputs[i];
			}
			return result;
	}else if(type == XNOR){
			bool result = false;
			for(int i = 0 ;  i < numOfInputs ; i++){
				result = result ^ inputs[i];
			}
			return !result;
	}else if(type == NOT){
		return !inputs[0];
	}else if(type == FLIPFLOP){
		return inputs[0];
	}
	return true;
}
bool operation2(int type, bool* inputs,int numOfInputs){
	if(type == INPUT_ ){
			return inputs[0];
	}else if(type == AND){
			bool result = true;
			for(int i = 0 ; i < numOfInputs ; i++){
				result = result & inputs[i];
			}
			return result;
	}else if(type == NAND){
		bool result = true;
			for(int i = 0 ; i < numOfInputs ; i++){
				result = result & inputs[i];
			}
			return !result;
	}else if(type == OR){
			bool result = false;
			for(int i = 0 ; i < numOfInputs ; i++){
				result = result || inputs[i];
			}
			return result;
	}else if(type == NOR){
		bool result = false;
			for(int i = 0 ; i < numOfInputs ; i++){
				result = result | inputs[i];
			}
			return !result;
	}else if(type == XOR){
			bool result = false;
			for(int i = 0 ;  i < numOfInputs ; i++){
				result = result ^ inputs[i];
			}
			return result;
	}else if(type == XNOR){
			bool result = false;
			for(int i = 0 ;  i < numOfInputs ; i++){
				result = result ^ inputs[i];
			}
			return !result;
	}else if(type == NOT){
		return !inputs[0];
	}else if(type == FLIPFLOP){
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

void printInput(InputVector* myvector, int size){
	
	cout << "input list contains:" << endl;
	for (int i = 0 ; i < size ; i++)
	    cout << all_gates[myvector[i]._ptr_gate]._name <<" " << myvector[i]._at_time_unit << " " << myvector[i]._switches_to << endl;
}
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
					bool current_new_signal=operation2(all_gates[current_output_gate]._type,inputs,all_gates[current_output_gate]._numOfInputs);
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

BaseGate* hostGates;
BaseGate* deviceGates;
InputVector* hostInputs;
InputVector* deviceInputs;
FutureEvent* deviceFue;
//FutureEventList* hostFue;

__global__ void deney(BaseGate* tempGate,InputVector* tempVector,int a){
	
	//__shared__ BaseGate sharedGates;
	if(a > threadIdx.x ){
		tempGate[threadIdx.x]._index = a -  threadIdx.x;
	}
	tempVector[1]._at_time_unit = 7;
}
__global__ void eds(int numberOfGates,int numberOfInputGates, int maxDelay, int timeIncrement, int numberOfInputs, BaseGate* gates, InputVector* inputs){
	
	__shared__ FutureEventList *kernelFue;
	__shared__ bool **currentValues ;
	__shared__ bool change;
	__shared__ FutureEvent* tempVector;
	__shared__ int currentTime;
	__shared__ int* semaphores;
	if(threadIdx.x == numberOfGates){
		kernelFue = (FutureEventList*)malloc(sizeof(FutureEventList) * numberOfGates );
		currentValues = (bool**)malloc(sizeof(bool*) * numberOfGates);
		semaphores = (int*)malloc(sizeof(int) * numberOfGates);
		for(int i = 0; i < numberOfGates; i++){
			currentValues[i] = (bool*) malloc(sizeof(bool) * (maxDelay+1)); 
		}
		tempVector = (FutureEvent*)malloc(sizeof(FutureEvent)* numberOfInputs); 
		/* TODO make shared
		size = numberOfGates+1;
		max_Delay = maxDelay;
		time_increments = timeIncrement;*/
		currentTime = 0;
		change = true;
	}
	__syncthreads();
	if(threadIdx.x < numberOfGates){
		currentValues[threadIdx.x][currentTime%(maxDelay+1)] = gates[threadIdx.x]._currentOutputSignal;
		kernelFue[threadIdx.x].high = 0;
		kernelFue[threadIdx.x].low = 0;
		kernelFue[threadIdx.x].update = false;
		semaphores[threadIdx.x] = 1;
	}
	__syncthreads();
	if(threadIdx.x == numberOfGates){
		for(int i = 0 ; i < numberOfInputs ; i++){
			tempVector[i].time_to_change = inputs[i]._at_time_unit;
			tempVector[i].new_value = inputs[i]._switches_to;
			
			kernelFue[inputs[i]._ptr_gate].future_event_list[kernelFue[inputs[i]._ptr_gate].high] = &tempVector[i] ;
			if(++(kernelFue[inputs[i]._ptr_gate].high) == FEL_SIZE){
				kernelFue[inputs[i]._ptr_gate].high = 0;
				if(kernelFue[inputs[i]._ptr_gate].high == kernelFue[inputs[i]._ptr_gate].low){
					return;//if we enter here, then error
				}
			}
			kernelFue[inputs[i]._ptr_gate].update = true;
		}
	}
	__syncthreads();
	while(change){
		if(threadIdx.x < numberOfGates){
			if(kernelFue[threadIdx.x].update){
				if(kernelFue[threadIdx.x].future_event_list[kernelFue[threadIdx.x].low]->time_to_change ==  currentTime ){
					bool* inputs_current = (bool*)malloc(sizeof(bool) * gates[threadIdx.x]._numOfInputs);
					for(int k=0;k<gates[threadIdx.x]._numOfInputs;k++)
					{
						inputs_current[k]=currentValues[gates[threadIdx.x]._inputGates[k]][(currentTime- gates[threadIdx.x]._delay)%(maxDelay+1)];
					}
					bool newValue=operation(gates[threadIdx.x]._type,inputs_current,gates[threadIdx.x]._numOfInputs);
					gates[threadIdx.x]._currentOutputSignal=newValue;
					kernelFue[threadIdx.x].low++;
					if(kernelFue[threadIdx.x].low==FEL_SIZE){
						kernelFue[threadIdx.x].low=0;
					}
					int *outputGates=gates[threadIdx.x]._outputGates;
					int outputsize=gates[threadIdx.x]._numberOfGates_Output;
					for(int k=0; k < outputsize ; k++){
						while(atomicExch(&semaphores[outputGates[k]],0)==1);
						//critical_section
						FutureEvent *temp=(FutureEvent *)malloc(sizeof(FutureEvent));
						temp->time_to_change=currentTime+gates[outputGates[k]]._delay;
						bool check_if=false;
						for(int m=0;m<FEL_SIZE;m++){
							if(kernelFue[outputGates[k]].future_event_list[m]->time_to_change==temp->time_to_change){
								check_if=true;
								break;
							}
						}
						if(!check_if){
							kernelFue[outputGates[k]].future_event_list[kernelFue[outputGates[k]].high]=temp;
							if(++(kernelFue[outputGates[k]].high) == FEL_SIZE){
								kernelFue[outputGates[k]].high = 0;
								if(kernelFue[outputGates[k]].high== kernelFue[outputGates[k]].low){
									return;//if we enter here, then error
								}
							}
							kernelFue[outputGates[k]].update = true;
						}
						//end critical section
						atomicExch(&semaphores[outputGates[k]],1);	
					}
				}
				if(kernelFue[threadIdx.x].high == kernelFue[threadIdx.x].low){
					kernelFue[threadIdx.x].update = false;
				}			
			}
		}
		if(threadIdx.x == numberOfGates){
			currentTime++;
			for(int i = 0; i < numberOfGates; i++){
				currentValues[threadIdx.x][currentTime%(maxDelay+1)]=gates[threadIdx.x]._currentOutputSignal;
			}
			change = false;
		}
		__syncthreads();
		if(threadIdx.x < numberOfGates){
			if(kernelFue[threadIdx.x].update == true){
				change = true;	
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
	
	//FutureEventList_Constructor( *hostFue ,reader->getMaxDelay(), reader->getGcdDelay());
	
	//cudaMemcpy(deviceFue,hostFue, sizeof(FutureEventList), cudaMemcpyHostToDevice);
	
	hostGates = new BaseGate[reader->getNumOfGates()];
	cudaMalloc((void**)&deviceGates, sizeof(BaseGate)* reader->getNumOfGates() );
	cudaMemcpy(deviceGates,all_gates, sizeof(BaseGate)* reader->getNumOfGates(), cudaMemcpyHostToDevice);
	
	hostInputs= new InputVector[reader->getNumOfInputs()];
	cudaMalloc((void**)&deviceInputs, sizeof(InputVector)* reader->getNumOfInputs() );
	cudaMemcpy(deviceInputs,inputs, sizeof(InputVector)* reader->getNumOfInputs(), cudaMemcpyHostToDevice);
	
	//deney<<<1,512>>>(deviceGates,deviceInputs,reader->getNumOfGates());
	//eds<<<1,reader->getNumOfGates()>>>(reader->getNumOfGates(),reader->getNumOfInputGates(),reader->getMaxDelay(), reader->getGcdDelay(),reader->getNumOfInputs(),deviceGates,deviceInputs);
	
    
	//cudaMemcpy(hostGates,deviceGates, sizeof(BaseGate)* reader->getNumOfGates(), cudaMemcpyDeviceToHost);
	//cudaMemcpy(hostInputs,deviceInputs, sizeof(InputVector)* reader->getNumOfInputs(), cudaMemcpyDeviceToHost);
	
	//for(int i = 0; i < reader->getNumOfGates(); i++){
	//	printf("%d___%d\n", i,hostGates[i]._index);
	//}
	//printf("%d___%d\n", all_gates[1]._delay,inputs[1]._at_time_unit);
	//printf("%d___%d\n",hostGates[1]._delay, hostInputs[1]._at_time_unit);
	
		
	printInput(inputs,reader->getNumOfInputs()); //for debugging

	//timeval start, finish;
	//double elapsedTime;
	//--------------------------- START

	//gettimeofday(&start, NULL);

	//simulate_all_the_circuit_with_default_values_to_inputs(reader->getNumOfGates());

	//TODO inputList yerine inputs g�nderilecek, ve inputs size'� g�nderilecek(reader->getNumOfInputs())

	//gettimeofday(&finish, NULL);
    //----------------------------FINISH
	/*
    elapsedTime = (finish.tv_sec - start.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (finish.tv_usec - start.tv_usec) ;   // us to ms
    cout << elapsedTime << " ms.\n";*/
    //printCircuit(all_gates,reader->getNumOfGates());
	for(;;);
	return 0;
}
