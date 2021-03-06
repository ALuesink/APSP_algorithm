CXX = g++
CFLAGS= -msse3 -O3 -fomit-frame-pointer -funroll-loops 

APPNAME = algorithm
EXT = .cpp
SRC = src
OBJ = obj
BIN = bin
INCLUDE = include
INPUT = input

LIBRARIES = 
EXECUTABLE = main

all: $(BIN)/$(APPNAME)

run: clean all
	clear
	./$(BIN)/$(APPNAME)

$(BIN)/$(APPNAME): $(SRC)/*.cpp 
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*

