# Makefile
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -g
OBJS = catan.o Board.o GameManager.o Tile.o Player.o Vertex.o  Settlement.o Road.o Card.o 

all: catan
run: all
	chmod +x !run_game.sh
	./!run_game.sh

valgrind: all
	valgrind --leak-check=full --track-origins=yes echo "1 2 3\
		1 2 2\
		2 2 2\
		2 2 6\
		0 0 1\
		0 0 1\
		4 0 1\
		4 0 1\
		3\
		1 2 3\
		1\
		2 2 3\
		1\
		4 2 1\
		2\
		8\
		9\
		"YearOfPlenty"\
		"wood"\
		"brick"\
		8\
		7\
		6"| ./catan

catan: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o catan