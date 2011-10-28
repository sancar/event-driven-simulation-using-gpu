/*
 * InputVectorList.cpp
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 */

#include "InputVectorList.h"

InputVectorList::InputVectorList() {
	// TODO Auto-generated constructor stub
}

InputVectorList::~InputVectorList() {
	// TODO Auto-generated destructor stub
}
void InputVectorList::push_to_list(InputVector & Node) {
	inputvectorlist.push_back(Node);
}
void InputVectorList::pop_from_list() {
	inputvectorlist.pop_back();
}
