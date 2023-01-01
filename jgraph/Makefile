#####################################

STEM = clang++ -pedantic -Wall `sdl2-config --cflags --libs`

#####################################

install:	bin/jgraph.a
	sudo apt install libsdl2-dev
	sudo rm -rf /usr/include/jgraph
	sudo cp -r . /usr/include/jgraph

#####################################

bin/jgraph.a:	bin/ build/ build/graph.o build/slopefield.o
	ar rsv bin/jgraph.a build/graph.o build/slopefield.o

#####################################

bin/:
	mkdir -p bin

build/:
	mkdir -p build

#####################################

build/graph.o:	src/graph.cpp graph.hpp
	$(STEM) -c src/graph.cpp -o build/graph.o

build/slopefield.o:	src/slopefield.cpp slopefield.hpp
	$(STEM) -c src/slopefield.cpp -o build/slopefield.o

#####################################