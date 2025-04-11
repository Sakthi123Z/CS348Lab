# this is the makefile for lab 9 - sakthi sivasubramanian

CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = lab9
SRC = SakthiSivasubramanianCS348lab9.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
