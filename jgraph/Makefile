#####################################

STEM = clang++ -pedantic -Wall
SUFFIX = `jgraph-flags`

#####################################

install:	bin/libjgraph.a /usr/bin/jgraph-flags
	sudo apt install libsdl2-dev libsdl2-ttf-dev
	sudo rm -rf /usr/include/jgraph
	sudo cp -r . /usr/include/jgraph

#####################################

bin/libjgraph.a:	bin/ build/ build/graph.o build/slopefield.o build/text.o build/drivers.o build/gradfield.o build/csv.o
	ar -rsv bin/libjgraph.a build/graph.o build/slopefield.o build/text.o build/drivers.o build/gradfield.o build/csv.o

/usr/bin/jgraph-flags:	jgraph-flags.sh
	chmod +x jgraph-flags.sh
	sudo cp ./jgraph-flags.sh /usr/bin/jgraph-flags

#####################################

bin/:
	mkdir -p bin

build/:
	mkdir -p build

#####################################

build/graph.o:	src/graph.cpp graph.hpp
	$(STEM) -c src/graph.cpp -o build/graph.o $(SUFFIX)

build/slopefield.o:	src/slopefield.cpp slopefield.hpp
	$(STEM) -c src/slopefield.cpp -o build/slopefield.o $(SUFFIX)

build/gradfield.o:	src/gradientfield.cpp gradientfield.hpp
	$(STEM) -c src/gradientfield.cpp -o build/gradfield.o $(SUFFIX)

build/text.o:	src/text.cpp text.hpp
	$(STEM) -c src/text.cpp -o build/text.o $(SUFFIX)

build/drivers.o:	src/drivers.cpp drivers.hpp
	$(STEM) -c src/drivers.cpp -o build/drivers.o $(SUFFIX)

build/csv.o:	src/csv.cpp csv.hpp
	$(STEM) -c src/csv.cpp -o build/csv.o $(SUFFIX)

#####################################

pclean:
	rm bin/* build/*

uninstall:
	rm bin/* build/*
	sudo rm -rf /usr/include/jgraph

#####################################