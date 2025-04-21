CXX = g++
CXXFLAGS = -std=c++14 -Wall -g
OBJS = main.cpp
HEADERS = Product.h HashTable.h MultiMap.h Sort.h

all: compile

compile: $(OBJS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o mainexe

run: compile
	./mainexe

clean:
	rm -f mainexe
