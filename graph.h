#ifndef GRAPH_H
#define GRAPH_H

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

#include "dungeon.h"

int initNeighbors(Cell dungeon[][80], int numNeighbors, int location, int *neighbors);
int calculateNumNeighbors(Cell dungeon[][80], int location);
int initNeighborsTunneling(int numNeighbors, int location, int *neighbors);
#endif