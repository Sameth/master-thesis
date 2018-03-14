all: countgraph.bin cycle

countgraph.bin: countgraph.cpp pp2p.cpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o countgraph.bin countgraph.cpp pp2p.cpp

cycle: cycle1.bin cycle2.bin cycle3.bin
cycle1.bin: cyclecheck.cpp pp2p.cpp pp2p.hpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o cycle1.bin cyclecheck.cpp pp2p.cpp
cycle2.bin: cyclebetter.cpp pp2p.cpp pp2p.hpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o cycle2.bin cyclebetter.cpp pp2p.cpp
cycle3.bin: cycleminimal.cpp pp2p.cpp pp2p.hpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o cycle3.bin cycleminimal.cpp pp2p.cpp
