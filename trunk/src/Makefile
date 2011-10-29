
trial.exe:	BaseGate.o Interconnection.o And.o Nand.o Or.o Nor.o FlipFlop.o Xor.o Xnor.o 
		g++ BaseGate.o Interconnection.o And.o Nand.o Or.o Nor.o FlipFlop.o Xor.o Xnor.o 

And.o:	Gates/And.h Gates/And.cpp BaseGate.o
		g++ -c Gates/And.h Gates/And.cpp BaseGate.o

Nand.o:	Gates/Nand.h Gates/Nand.cpp BaseGate.o
		g++ -c Gates/Nand.h Gates/Nand.cpp BaseGate.o

Or.o:	Gates/Or.h Gates/Or.cpp BaseGate.o
		g++ -c Gates/Or.h Gates/Or.cpp BaseGate.o

Nor.o:	Gates/Nor.h Gates/Nor.cpp BaseGate.o
		g++ -c Gates/Nor.h Gates/Nor.cpp BaseGate.o

FlipFlop.o:	Gates/FlipFlop.h Gates/FlipFlop.cpp BaseGate.o
		g++ -c Gates/FlipFlop.h Gates/FlipFlop.cpp BaseGate.o

Xor.o:	Gates/Xor.h Gates/Xor.cpp BaseGate.o
		g++ -c Gates/Xor.h Gates/Xor.cpp BaseGate.o

Xnor.o:	Gates/Xnor.h Gates/Xnor.cpp BaseGate.o
		g++ -c Gates/Xnor.h Gates/Xnor.cpp BaseGate.o

BaseGate.o:	Gates/BaseGate.h Gates/BaseGate.cpp Interconnection.o
		g++ -c Gates/BaseGate.h Gates/BaseGate.cpp Interconnection.o

Interconnection.o:	Interconnection.h Interconnection.cpp BaseGate.o
		g++ -c Interconnection.h Interconnection.cpp BaseGate.o