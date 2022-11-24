MAKEFLAGS += --silent
CC = g++
CC_FLAGS = -std=c++17 -Wall

EXECUTABLE=./main

run: $(EXECUTABLE)
	$(EXECUTABLE)

$(EXECUTABLE): Main.cpp
	$(CC) $(CC_FLAGS) Main.cpp -o $(EXECUTABLE)
