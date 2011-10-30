//============================================================================
// Name        : Event.cpp
// Author      : Ervin Domazet - M.Sancar Koyunlu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "InputVector.h"

using namespace std;
#include "Gates/BaseGate.h"
#include "Gates/And.h"
#include "Gates/FlipFlop.h"
#include "Gates/Nand.h"
#include "Gates/Nor.h"
#include "Gates/Not.h"
#include "Gates/Or.h"
#include "Gates/Xnor.h"
#include "Gates/Xor.h"
int main() {
    And ervin(4,3,2);
    Or harun(2,2,2);
    ervin.addGate_Output(&harun);

    BaseGate *deneme=&ervin;
	InputVector *a = new InputVector(deneme,15, true);
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
