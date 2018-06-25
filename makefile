CXX =g++ -std=c++0x -g
IFLAGS = -I /usr/local/include -I include
LFLAGS = -L /usr/local/lib64
SRC_DIR = ./src
LINKFLAGS = -lprimesieve -lprimecount
RPATH = -Wl,-rpath=/usr/local/lib64
PROGRAM = main
C ?= na
F ?=

.PHONY: all
main: clean
	$(CXX) -o $(PROGRAM) $(LFLAGS) $(IFLAGS) $(SRC_DIR)/*.cc main.cc $(LINKFLAGS) $(RPATH)

static: clean
	$(CXX) $(IFLAGS) $(LFLAGS) $(PROGRAM).cc $(SRC_DIR)/* -o $(PROGRAM) $(LINKFLAGS) $(RPATH) -static

custom: clean
	$(CXX) $(IFLAGS) $(LFLAGS) $(C).cc $(SRC_DIR)/* -o $(C) $(LINKFLAGS) $(RPATH) $(F)

min: clean
	$(CXX) $(PROGRAM).cc $(SRC_DIR)/* -o $(PROGRAM)

clean:
	rm -rf *.o *~ main ./include/*.gch

oiginal:
	$(CXX) $(IFLAGS) $(LFLAGS) $(PROGRAM).cc $(SRC_DIR)/* -o $(PROGRAM) $(LINKFLAGS) $(RPATH)
