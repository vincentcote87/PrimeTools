CXX =g++ -std=c++0x -g
IFLAGS = -I /usr/local/include -I include
LFLAGS = -L /usr/local/lib64
SRC_DIR = ./src
LINKFLAGS = -lprimesieve -lprimecount -lgmp -lmpfr
RPATH = -Wl,-rpath=/usr/local/lib64
PROGRAM = main
C ?= na
F ?=

.PHONY: all
main: clean
	$(CXX) -o $(PROGRAM) $(LFLAGS) $(IFLAGS) $(SRC_DIR)/*.cc main.cc $(LINKFLAGS) $(RPATH) -static-libgcc

static: clean
	$(CXX) -o $(PROGRAM) $(LFLAGS) $(IFLAGS) $(SRC_DIR)/*.cc main.cc $(LINKFLAGS) $(RPATH) -static-libgcc

custom: clean
	$(CXX) $(IFLAGS) $(LFLAGS) $(C).cc $(SRC_DIR)/* -o $(C) $(LINKFLAGS) $(RPATH) $(F) -static-libgcc

min: clean
	$(CXX) $(PROGRAM).cc $(SRC_DIR)/* -o $(PROGRAM) -static-libgcc

clean:
	rm -rf *.o *~ main ./include/*.gch

oiginal:
	$(CXX) $(IFLAGS) $(LFLAGS) $(PROGRAM).cc $(SRC_DIR)/* -o $(PROGRAM) $(LINKFLAGS) $(RPATH) -static-libgcc
