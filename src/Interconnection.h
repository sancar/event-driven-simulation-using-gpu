/*
 * Interconnection.h
 *
 *  Created on: Oct 29, 2011
 *      Author: Mustafa Sancar Koyunlu
 */

#ifndef INTERCONNECTION_H_
#define INTERCONNECTION_H_

#include "Gates/BaseGate.h"

class Interconnection{
public:
	Interconnection(int);
	~Interconnection();

	void setSignal(bool);
	bool getSignal();
	bool isDefined();

	void addGate(BaseGate*);
private:
	bool _currentSignal;
	bool _defined;
	bool _full;
	BaseGate** _fanouts;
	int _numberOfGates;
	int _currentNumberOfGates;
};


#endif /* INTERCONNECTION_H_ */
