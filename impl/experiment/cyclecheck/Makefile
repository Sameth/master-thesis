all: countgraph.bin cycle draw

countgraph.bin: countgraph.cpp pp2p.cpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o countgraph.bin countgraph.cpp pp2p.cpp

cycle: cycle1.bin cycle2.bin cycle3.bin cycle4.bin cycle5.bin cycle6.bin
cycle1.bin: cyclecheck.cpp pp2p.cpp pp2p.hpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o cycle1.bin cyclecheck.cpp pp2p.cpp
cycle2.bin: cyclebetter.cpp pp2p.cpp pp2p.hpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o cycle2.bin cyclebetter.cpp pp2p.cpp
cycle3.bin: cycleminimal.cpp pp2p.cpp pp2p.hpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o cycle3.bin cycleminimal.cpp pp2p.cpp
cycle4.bin: cycleuniq.cpp pp2p.cpp pp2p.hpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o cycle4.bin cycleuniq.cpp pp2p.cpp
cycle5.bin: cyclemaxstart.cpp pp2p.cpp pp2p.hpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o cycle5.bin cyclemaxstart.cpp pp2p.cpp
cycle6.bin: cyclemaxzerostart.cpp pp2p.cpp pp2p.hpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o cycle6.bin cyclemaxzerostart.cpp pp2p.cpp

draw: draw_largest.bin
draw_largest.bin: draw_largest.cpp pp2p.cpp pp2p.hpp graphmaker.hpp graphmaker.cpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o draw_largest.bin draw_largest.cpp pp2p.cpp graphmaker.cpp
