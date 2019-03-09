#ifndef CHARACTER_H
#define CHARACTER_H

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

#define NOTYPE 0
#define WEAPON 1
#define OFFHAND 2
#define RANGED 3
#define LIGHT 4
#define ARMOR 5
#define HELMET 6
#define CLOAK 7
#define GLOVES 8
#define BOOTS 9
#define AMULET 10
#define RING 11
#define SCROLL 12
#define BOOK 13
#define FLASK 14
#define GOLD 15
#define AMMUNITION 16
#define FOOD 17
#define WAND 18
#define CONTAINER 19

#define INTELLIGENT 0x1
#define TELEPATHIC 0x2
#define TUNNELING 0x4
#define ERRATIC 0x8
#define PASS 0x16
#define PICKUP 0x32
#define DESTROY 0x64
#define UNIQ 0x128

#define NUMBER_OF_OBJECTS 12
extern const char object_symbol[];

class Dice
{
	public:
	int base;
	int dice;
	int sides;
	
	int roll()
	{
		int temp = 0;
		for(int i = 0; i < dice; i++)
		{
			temp+= ((rand()%sides) + 1);
		}
		return base + temp;
	}
};

class Object
{
	public:
	int type;
	int color;
	Dice weightDice;
	Dice hitDice;
	Dice attrDice;
	Dice valDice;
	Dice damDice; 
	Dice dodgeDice;
	Dice defDice;
	Dice speedDice; 
	std::string name;
	std::string desc;
	int weight;
	int hit;
	int attr;
	int val;
	int dodge;
	int def;
	int speed;
	
};

class Character
{
	public:
	int speed;
	char symbol;
	char sequence;
	int hp;
	Dice damDice;
	
};

class PC: public Character
{
	public:
	std::vector<Object *> carrySlots; //10 max (must be maintained by me, {obviously})
	std::vector<Object *> equipment;
	/*Object *weapon; //a 1
	Object *offhand;  //b 2
	Object *ranged;   //c 3
	Object *light;    //d 4
	Object *armor;    //e 5
	Object *helmet;   //f 6
	Object *cloak;    //g 7
	Object *gloves;   //h 8
	Object *boots;    //i 9
	Object *amulet;   //j 10
	Object *ring1;    //k 11
	Object *ring2; */ //l 12 total
	
}; 

class NPC: public Character
{
	public:
	int characteristics;
	int lastLocation;
	Dice hpDice;
	Dice speedDice;
	int isSpawned;
	int hasDied;
	int color; 
	// 0 BLACK
	// 1 RED
	// 2 GREEN
	// 3 YELLOW
	// 4 BLUE
	// 5 MAGENTA
	// 6 CYAN
	// 7 WHITE
	std::string name;
	std::string desc;
	
};

class Cell;

#include "dungeon.h"

void initMonsters(int numMonsters, int *characterL, int *characterIni, std::vector<NPC *> &characterMap, 
	Cell dungeon[][80], int *rooms, Room *allRooms, std::vector<NPC *> &npcTemplates);
void initObjects(int *objectL, int *objectIni, std::vector<Object *> &objectMap, 
	Cell dungeon[][80], int *rooms, Room *allRooms, std::vector<Object *> &objectTemplates);
int canSee(int i, int *characterL, Cell dungeon[][80]);
int parseMonsters(std::ifstream &f, std::vector<NPC *> &npcTemplates);
int parseObjects(std::ifstream &f, std::vector<Object *> &objectTemplates);

#endif