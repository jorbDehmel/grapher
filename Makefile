STEM = clang++ -pedantic -Wall `sdl2-config --cflags --libs`

main.out: graph.cpp graph.hpp main.cpp
	$(STEM) graph.cpp main.cpp -o main.out