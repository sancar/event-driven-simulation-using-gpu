/*
 * FutureEventList.h
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#ifndef FUTUREEVENTLIST_H_
#define FUTUREEVENTLIST_H_
#include <thrust/device_vector.h>
#include <vector>

#include "FutureEvent.h"

struct FutureEventList  {
	FutureEvent *future_event_list[FEL_SIZE];
	int low;
	int high;
	//vector<FutureEvent> *future_event_list;//  1 tane
	bool update;
};
/*void FutureEventList_Constructor(FutureEventList& fue, int Maximum_Delay, int time_increments){
	fue.max_Delay = Maximum_Delay;
	fue.time_increments = time_increments;
	fue.size = Maximum_Delay / time_increments + 1;

	fue.future_event_list = new thrust::device_vector<event>(size);
	//fue.future_event_list = new event[fue.size];

}*/


#endif /* FUTUREEVENTLIST_H_ */
