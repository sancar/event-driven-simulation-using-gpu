/*
 * FutureEvent.h
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#ifndef FUTUREEVENT_H_
#define FUTUREEVENT_H_

struct BaseGate;


struct FutureEvent {
	
	int time_to_change;
	bool new_value;

};
void FutureEvent_Constructor(FutureEvent& fu, int time, bool c_event){
	fu.time_to_change = time;
	fu.new_value = c_event;

}
#endif /* FUTUREEVENT_H_ */
