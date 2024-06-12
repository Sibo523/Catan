# Makefile
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -g
OBJS = catan.o Board.o GameManager.o Tile.o Player.o Vertex.o  Settlement.o

all: catan

catan: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o catan