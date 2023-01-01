BUILD = build/
BIN = bin/
STEM = clang++ -pedantic -Wall `sdl2-config --cflags --libs`

#####################################

$(BIN)sfmain.out:	$(BUILD)sfmain.o $(BUILD)graph.o $(BUILD)slopefield.o
	$(STEM) $(BUILD)sfmain.o $(BUILD)graph.o $(BUILD)slopefield.o -o $(BIN)sfmain.out

$(BIN)barmain.out:	$(BUILD)barmain.o $(BUILD)graph.o
	$(STEM) $(BUILD)barmain.o $(BUILD)graph.o -o $(BIN)barmain.out

#####################################

$(BUILD)sfmain.o:	sfmain.cpp graph.hpp slopefield.hpp
	$(STEM) -c sfmain.cpp -o $(BUILD)sfmain.o

$(BUILD)barmain.o:	barmain.cpp graph.hpp
	$(STEM) -c barmain.cpp -o $(BUILD)barmain.o

$(BUILD)graph.o:	graph.cpp graph.hpp
	$(STEM) -c graph.cpp -o $(BUILD)graph.o

$(BUILD)slopefield.o:	slopefield.cpp slopefield.hpp
	$(STEM) -c slopefield.cpp -o $(BUILD)slopefield.o

#####################################

clean:
	rm $(BUILD)/*.o

pclean:
	rm $(BUILD)/* $(BIN)/*