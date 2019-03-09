#include "dungeon.h"
using namespace std;
unsigned long long rdtsc(){
	unsigned int lo,hi;
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	return ((unsigned long long)hi << 32) | lo;
}

void dungeonInit(Cell dungeon[21][80])
{
	
	//init outer edge, 255 hardness, immutable , - and | are the graphics
	for(int i = 0; i < 80; i++) // horizontal
	{
		dungeon[0][i].hardness = dungeon[20][i].hardness = 255;
		dungeon[0][i].graphic = dungeon[20][i].graphic = ' ';		
		dungeon[0][i].isRoom = dungeon[20][i].isRoom = 0;	
		dungeon[0][i].isLit = dungeon[20][i].isLit = 0;	
		dungeon[0][i].hasSeen = dungeon[20][i].hasSeen = 0;	
		dungeon[0][i].objectNum = dungeon[20][i].objectNum = -1;	
	}
	for(int i = 1; i < 20; i++) // vertical
	{
		dungeon[i][0].hardness = dungeon[i][79].hardness = 255;
		dungeon[i][0].graphic = dungeon[i][79].graphic = ' ';
		dungeon[i][0].isRoom = dungeon[i][79].isRoom = 0;
		dungeon[i][0].isLit = dungeon[i][79].isLit = 0;	
		dungeon[i][0].hasSeen = dungeon[i][79].hasSeen = 0;	
		dungeon[i][0].objectNum = dungeon[i][79].objectNum = -1;	
	}
	// init the rest
	for(int i = 1; i < 20;i++)
	{
		for(int j = 1; j < 79;j++)
		{
			/*int r = (rand() % 176) + 1;
			if (r > 84) 
			{
				r = (rand() % 176) + 1;
			}*/
			dungeon[i][j].hardness = 100;
			dungeon[i][j].graphic = ' ';
			dungeon[i][j].isRoom = 0;
			dungeon[i][j].isLit = 0;	
			dungeon[i][j].hasSeen = 0;	
			dungeon[i][j].objectNum = -1;
		}
	}
}

int isValidLocation(int x, int y, int i, Room allRooms[]) // makes sure Room doesn't overrite another
{
	
	for (int j = 0; i - j != 0; j++)
	{
		if(abs((allRooms[j].posx+4) - (x+4)) < 9 && abs((allRooms[j].posy+2) - (y+2)) < 6) // if location that we're testing is within Room space limit
		{
			return 1;
		}
		/*if(abs((allRooms[j].posx) - x) < 4) {
			return 1;
		}
		if(abs((allRooms[j].posy) - y) < 4) {
			return 1;
		} */
	}
	return 0;
}

void generateRooms(Cell dungeon[][80], int *rooms, Room allRooms[])
{
	for(int i = 0; i < *rooms;)
	{
		int x = (rand() % 71 ) + 1;
		int y = (rand() % 15) + 1;
		if(isValidLocation(x, y, i, allRooms) == 0) 
		{
			allRooms[i].connected = 1;
			allRooms[i].posx = x;
			allRooms[i].posy = y;
			int sizex = allRooms[i].sizex = (rand() % 6) + 3;
			int sizey = allRooms[i].sizey = (rand() % 4) + 2;
			
			for(int j = 0; j < sizey; j++) 
			{
				for(int k = 0; k < sizex; k++) 
				{
					dungeon[y + j][x + k].hardness = 0;
					dungeon[y + j][x + k].graphic = '.';
					dungeon[y + j][x + k].isRoom = 1;
				}
			}
			i++;
		}
		
	}
	connectRooms(dungeon, rooms, allRooms);
}

void connectRooms(Cell dungeon[][80], int *rooms, Room allRooms[])
{
	for(int i = 0; i < *rooms - 1;i++)
	{
		int tempx = allRooms[i].posx;
		int tempy = allRooms[i].posy;
		int nextx = allRooms[i+1].posx;
		int nexty = allRooms[i+1].posy;
		int j = 0;
		int k = 0;
		if (tempx < nextx) 
		{ // if path needs to go right

			for(; tempx + j != nextx; j++) {
				if (dungeon[tempy][tempx + j].graphic == ' ') 
				{	
					dungeon[tempy][tempx + j].graphic = '#';
					dungeon[tempy][tempx + j].hardness = 0;
				}
			}
			
		}
		
		else if (tempx > nextx) 
		{ // if path needs to go left
			
			for(; tempx + j != nextx; j--) 
			{
				if (dungeon[tempy][tempx + j].graphic == ' ') 
				{	
					dungeon[tempy][tempx + j].graphic = '#';
					dungeon[tempy][tempx + j].hardness = 0;
				}
			}
			
		}
		
		if (tempy < nexty) 
		{ // if path needs to go down
			
			for(; tempy + k != nexty; k++) {
				if (dungeon[tempy + k][tempx + j].graphic == ' ') 
				{	
					dungeon[tempy + k][tempx + j].graphic = '#';
					dungeon[tempy + k][tempx + j].hardness = 0;
				}
			}
		}
		else if (tempy > nexty) 
		{ // if path needs to go up
			
			for(; tempy - k != nexty; k++) {
				if (dungeon[tempy - k][tempx + j].graphic == ' ') 
				{	
					dungeon[tempy - k][tempx + j].graphic = '#';
					dungeon[tempy - k][tempx + j].hardness = 0;
				}
			}
		}
		allRooms[i].connected = allRooms[i+1].connected = 0;
	}
}
int writeDungeon(char *filepath, int *version, Cell dungeon[21][80], int *rooms, Room *allRooms)
{	
	FILE *f;
	f = fopen(filepath,"w");	
	char semantic[6] = "RLG32";
	unsigned int size = 1694 + (*rooms * 4);
	unsigned char *dun = (unsigned char *) malloc(1680);
	int sizeRoomBlock = size - 1694;
	unsigned char *roomArr = (unsigned char *) malloc(sizeRoomBlock);
	unsigned int temp;
	for (int i = 0; i < 21;i++) 
	{
		for(int j = 0; j < 80;j++)
		{
			*(dun + j + (i*80)) = dungeon[i][j].hardness;
		}
	}
	
	
	
	for(int i = 0; i < sizeRoomBlock/4;i++) //give file data block of rooms local data of rooms
	{
		
		*(roomArr + (i*4) + 0) = allRooms[i].posy;
		*(roomArr + (i*4) + 1) = allRooms[i].posx;
		*(roomArr + (i*4) + 2) = allRooms[i].sizey;
		*(roomArr + (i*4) + 3) = allRooms[i].sizex;
	}
	fwrite(semantic, 1,6,f);
	temp = htobe32(*version);
	fwrite(&temp,1,4,f);
	temp = htobe32(size);
	fwrite(&temp,1,4,f);
	fwrite(dun,1,1680,f);
	fwrite(roomArr, 1, sizeRoomBlock,f);
	free(roomArr);
	free(dun);
	fclose(f);
	return 0;
}

int loadDungeon(char *filepath, int *version, Cell dungeon[][80], int *rooms, Room *allRooms)
{
	
	FILE *f;
	f = fopen(filepath,"r");
	char semantic[6];
	unsigned int size;
	unsigned char *dun = (unsigned char *) malloc(1680);
	unsigned int temp;
	
	fread(semantic, 1,6,f);
	fread(&temp,1,4,f);
	*version = be32toh(temp);
	fread(&temp,1,4,f);
	size = be32toh(temp);
	fread(dun,1,1680,f);
	int sizeRoomBlock = size - 1694;
	*rooms = (sizeRoomBlock/4);
	unsigned char *roomArr = (unsigned char *) malloc(sizeRoomBlock);
	
	fread(roomArr, 1, sizeRoomBlock,f);
	
	
	for(int i = 0; i < 21; i++) 
	{
		for(int j = 0; j < 80; j++) 
		{
			dungeon[i][j].hardness = dun[j + (i*80)];
			dungeon[i][j].graphic = ' ';
			
		}
	}
	
	
	for(int i = 0; i < sizeRoomBlock/4;i++)
	{
		
		allRooms[i].posy = *(roomArr + (i*4) + 0);
		allRooms[i].posx = *(roomArr + (i*4) + 1);
		allRooms[i].sizey = *(roomArr + (i*4) + 2);
		allRooms[i].sizex = *(roomArr + (i*4) + 3);
		allRooms[i].connected = 0;
	}
	loadRooms(dungeon, rooms, allRooms);
	loadCorridors(dungeon);
	fclose(f);
	free(dun);
	free(roomArr);
	return 0;
}
int loadRooms(Cell dungeon[][80], int *rooms, Room *allRooms) //specifically for loaded dungeons
{
	for(int i = 0; i < *rooms ;i++)
	{
		int roomx = allRooms[i].posx;
		int roomy = allRooms[i].posy;
		int sizex = allRooms[i].sizex;
		int sizey = allRooms[i].sizey;
		for(int j = 0; j < sizey; j++)
		{
			for (int k = 0; k < sizex; k++)
			{
				dungeon[roomy + j][roomx + k].graphic = '.';
			}
		}
	}
	return 0;
}

int loadCorridors(Cell dungeon[][80]) //specifically for loaded dungeons
{ 
	for (int i = 1; i < 20; i++)
	{
		for (int j = 1; j < 79; j++)
		{
			if(dungeon[i][j].hardness == 0 && dungeon[i][j].graphic == ' ')
			{
				dungeon[i][j].graphic = '#';
			}
		}
	}
	return 0;
}

int loadStairs(Cell dungeon[][80], int *rooms, Room *allRooms, int *stairsL)
{
	int rRoom = rand() % (*rooms);
	int baseX = allRooms[rRoom].posx;
	int baseY = allRooms[rRoom].posy;
	int rOffsetX = (rand() % allRooms[rRoom].sizex);
	int rOffsetY = (rand() % allRooms[rRoom].sizey);
	int rPosX = baseX + rOffsetX;
	int rPosY = baseY + rOffsetY;
	while(dungeon[rPosY][rPosX].graphic != '.') 
	{
		rRoom = rand() % (*rooms);
		baseX = allRooms[rRoom].posx;
		baseY = allRooms[rRoom].posy;
		rOffsetX = (rand() % allRooms[rRoom].sizex);
		rOffsetY = (rand() % allRooms[rRoom].sizey);
		rPosX = baseX + rOffsetX;
		rPosY = baseY + rOffsetY;
	}
	
	dungeon[rPosY][rPosX].graphic = '>';	
	stairsL[0] = (rPosY * 80) + (rPosX);
	
	rRoom = rand() % (*rooms);
	baseX = allRooms[rRoom].posx;
	baseY = allRooms[rRoom].posy;
	rOffsetX = (rand() % allRooms[rRoom].sizex);
	rOffsetY = (rand() % allRooms[rRoom].sizey);
	rPosX = baseX + rOffsetX;
	rPosY = baseY + rOffsetY;
	
	while(dungeon[rPosY][rPosX].graphic != '.') 
	{
		rRoom = rand() % (*rooms);
		baseX = allRooms[rRoom].posx;
		baseY = allRooms[rRoom].posy;
		rOffsetX = (rand() % allRooms[rRoom].sizex);
		rOffsetY = (rand() % allRooms[rRoom].sizey);
		rPosX = baseX + rOffsetX;
		rPosY = baseY + rOffsetY;
	}
	dungeon[rPosY][rPosX].graphic = '<';
	stairsL[1] = (rPosY * 80) + (rPosX);
	return 0;
}

void display(Cell dungeon[][80], int *characterIni, int *characterL,  vector<NPC *> &characterMap, int *objectIni, vector<Object *> &objectMap) 
{
	chtype x;
	for(int i = 0; i < 21;i++)
	{
		for(int j = 0; j < 80;j++)
		{
			int attronMon = 0;
			int attronObj = 0;
			x = dungeon[i][j].graphic;
			if(dungeon[i][j].graphic == '@' || dungeon[i][j].graphic == '<' || dungeon[i][j].graphic == '>')
				;
			else if(characterIni[(i * 80) + j] && (((i*80) + j) != characterL[0]))
			{
				attron(COLOR_PAIR(characterMap[(i*80) + j]->color));
				attronMon = 1;
			}
			else if(objectIni[(i*80) + j])
			{
				attron(COLOR_PAIR(objectMap[(i*80) + j]->color));
				attronObj = 1;
			}
			mvaddch(i + 1,j, x); // must be drawn 1 - 21 in 0 indexed 24 pixel tall prompt
			if(attronMon)
				attroff(COLOR_PAIR(characterMap[(i*80) + j]->color));
			else if(attronObj)
				attroff(COLOR_PAIR(objectMap[(i*80) + j]->color));
		}
	}
}

void displayFog(Cell dungeon[][80], int *stairsL, int *characterIni, int *characterL, vector<NPC *> &characterMap, int *objectIni, vector<Object *> &objectMap)
{
	chtype x;
	for(int i = 0; i < 21;i++)
	{
		for(int j = 0; j < 80;j++)
		{
			if(dungeon[i][j].isLit)
			{
				int attronMon = 0;
				int attronObj = 0;
				x = dungeon[i][j].graphic;
				if(x == '@' || x == '<' || x == '>')
					;
				else if(characterIni[(i * 80) + j] && (((i*80) + j) != characterL[0]))
				{
					attron(COLOR_PAIR(characterMap[(i*80) + j]->color));
					attronMon = 1;
				}
				else if(objectIni[(i*80) + j])
				{
					attron(COLOR_PAIR(objectMap[(i*80) + j]->color));
					attronObj = 1;
				}
				mvaddch(i + 1,j, x); // must be drawn 1 - 21 in 0 indexed 24 pixel tall prompt
				if(attronMon)
					attroff(COLOR_PAIR(characterMap[(i*80) + j]->color));
				else if(attronObj)
					attroff(COLOR_PAIR(objectMap[(i*80) + j]->color));
			}
			else if(dungeon[i][j].hasSeen)
			{
				if(dungeon[i][j].hardness == 0)
				{
					if(dungeon[i][j].isRoom)
					{
						if(stairsL[0] == ((i*80) + j))
						{
							x = '>';
						}
						else if(stairsL[1] == ((i*80) + j))
						{
							x = '<';
						}
						else
						{
							x = '.';
							
						}	
						mvaddch(i + 1,j, x);
					}
					else
					{											
						x = '#';
						mvaddch(i + 1,j, x);
					}
				}
				else
				{
					x = ' ';
					mvaddch(i + 1, j, x);
				}
			}
			else
			{
				x = ' ';
				mvaddch(i + 1, j, x);
			}
		}
	}
}


void displayHardness(Cell dungeon[][80])
{
	for(int i = 0; i < 21;i++)
	{
		for(int j = 0; j < 80;j++)
		{
			printf("%d", dungeon[i][j].hardness);
		}
		printf("\n");
	}
}

void displayPathing(char *normalWeightMap)
{
	for(int i = 0; i < 21;i++)
	{
		for(int j = 0; j < 80; j++)
		{
			printf("%c",normalWeightMap[(i*80) + j]);
		}
		
		printf("\n");
	}
}

int spawnCharacter(Cell dungeon[][80], int *rooms, Room allRooms[])
{
	int rRoom = rand() % (*rooms);
	int baseX = allRooms[rRoom].posx;
	int baseY = allRooms[rRoom].posy;
	int rOffsetX = (rand() % allRooms[rRoom].sizex);
	int rOffsetY = (rand() % allRooms[rRoom].sizey);
	int rPosX = baseX + rOffsetX;
	int rPosY = baseY + rOffsetY;
	dungeon[rPosY][rPosX].graphic = '@';
	return (rPosY * 80) + rPosX;
}