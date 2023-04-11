#####################################

STEM := clang++ -pedantic -Wall
CSUFFIX := `jgraph-flags --compile`
LSUFFIX := `jgraph-flags --link`

#####################################

demos: bin/ build/ bin/sfmain.out bin/gfmain.out bin/barmain.out bin/dotmain.out bin/linemain.out

#####################################

bin/sfmain.out:	build/sfmain.o
	$(STEM) -o bin/sfmain.out build/sfmain.o $(LSUFFIX)

bin/gfmain.out:	build/gfmain.o
	$(STEM) -o bin/gfmain.out build/gfmain.o $(LSUFFIX)

bin/barmain.out:	build/barmain.o
	$(STEM) -o bin/barmain.out build/barmain.o $(LSUFFIX)

bin/dotmain.out:	build/dotmain.o
	$(STEM) -o bin/dotmain.out build/dotmain.o $(LSUFFIX)

bin/linemain.out:	build/linemain.o
	$(STEM) -o bin/linemain.out build/linemain.o $(LSUFFIX)

#####################################

build/sfmain.o:	demos/sfmain.cpp
	$(STEM) -c demos/sfmain.cpp -o build/sfmain.o  $(CSUFFIX)

build/gfmain.o:	demos/gfmain.cpp
	$(STEM) -c demos/gfmain.cpp -o build/gfmain.o $(CSUFFIX)

build/barmain.o:	demos/barmain.cpp
	$(STEM) -c demos/barmain.cpp -o build/barmain.o $(CSUFFIX)

build/dotmain.o:	demos/dotmain.cpp
	$(STEM) -c demos/dotmain.cpp -o build/dotmain.o $(CSUFFIX)

build/linemain.o:	demos/linemain.cpp
	$(STEM) -c demos/linemain.cpp -o build/linemain.o $(CSUFFIX)

#####################################

bin/:
	mkdir -p bin

build/:
	mkdir -p build

#####################################

clean:
	rm build/*.o

pclean:
	rm build/* bin/*

