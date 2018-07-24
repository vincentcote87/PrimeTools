CXX =g++ -std=c++0x -g -Wall -fprofile-arcs -ftest-coverage
# IFLAGS = -I /usr/local/include -I ./include
IFLAGS = -I ./include
LFLAGS = -L /usr/local/lib64
# LFLAGS = -L /usr/local/lib64
SRC_DIR = ./src
LINKFLAGS = -lprimesieve -lprimecount -lgmp -lmpfr
RPATH = -Wl,-rpath=/usr/local/lib64
# RPATH = -Wl,-rpath=/usr/local/lib64

LCOV = lcov
GCOV = gcov
COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage

PROGRAM = main
C ?= na
F ?=

#g++ -static -std=c++0x -o s4test -I ./include ./src/*.cc s4test.cc -fopenmp -lprimesieve -lprimecount -lgmp -lmpfr -lgmp

.PHONY: all
main: clean
	# $(CXX) -o $(PROGRAM) $(LFLAGS) $(IFLAGS) $(SRC_DIR)/*.cc main.cc $(LINKFLAGS) $(RPATH)
	$(CXX) -o $(PROGRAM) $(IFLAGS) $(SRC_DIR)/*.cc main.cc $(LINKFLAGS) $(RPATH)
static: clean
	$(CXX) -o $(PROGRAM) $(IFLAGS) $(SRC_DIR)/*.cc main.cc $(LINKFLAGS) $(RPATH) -static-libgcc

custom: clean
	#$(CXX) $(IFLAGS) $(C).cc $(SRC_DIR)/* -o $(C) $(LINKFLAGS) $(RPATH) $(F)
	$(CXX) -o $(C) $(IFLAGS) $(SRC_DIR)/*.cc $(C).cc $(LINKFLAGS) $(RPATH) $(F) -static-libgcc

min: clean
	$(CXX) $(PROGRAM).cc $(SRC_DIR)/* -o $(PROGRAM)

clean:
	rm -rf *.o *~ main ./include/*.gch *.gcov *.gcda *.gcno $(COVERAGE_RESULTS)

musl:
	/usr/local/musl/bin/musl-gcc -static -o $(PROGRAM) $(IFLAGS) $(SRC_DIR)/*.cc main.cc $(LINKFLAGS) $(RPATH)

original:
	$(CXX) $(IFLAGS) $(LFLAGS) $(PROGRAM).cc $(SRC_DIR)/* -o $(PROGRAM) $(LINKFLAGS) $(RPATH)

test: main
	./main 100000

coverage: test
	$(LCOV) --capture --gcov-tool $(GCOV) --directory . --output-file $(COVERAGE_RESULTS)
	$(LCOV) --extract $(COVERAGE_RESULTS) "*/src/*" -o $(COVERAGE_RESULTS)
	genhtml $(COVERAGE_RESULTS) --output-directory $(COVERAGE_DIR)
	rm -f *.gc*
