

#ifndef DUNGEON_H
#define DUNGEON_H

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
#include <cstring>
#include <endian.h>
#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>


#define ESC 27
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

class Character;
class Object;

class Cell
{
	public:
	int hardness;
	char graphic;
	int isRoom;
	int isLit; // 1 can see 0 cant
	int hasSeen; // 0 hasn't seen 1 has
	int objectNum; // -1 is no object here, 0 - 19 are the objects
	
};

class Room 
{
	public:
	int posx;
	int posy;
	int sizex;
	int sizey;
	int connected;	// where 0 = connected and 1 = not connected
	
};

unsigned long long rdtsc();	

void dungeonInit(Cell dungeon[][80]); //initializes the cells of the dungeon, hardness and graphics

int isValidLocation(int x, int y, int i, Room *allRooms); //returns 0 if given location can be a valid placement of a Room

void generateRooms(Cell dungeon[][80], int *rooms, Room *allRooms); //changes hardness and graphics of the cells of the dungeon as per the spec
//rooms are min 3x2 max 8x5
//# of rooms varies between 5 and 7 inclusively

void connectRooms(Cell dungeon[][80], int *rooms, Room *allRooms); //changes hardness and graphics of cells of the dungeon to properly connect rooms

int writeDungeon(char *filepath, int *version, Cell dungeon[][80], int *rooms, Room *allRooms);

int loadDungeon(char *filepath, int *version, Cell dungeon[][80], int *rooms, Room *allRooms);

int loadRooms(Cell dungeon[][80], int *rooms, Room *allRooms);

int loadCorridors(Cell dungeon[][80]);

int loadStairs(Cell dungeon[][80], int *rooms, Room *allRooms, int *stairsL);

#include "character.h"

void display(Cell dungeon[][80], int *characterIni, int *characterL,  std::vector<NPC *> &characterMap, 
			int *objectIni, std::vector<Object *> &objectMap); //prints the graphics of the dungeon

void displayFog(Cell dungeon[][80], int *stairsL, int *characterIni, int *characterL, std::vector<NPC *> &characterMap, 
			int *objectIni, std::vector<Object *> &objectMap); //"" with fog of war enabled

void displayHardness(Cell dungeon[][80]);

void displayPathing(char *normalWeightMap);

int spawnCharacter(Cell dungeon[][80], int *rooms, Room *allRooms);

#endif
