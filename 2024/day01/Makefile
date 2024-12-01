CXX=clang++
CXXFLAGS=--std=c++23 --stdlib=libc++

FILES=$(shell ls *.cpp | sed 's/.cpp//g')
RUN=$(shell ls *.cpp | sed 's/.cpp//g' | sed 's/main/run/g')

$(RUN): run%: main%
	cat input | ./$^

$(FILES): %: %.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(FILES)
