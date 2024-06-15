# Makefile
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -g
OBJS = catan.o Board.o GameManager.o Tile.o Player.o Vertex.o  Settlement.o Road.o 

all: catan
run: all
	chmod +x !run_game.sh
	./!run_game.sh

valgrind: all
	chmod +x !run_game.sh
	./!run_game.sh 
catan: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o catan