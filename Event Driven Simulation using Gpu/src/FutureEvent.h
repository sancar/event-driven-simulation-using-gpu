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
	BaseGate *base_gate;
	bool new_value;
};
void FutureEvent_Constructor(FutureEvent& fu, BaseGate* gate, bool c_event){
	fu.base_gate = gate;
	fu.new_value = c_event;

}
#endif /* FUTUREEVENT_H_ */
