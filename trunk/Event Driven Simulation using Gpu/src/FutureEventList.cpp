/*
 * FutureEventList.cpp
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#include "FutureEventList.h"

FutureEventList::FutureEventList(int Maximum_Delay, int time_increments) {
	this->max_Delay = Maximum_Delay;
	this->time_increments = time_increments;
	int size = Maximum_Delay / time_increments + 1;
	this->future_event_list = new vector<event>(size);
	// TODO Auto-generated constructor stub


}

FutureEventList::~FutureEventList() {
	// TODO Auto-generated destructor stub
}

