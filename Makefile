#####################################

STEM = clang++ -pedantic -Wall `sdl2-config --cflags --libs` -lSDL2_ttf

#####################################

demos: bin/sfmain.out bin/gfmain.out bin/barmain.out bin/dotmain.out bin/linemain.out

#####################################

bin/sfmain.out:	build/sfmain.o bin/jgraph.a
	$(STEM) -o bin/sfmain.out build/sfmain.o bin/jgraph.a

bin/gfmain.out:	build/gfmain.o bin/jgraph.a
	$(STEM) -o bin/gfmain.out build/gfmain.o bin/jgraph.a

bin/barmain.out:	build/barmain.o bin/jgraph.a
	$(STEM) -o bin/barmain.out build/barmain.o bin/jgraph.a

bin/dotmain.out:	build/dotmain.o bin/jgraph.a
	$(STEM) -o bin/dotmain.out build/dotmain.o bin/jgraph.a

bin/linemain.out:	build/linemain.o bin/jgraph.a
	$(STEM) -o bin/linemain.out build/linemain.o bin/jgraph.a

#####################################

bin/jgraph.a:	/usr/include/jgraph/bin/jgraph.a
	cp /usr/include/jgraph/bin/jgraph.a bin/jgraph.a

/usr/include/jgraph/bin/jgraph.a:
	cd jgraph && make && cd -

#####################################

build/sfmain.o:	demos/sfmain.cpp
	$(STEM) -c demos/sfmain.cpp -o build/sfmain.o

build/gfmain.o:	demos/gfmain.cpp
	$(STEM) -c demos/gfmain.cpp -o build/gfmain.o

build/barmain.o:	demos/barmain.cpp
	$(STEM) -c demos/barmain.cpp -o build/barmain.o

build/dotmain.o:	demos/dotmain.cpp
	$(STEM) -c demos/dotmain.cpp -o build/dotmain.o

build/linemain.o:	demos/linemain.cpp
	$(STEM) -c demos/linemain.cpp -o build/linemain.o

#####################################

clean:
	rm build/*.o

pclean:
	rm build/* bin/*