/*
 * InputVectorList.h
 *
 *  Created on: Oct 28, 2011
 *      Author: patron
 *deneme
 */

#ifndef INPUTVECTORLIST_H_
#define INPUTVECTORLIST_H_

#include "InputVector.h"
#include <vector>

using std::vector;
class InputVectorList {
public:
	InputVectorList();
	virtual ~InputVectorList();
	void push_to_list(InputVector&);
	void pop_from_list();
private:
	vector<InputVector> inputvectorlist;
};

#endif /* INPUTVECTORLIST_H_ */
