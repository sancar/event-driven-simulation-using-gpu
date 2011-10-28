/*
 * FutureEvent.h
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#ifndef FUTUREEVENT_H_
#define FUTUREEVENT_H_

class interconnection;

class FutureEvent {
public:
	FutureEvent(interconnection *, bool);
	virtual ~FutureEvent();

private:
	interconnection *inter_connection;
	bool new_value;
};

#endif /* FUTUREEVENT_H_ */
