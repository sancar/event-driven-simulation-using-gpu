/*
 * FutureEventList.h
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#ifndef FUTUREEVENTLIST_H_
#define FUTUREEVENTLIST_H_
//#include <thrust/host_vector.h>
#include <vector>

#include "FutureEvent.h"

//typedef thrust::host_vector<FutureEvent> event;
typedef vector<FutureEvent> event;
struct FutureEventList  {
	vector <event> *future_event_list;
	int size;
	int max_Delay;
	int time_increments;
};
void FutureEventList_Constructor(FutureEventList& fue, int Maximum_Delay, int time_increments){
	fue.max_Delay = Maximum_Delay;
	fue.time_increments = time_increments;
	fue.size = Maximum_Delay / time_increments + 1;

	//fue.future_event_list = new thrust::host_vector<event>(size);
	fue.future_event_list = new vector<event>(fue.size);

}


#endif /* FUTUREEVENTLIST_H_ */
