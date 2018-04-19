all: draw

draw: draw_input.bin
draw_input.bin: draw_input.cpp graphmaker.hpp graphmaker.cpp
	g++ -Wall -Wextra -O2 -g -std=c++11 -o draw_input.bin draw_input.cpp graphmaker.cpp
