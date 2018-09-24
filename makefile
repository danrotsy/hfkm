install:
	# Builds all commands to bin. NTL *MUST* be installed. (see readme.txt)
	g++ -std=c++11 -I include -c src/jta.cpp -o build/jta.o
	g++ -std=c++11 -I include -c src/gridgen.cpp -o build/gridgen.o
	g++ -std=c++11 -I include -c src/rect.cpp -o build/rect.o
	g++ -std=c++11 -I include -c src/gridio.cpp -o build/gridio.o
	g++ -std=c++11 -I include -c src/grid.cpp -o build/grid.o
	g++ -std=c++11 -I include -c src/cgen.cpp -o build/cgen.o
	g++ -std=c++11 -I include -c src/gencmd.cpp -o build/gencmd.o
	g++ -std=c++11 -I include -o bin/gen build/jta.o build/gridgen.o \
	build/rect.o build/gridio.o build/cgen.o build/grid.o \
	build/gencmd.o -lboost_system -lboost_filesystem
	g++ -std=c++11 -I include -c src/expsni.cpp -o build/expsni.o
	g++ -std=c++11 -I include -c src/cgrp.cpp -o build/cgrp.o
	g++ -std=c++11 -I include -c src/diff.cpp -o build/diff.o
	g++ -std=c++11 -I include -c src/hom.cpp -o build/hom.o
	g++ -std=c++11 -I include -c src/hfkmcmd.cpp -o build/hfkmcmd.o
	g++ -std=c++11 -I include -pthread -o bin/hfkm build/jta.o \
	build/gridgen.o build/rect.o build/gridio.o build/expsni.o \
	build/cgen.o build/grid.o build/cgrp.o build/diff.o \
	build/hom.o build/hfkmcmd.o -lboost_system -lboost_filesystem -lntl \
	-lgmp
gen:
	# This command is used to compute generators. (see readme.txt)
	g++ -std=c++11 -I include -c src/jta.cpp -o build/jta.o
	g++ -std=c++11 -I include -c src/gridgen.cpp -o build/gridgen.o
	g++ -std=c++11 -I include -c src/rect.cpp -o build/rect.o
	g++ -std=c++11 -I include -c src/gridio.cpp -o build/gridio.o
	g++ -std=c++11 -I include -c src/grid.cpp -o build/grid.o
	g++ -std=c++11 -I include -c src/cgen.cpp -o build/cgen.o
	g++ -std=c++11 -I include -c src/gencmd.cpp -o build/gencmd.o
	g++ -std=c++11 -I include -o bin/gen build/jta.o build/gridgen.o \
	build/rect.o build/gridio.o build/cgen.o build/grid.o \
	build/gencmd.o -lboost_system -lboost_filesystem
hfkm:
	# This command is used to compute HFK^-(K). (see readme.txt)
	g++ -std=c++11 -I include -c src/jta.cpp -o build/jta.o
	g++ -std=c++11 -I include -c src/gridgen.cpp -o build/gridgen.o
	g++ -std=c++11 -I include -c src/rect.cpp -o build/rect.o
	g++ -std=c++11 -I include -c src/gridio.cpp -o build/gridio.o
	g++ -std=c++11 -I include -c src/grid.cpp -o build/grid.o
	g++ -std=c++11 -I include -c src/expsni.cpp -o build/expsni.o
	g++ -std=c++11 -I include -c src/cgen.cpp -o build/cgen.o
	g++ -std=c++11 -I include -c src/cgrp.cpp -o build/cgrp.o
	g++ -std=c++11 -I include -c src/diff.cpp -o build/diff.o
	g++ -std=c++11 -I include -c src/hom.cpp -o build/hom.o
	g++ -std=c++11 -I include -c src/hfkmcmd.cpp -o build/hfkmcmd.o
	g++ -std=c++11 -I include -pthread -o bin/hfkm build/jta.o \
	build/gridgen.o build/rect.o build/gridio.o build/expsni.o \
	build/cgen.o build/grid.o build/cgrp.o build/diff.o \
	build/hom.o build/hfkmcmd.o -lboost_system -lboost_filesystem -lntl \
	-lgmp
clean:
	# Cleaning object and binary files.
	rm build/*;
	rm bin/*
