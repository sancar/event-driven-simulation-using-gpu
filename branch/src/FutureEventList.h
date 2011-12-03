/*
 * FutureEventList.h
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#ifndef FUTUREEVENTLIST_H_
#define FUTUREEVENTLIST_H_
#include <vector>
#include "FutureEvent.h"
using std::vector;
typedef vector<FutureEvent> event;
class FutureEventList  {
public:
	FutureEventList(int Maximum_Delay, int time_increments);
	virtual ~FutureEventList();
	int getSize();
	vector <event> * get_future_event_list();
private:
	vector<event> *future_event_list;
	int size;
	int max_Delay;
	int time_increments;

};

#endif /* FUTUREEVENTLIST_H_ */
