/*
 * FutureEvent.h
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#ifndef FUTUREEVENT_H_
#define FUTUREEVENT_H_

#include "Gates/BaseGate.h"


class FutureEvent {
public:
	FutureEvent(BaseGate *, bool);
	virtual ~FutureEvent();

private:
	BaseGate *base_gate;
	bool new_value;
};

#endif /* FUTUREEVENT_H_ */
