/*
 * FutureEvent.h
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#ifndef FUTUREEVENT_H_
#define FUTUREEVENT_H_

#include "Interconnection.h"


class FutureEvent {
public:
	FutureEvent(Interconnection *, bool);
	virtual ~FutureEvent();

private:
	Interconnection *inter_connection;
	bool new_value;
};

#endif /* FUTUREEVENT_H_ */
