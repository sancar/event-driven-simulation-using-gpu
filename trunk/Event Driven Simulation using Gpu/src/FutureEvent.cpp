/*
 * FutureEvent.cpp
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#include "FutureEvent.h"


FutureEvent::FutureEvent(Interconnection* conn, bool event) {
	this->inter_connection = conn;
	this->new_value = event;

	// TODO Auto-generated constructor stub

}

FutureEvent::~FutureEvent() {
	// TODO Auto-generated destructor stub
}

