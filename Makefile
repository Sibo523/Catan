# Makefile
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -g
OBJS = catan.o Board.o GameManager.o Tile.o Player.o Vertex.o  Settlement.o Road.o Card.o 
TEST_OBJS = Board.o GameManager.o Tile.o Player.o Vertex.o Settlement.o Road.o Card.o test.o

all: catan test 
run: all
	chmod +x !run_game.sh
	./!run_game.sh

test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	./test
	
valgrind: all test
	valgrind --leak-check=full --track-origins=yes echo ./test

catan: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o catan test