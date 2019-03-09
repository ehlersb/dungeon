#include "graph.h"
int calculateNumNeighbors(Cell dungeon[][80], int location) 
{
	int numNeighbors = 0;
	
	int x = location % 80;
	int y = location / 80;
	if(dungeon[y+1][x].hardness == 0)
	{
		numNeighbors++;		
	}
	if(dungeon[y-1][x].hardness == 0)
	{
		numNeighbors++;
	}
	if(dungeon[y][x+1].hardness == 0)
	{
		numNeighbors++;
	}
	if(dungeon[y][x-1].hardness == 0)
	{
		numNeighbors++;
	}
	if(dungeon[y-1][x-1].hardness == 0)
	{
		numNeighbors++;
	}
	if(dungeon[y-1][x+1].hardness == 0)
	{
		numNeighbors++;
	}
	if(dungeon[y+1][x-1].hardness == 0)
	{
		numNeighbors++;
	}
	if(dungeon[y+1][x+1].hardness == 0)
	{
		numNeighbors++;
	}
	return numNeighbors;
}
int initNeighbors(Cell dungeon[][80], int numNeighbors, int location, int *neighbors)
{
	int j = 0;
	int x = location % 80;
	int y = location / 80;
	if(dungeon[y][x-1].hardness == 0)
	{
		if(j == numNeighbors) 
		{
			return 0;
		}
		neighbors[j++] = location - 1;
		
	}
	if(dungeon[y][x+1].hardness == 0)
	{
		if(j == numNeighbors) 
		{
			return 0;
		}
		neighbors[j++] = location + 1;	
		
	}
	if(dungeon[y-1][x].hardness == 0)
	{
		if(j == numNeighbors) 
		{
			return 0;
		}
		neighbors[j++] = location - 80;
		
	}
	if(dungeon[y+1][x].hardness == 0)
	{
		if(j == numNeighbors) 
		{
			return 0;
		}
		neighbors[j++] = location + 80;
		
	}		
	if(dungeon[y-1][x-1].hardness == 0)
	{
		if(j == numNeighbors) 
		{
			return 0;
		}
		neighbors[j++] = location - 81;
		
	}
	if(dungeon[y-1][x+1].hardness == 0)
	{
		if(j == numNeighbors) 
		{
			return 0;
		}
		neighbors[j++] = location - 79;
		
	}
	if(dungeon[y+1][x-1].hardness == 0)
	{
		if(j == numNeighbors) 
		{
			return 0;
		}
		neighbors[j++] = location + 79;
		
	}
	if(dungeon[y+1][x+1].hardness == 0)
	{
		if(j == numNeighbors) 
		{
			return 0;
		}
		neighbors[j++] = location + 81;
		
	}
	return 0;
}

int initNeighborsTunneling(int numNeighbors, int location, int *neighbors)
{	
	
	neighbors[0] = location - 1;
	
	neighbors[1] = location - 81;
	
	neighbors[2] = location - 80;
	
	neighbors[3] = location - 79;
	
	neighbors[4] = location + 1;
	
	neighbors[5] = location + 81;
	
	neighbors[6] = location + 80;
	
	neighbors[7] = location + 79;
	
	
	return 0;
}