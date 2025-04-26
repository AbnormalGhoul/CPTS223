# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

# Output executable name
TARGET = ma4

# Source files
SRC = ma4.cpp

# Default target
all: $(TARGET)

# Compile rule
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(TARGET)
