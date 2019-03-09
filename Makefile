all: dungeon

dungeon: main.cpp dungeon.cpp
	g++ -o dungeon dungeon.cpp main.cpp queue.cpp graph.cpp character.cpp game.cpp -lncurses -Werror -Wall -ggdb
clean:
	rm -f dungeon *~
