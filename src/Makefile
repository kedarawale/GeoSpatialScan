# Define compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++11 -O2 -g -Iinclude -Iann_src
# Linker flags
LDFLAGS = -Llib -lANN

# Define the source and object files
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Executable name
EXEC = bin/rangesearch

all: $(EXEC)

$(EXEC): $(OBJ)
    $(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f src/*.o $(EXEC)

.PHONY: all clean
