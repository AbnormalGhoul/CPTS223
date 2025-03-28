CXX = g++
CXXFLAGS = -g -Wall -std=c++14

SRCS = main.cpp product.cpp inventorysystem.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = mainexe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

#====================
# # Compiler and flags
# CXX = g++
# CXXFLAGS = -g -Wall -std=c++14

# # Executable name
# TARGET = mainexe

# # Source files
# SRCS = main.cpp CustomHashTable.cpp
# OBJS = $(SRCS:.cpp=.o)

# # Build the executable
# $(TARGET): $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# # Compile source files into object files
# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Run the program
# run: $(TARGET)
# 	./$(TARGET)

# # Clean up generated files
# clean:
# 	rm -f $(OBJS) $(TARGET)
