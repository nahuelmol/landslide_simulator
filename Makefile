CXX = g++
CXXFLAGS = -Wall -Iinclude
CC = gcc
SRC = $(shell find src -name "*.cpp")
OBJ = $(SRC:.cpp=.o)
TARGET = dext
all = $(TARGET)

$(TARGET): $(OBJ) 
	$(CXX) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
