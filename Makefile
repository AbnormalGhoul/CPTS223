# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -g

# Executable names
LIST_EXEC = list_josephus
VECTOR_EXEC = vector_josephus

# Source files
LIST_SRC = ListMyJosephus.cpp Destination.cpp TestListMyJosephus.cpp
VECTOR_SRC = VectorMyJosephus.cpp Destination.cpp TestVectorMyJosephus.cpp

# Default target (compiles both programs)
all: $(LIST_EXEC) $(VECTOR_EXEC)

# Compile list-based Josephus program
$(LIST_EXEC): $(LIST_SRC)
	$(CXX) $(CXXFLAGS) -o $(LIST_EXEC) $(LIST_SRC)

# Compile vector-based Josephus program
$(VECTOR_EXEC): $(VECTOR_SRC)
	$(CXX) $(CXXFLAGS) -o $(VECTOR_EXEC) $(VECTOR_SRC)

# Clean up compiled files
clean:
	rm -f $(LIST_EXEC) $(VECTOR_EXEC)
