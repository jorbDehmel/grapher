#####################################

STEM = clang++ -pedantic -Wall
SUFFIX = `jgraph-flags`

#####################################

install:
	$(MAKE) -C jgraph

demos: bin/sfmain.out bin/gfmain.out bin/barmain.out bin/dotmain.out bin/linemain.out

#####################################

bin/sfmain.out:	build/sfmain.o bin/libjgraph.a
	$(STEM) -o bin/sfmain.out build/sfmain.o $(SUFFIX)

bin/gfmain.out:	build/gfmain.o bin/libjgraph.a
	$(STEM) -o bin/gfmain.out build/gfmain.o $(SUFFIX)

bin/barmain.out:	build/barmain.o bin/libjgraph.a
	$(STEM) -o bin/barmain.out build/barmain.o $(SUFFIX)

bin/dotmain.out:	build/dotmain.o bin/libjgraph.a
	$(STEM) -o bin/dotmain.out build/dotmain.o $(SUFFIX)

bin/linemain.out:	build/linemain.o bin/libjgraph.a
	$(STEM) -o bin/linemain.out build/linemain.o $(SUFFIX)

#####################################

bin/libjgraph.a:	/usr/include/jgraph/bin/libjgraph.a
	cp /usr/include/jgraph/bin/libjgraph.a bin/libjgraph.a

/usr/include/jgraph/bin/libjgraph.a:
	cd jgraph && make && cd -

#####################################

build/sfmain.o:	demos/sfmain.cpp
	$(STEM) -c demos/sfmain.cpp -o build/sfmain.o  $(SUFFIX)

build/gfmain.o:	demos/gfmain.cpp
	$(STEM) -c demos/gfmain.cpp -o build/gfmain.o $(SUFFIX)

build/barmain.o:	demos/barmain.cpp
	$(STEM) -c demos/barmain.cpp -o build/barmain.o $(SUFFIX)

build/dotmain.o:	demos/dotmain.cpp
	$(STEM) -c demos/dotmain.cpp -o build/dotmain.o $(SUFFIX)

build/linemain.o:	demos/linemain.cpp
	$(STEM) -c demos/linemain.cpp -o build/linemain.o $(SUFFIX)

#####################################

clean:
	rm build/*.o

pclean:
	rm build/* bin/*

