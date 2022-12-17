STEM = clang++ -pedantic -Wall `sdl2-config --cflags --libs`

main.out: graph.cpp graph.hpp slopefield.cpp slopefield.hpp main.cpp
	$(STEM) graph.cpp slopefield.cpp main.cpp -o main.out