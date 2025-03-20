CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# List of object files
OBJS = main.o PrinterJob.o HeapPriorityQueue.o

# Target executable
TARGET = priority_queue

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile main.cpp
main.o: main.cpp HeapPriorityQueue.h PrinterJob.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile PrinterJob.cpp
PrinterJob.o: PrinterJob.cpp PrinterJob.h
	$(CXX) $(CXXFLAGS) -c PrinterJob.cpp

# Compile HeapPriorityQueue.cpp
HeapPriorityQueue.o: HeapPriorityQueue.cpp HeapPriorityQueue.h PrinterJob.h
	$(CXX) $(CXXFLAGS) -c HeapPriorityQueue.cpp

# Clean up build files
clean:
	rm -f $(OBJS) ListPriorityQueue.o $(TARGET)