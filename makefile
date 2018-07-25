CXX =g++ -std=c++0x -g -w
TFLAGS = -fprofile-arcs -ftest-coverage
# IFLAGS = -I /usr/local/include -I ./include
IFLAGS = -I ./include
LFLAGS = -L /usr/local/lib64
# LFLAGS = -L /usr/local/lib64
SRC_DIR = ./src
SRCS = $(SRC_DIR)/B2.cc $(SRC_DIR)/mobius.cc $(SRC_DIR)/N.cc $(SRC_DIR)/Primetools.cc $(SRC_DIR)/PsiTools.cc $(SRC_DIR)/s1.cc $(SRC_DIR)/s2.cc $(SRC_DIR)/s3.cc $(SRC_DIR)/s4.cc
LINKFLAGS = -fopenmp -lprimesieve -lprimecount -lgmp -lmpfr -lgtest -lpthread
RPATH = -Wl,-rpath=/usr/local/lib64
# RPATH = -Wl,-rpath=/usr/local/lib64

TEST_DIR = ./tests

LCOV = lcov
GCOV = gcov
COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage

PROGRAM = main
PROGRAM_TEST = testMain
C ?= na
F ?=

#g++ -static -std=c++0x -o main -I ./include ./src/*.cc main.cc -fopenmp -lprimesieve -lprimecount -lgmp -lmpfr -lgmp

.PHONY: all
main: clean
	$(CXX) -o $(PROGRAM) $(IFLAGS) $(SRC_DIR)/*.cc main.cc $(LINKFLAGS) $(RPATH)

static: clean
	$(CXX) -static -o $(PROGRAM) $(IFLAGS) $(SRC_DIR)/*.cc main.cc $(LINKFLAGS) -static-libgcc

test: clean
	$(CXX) -o $(C) $(IFLAGS) $(SRC_DIR)/*.cc tests/$(C).cc $(LINKFLAGS) $(RPATH) $(F) -static-libgcc

custom: clean
	#$(CXX) $(IFLAGS) $(C).cc $(SRC_DIR)/* -o $(C) $(LINKFLAGS) $(RPATH) $(F)
	$(CXX) -o $(C) $(IFLAGS) $(SRC_DIR)/*.cc $(C).cc $(LINKFLAGS) $(RPATH) $(F) -static-libgcc

min: clean
	$(CXX) $(PROGRAM).cc $(SRC_DIR)/* -o $(PROGRAM)

clean:
	rm -rf *.o *~ ./include/*.gch *.gcov *.gcda *.gcno $(COVERAGE_RESULTS)

clean-all: clean
	rm -rf $(PROGRAM) $(COVERAGE_DIR)

musl:
	/usr/local/musl/bin/musl-gcc -static -o $(PROGRAM) $(IFLAGS) $(SRC_DIR)/*.cc main.cc $(LINKFLAGS) $(RPATH)

original:
	$(CXX) $(IFLAGS) $(LFLAGS) $(PROGRAM).cc $(SRC_DIR)/* -o $(PROGRAM) $(LINKFLAGS) $(RPATH)

test: $(TEST_DIR)/*.cc
	$(CXX) $(TFLAGS) -o $(PROGRAM_TEST) $(IFLAGS) $(TEST_DIR)/*.cc  $(SRCS) $(LINKFLAGS) $(RPATH)
	./$(PROGRAM_TEST)
	# ./main 384930213

coverage: test
	$(LCOV) --capture --gcov-tool $(GCOV) --directory . --output-file $(COVERAGE_RESULTS)
	$(LCOV) --extract $(COVERAGE_RESULTS) "*/src/*" -o $(COVERAGE_RESULTS)
	genhtml $(COVERAGE_RESULTS) --output-directory $(COVERAGE_DIR)
	rm -f *.gc*
