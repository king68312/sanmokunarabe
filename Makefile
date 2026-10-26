CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDLIBS =  -lgtest -lgtest_main -pthread

.PHONY: all test clean

all: game board_test

game: board.cpp key.cpp main.cpp board.h key.h
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@

board_test: board.cpp key.cpp board_test.cpp board.h key.h
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) $(LDLIBS) -o $@

test: board_test
	./board_test

clean:
	rm -f game board_test
