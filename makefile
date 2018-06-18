CXX =g++ -std=c++11
IFLAGS = -I /usr/local/include
LFLAGS = -L /usr/local/lib64
SRC_DIR = ./src
LINKFLAGS = -lprimesieve -lprimecount -lmpfr -lgmp
RPATH = -Wl,-rpath=/usr/local/lib64
PROGRAM = main
C ?= na
F ?=

.PHONY: all
main: clean
	$(CXX) $(IFLAGS) $(LFLAGS) $(PROGRAM).cc $(SRC_DIR)/* -o $(PROGRAM) $(LINKFLAGS) $(RPATH)

static: clean
	$(CXX) $(IFLAGS) $(LFLAGS) $(PROGRAM).cc $(SRC_DIR)/* -o $(PROGRAM) $(LINKFLAGS) $(RPATH) -static

custom: clean
	$(CXX) $(IFLAGS) $(LFLAGS) $(C).cc $(SRC_DIR)/* -o $(C) $(LINKFLAGS) $(RPATH) $(F)

min: clean
	$(CXX) $(PROGRAM).cc $(SRC_DIR)/* -o $(PROGRAM)

clean:
	rm -rf *.o *~ main ./include/*.h.gch
