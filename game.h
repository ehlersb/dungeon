#ifndef GAME_H
#define GAME_H

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
#include <algorithm>

#include "dungeon.h"
#include "character.h"
#include "queue.h"

void simulateGame(int numMonsters, int *characterL, int *characterIni, 
					std::vector<NPC *> &characterMap, int *objectL, int *objectIni, 
					std::vector<Object *> &objectMap, Cell dungeon[][80], int *rooms, Room allRooms[], 
					int *stairsL, std::vector<NPC *> &npcTemplates, std::vector<Object *> &objectTemplates, PC *pc);
					
int moveCharacter(Queue *q, int direction, int location, int numMonsters, 
					int *curMonsters, int *characterL, int *characterIni, 
					std::vector<NPC *> &characterMap, Cell dungeon[][80], int *stairsL, 
					unsigned int spongeBobIndex, std::vector<NPC *> &npcTemplates, PC *pc, 
					int *objectIni, int *objectL, std::vector<Object *> &objectMap);
					
int teleportCharacter(Queue *q, int destination, int location, int numMonsters, 
						int *curMonsters, int *characterL, int *characterIni, 
						std::vector<NPC *> &characterMap, Cell dungeon[][80], int *stairsL, 
						unsigned int spongeBobIndex, std::vector<NPC *> &npcTemplates, PC *pc, 
						int *objectIni, int *objectL, std::vector<Object *> &objectMap);
int getMoveLiteral(int d);
#endif