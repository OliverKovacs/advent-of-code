CC=gcc
CCFLAGS=-std=c23 -Wall -Wextra -Wpedantic -lm -Iinclude

CXX=g++
CXXFLAGS=-std=c++23 -Wall -Wextra -Wpedantic -lm -Iinclude

BINS_C=$(shell ls src/day*.c | sed 's/\.c//g' | sed 's/src/bin/g')
BINS_CXX=$(shell ls src/day*.cpp | sed 's/\.cpp//g' | sed 's/src/bin/g')
DAYS=$(shell ls src/day*.c* | sed 's/\.cpp//g' | sed 's/\.c//g' | sed 's/src\///g')

$(DAYS): day%: bin/day%
	DATA=$(shell echo $@ | sed 's/.$$//g') && \
	cat test/$$DATA.txt | ./$^ && \
	cat data/$$DATA.txt | ./$^

$(BINS_C): bin/day%: src/day%.c
	$(CC) $(CCFLAGS) $^ -o $@

$(BINS_CXX): bin/day%: src/day%.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f bin/*
