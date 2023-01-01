BUILD = build/
BIN = bin/
STEM = clang++ -pedantic -Wall `sdl2-config --cflags --libs`

#####################################

$(BIN)sfmain.out:	$(BUILD)sfmain.o $(BUILD)graph.o $(BUILD)slopefield.o
	$(STEM) $(BUILD)sfmain.o $(BUILD)graph.o $(BUILD)slopefield.o -o $(BIN)sfmain.out

$(BIN)barmain.out:	$(BUILD)barmain.o $(BUILD)graph.o
	$(STEM) $(BUILD)barmain.o $(BUILD)graph.o -o $(BIN)barmain.out

$(BIN)dotmain.out:	$(BUILD)dotmain.o $(BUILD)graph.o $(BUILD)slopefield.o
	$(STEM) $(BUILD)dotmain.o $(BUILD)graph.o $(BUILD)slopefield.o -o $(BIN)dotmain.out

$(BIN)linemain.out:	$(BUILD)linemain.o $(BUILD)graph.o
	$(STEM) $(BUILD)linemain.o $(BUILD)graph.o -o $(BIN)linemain.out

#####################################

$(BUILD)sfmain.o:	demos/sfmain.cpp graph.hpp slopefield.hpp
	$(STEM) -c demos/sfmain.cpp -o $(BUILD)sfmain.o

$(BUILD)barmain.o:	demos/barmain.cpp graph.hpp
	$(STEM) -c demos/barmain.cpp -o $(BUILD)barmain.o

$(BUILD)dotmain.o:	demos/dotmain.cpp graph.hpp
	$(STEM) -c demos/dotmain.cpp -o $(BUILD)dotmain.o

$(BUILD)linemain.o:	demos/linemain.cpp graph.hpp
	$(STEM) -c demos/linemain.cpp -o $(BUILD)linemain.o

#####################################

$(BUILD)graph.o:	graph.cpp graph.hpp
	$(STEM) -c graph.cpp -o $(BUILD)graph.o

$(BUILD)slopefield.o:	slopefield.cpp slopefield.hpp
	$(STEM) -c slopefield.cpp -o $(BUILD)slopefield.o

#####################################

clean:
	rm $(BUILD)/*.o

pclean:
	rm $(BUILD)/* $(BIN)/*