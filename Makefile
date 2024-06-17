# Makefile
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -g
OBJS = catan.o Board.o GameManager.o Tile.o Player.o Vertex.o  Settlement.o Road.o Card.o 
TEST_OBJS = Board.o GameManager.o Tile.o Player.o Vertex.o Settlement.o Road.o Card.o test.o

all: catan 
run: all
	chmod +x !run_game.sh
	./!run_game.sh

test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	./test
coredump: all
	coredumpctl gdb ./catan
valgrind: all 
	valgrind --leak-check=full --track-origins=yes echo ./test
# valgrind --leak-check=full  --show-leak-kinds=all ./!run_game.sh //running this is irrelevent cause 
#it doesn't show right, it things the shell is a malloc	
catan: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o catan test