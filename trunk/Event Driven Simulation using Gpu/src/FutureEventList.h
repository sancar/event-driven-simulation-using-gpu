/*
 * FutureEventList.h
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#ifndef FUTUREEVENTLIST_H_
#define FUTUREEVENTLIST_H_
#include <thrust/host_vector.h>

#include "FutureEvent.h"

typedef thrust::host_vector<FutureEvent> event;
struct FutureEventList  {
	thrust::host_vector<event> *future_event_list;
	int size;
	int max_Delay;
	int time_increments;

};
FutureEventList_Constructor(FutureEventList& fue, int Maximum_Delay, int time_increments){
	fue.max_Delay = Maximum_Delay;
	fue.time_increments = time_increments;
	fue.size = Maximum_Delay / time_increments + 1;

	fue.future_event_list = new thrust::host_vector<event>(size);
}

#endif /* FUTUREEVENTLIST_H_ */
