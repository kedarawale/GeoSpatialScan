CXX = g++
CXXFLAGS = -Iinclude -O3  # Add more flags as necessary
LDFLAGS = -Llib -lANN -lm  # Link against the ANN library and math library

# Define the expected output binary under 'bin/'
OUTPUT = bin/rangesearch

# Define source and object files
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)  # Updated to store .o files in the same directory as the .cpp files

# Default target
all: $(OUTPUT)

# Rule for linking the final executable
$(OUTPUT): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Rule for compiling object files
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f src/*.o  # Updated to remove .o files from the src directory
	rm -f $(OUTPUT)

.PHONY: all clean
