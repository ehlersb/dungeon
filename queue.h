#ifndef QUEUE_H
#define QUEUE_H

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

#include "graph.h"
#include "dungeon.h"
#include "character.h"

class Node {
	public:
	int dist; //priority
	int location;
	struct Node *next;
	struct Node *prev;
};

class Queue {
	public:
	int size;
	Node *head, *tail;
};

int queueInit(Queue *q);
int queueDelete(Queue *q);
/*int queueAdd(Queue *q, int v, int d);*/
int queueRemove(Queue *q, int *d, int *l);
int queueRemoveEvent(Queue *q, int l);
int decreasePriority(Queue *q, int location, int d);
int decreasePriorityEvent(Queue *q, int location, int d); // where d is priority to subtract from Node
int addWithPriority(Queue *q, int location, int d);
int extractMin(Queue *q);
int extractMinEvent(Queue *q, int sequences[], int *p);
void dijkstraNormal(Cell dungeon[][80], int source, char *normalWeightMap);
void dijkstraTunneling(Cell dungeon[][80], int source, char *normalWeightMap);
/*int peek(Queue *q, int *v);*/
//int size(Queue *q);

#endif