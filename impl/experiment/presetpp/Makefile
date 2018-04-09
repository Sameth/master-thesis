all: presetratio.bin dvojicavrcholov.bin


presetratio.bin: presetratio.cpp pp2p.cpp pp2p.hpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o presetratio.bin presetratio.cpp pp2p.cpp

dvojicavrcholov.bin: dvojicavrcholov.cpp pp2p.cpp pp2p.hpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o dvojicavrcholov.bin dvojicavrcholov.cpp pp2p.cpp
