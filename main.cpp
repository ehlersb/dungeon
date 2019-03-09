#include "dungeon.h"
#include "queue.h"
#include "character.h"
#include "game.h"

using namespace std;

int main (int argc, char* argv[])
{
	/*int length;
	length = strlen(getenv("HOME"));
	length+=strlen("/.rlg327/dungeon/")+1;
	char *filepath = (char *) malloc(length);
	strcpy(filepath,getenv("HOME"));
	strcat(filepath, "/.rlg327/dungeon"); 	//define filepath*/

	int length1;
	length1 = strlen(getenv("HOME"));
	length1+=strlen("/.rlg327/monster_desc.txt/")+1;
	char *filepathMonsters = (char *) malloc(length1);
	strcpy(filepathMonsters,getenv("HOME"));
	strcat(filepathMonsters, "/.rlg327/monster_desc.txt"); 	//define filepath
	
	int length2;
	length2 = strlen(getenv("HOME"));
	length2+=strlen("/.rlg327/object_desc.txt/")+1;
	char *filepathObjects = (char *) malloc(length2);
	strcpy(filepathObjects,getenv("HOME"));
	strcat(filepathObjects, "/.rlg327/object_desc.txt"); 	//define filepath
	
	int length3;
	length3 = strlen(getenv("HOME"));
	length3+=strlen("/.rlg327/dungeon/")+1;
	char *filepathSave = (char *) malloc(length3);
	strcpy(filepathSave,getenv("HOME"));
	strcat(filepathSave, "/.rlg327/dungeon"); 	//define filepath

	srand(rdtsc());//srand(1);							//seed rand
	int *version = (int *) malloc(sizeof(int));
	Cell dungeon[21][80];
	
	initscr();
	raw();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	set_escdelay(100);
	start_color();
	init_pair(COLOR_BLACK, COLOR_WHITE, COLOR_BLACK); //0
	init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK); //1
	init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK); //2
	init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK); //3
	init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK); //4
	init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK); //5
	init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK); //6
	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK); //7
	
	
	if (argc > 3)
	{
		fprintf(stderr, "Wrong number of paramenters\n");
		free(filepathSave);
		free(filepathObjects);
		free(filepathMonsters);
		free(version);
		return -1;
	}	
	/*else if(argc == 2) //if 1 arg 
	{
		if(!strcmp(argv[1], "--save")) //DISPLAY AND SAVE NEW DUNGEON
		{
			*version = 0;
			int *rooms = (int *) malloc(sizeof(int));
			*rooms = ((rand() % 3) + 5);
			Room *allRooms = (Room *) malloc((*rooms) * sizeof(Room));
			dungeonInit(dungeon);
			generateRooms(dungeon, rooms, allRooms);
			writeDungeon(filepathSave, version, dungeon, rooms, allRooms);
			display(dungeon);
			free(version);
			free(rooms);
			free(allRooms);
			free(filepathSave);
			free(filepathObjects);
			free(filepathMonsters);
			return 0;	
		}
		else if(!strcmp(argv[1], "--load")) //LOAD DUNGEON, DISPLAY IT
		{	
			*version = 0;
			int *rooms = (int *) malloc(sizeof(int));
			*rooms = 7;
			Room *allRooms = (Room *) malloc((*rooms) * sizeof(Room));
			loadDungeon(filepathSave, version, dungeon, rooms, allRooms);
			display(dungeon);
			free(version);
			free(rooms);
			free(allRooms);
			free(filepathSave);
			free(filepathObjects);
			free(filepathMonsters);
			return 0;
		}
		else 
		{
			fprintf(stderr, "Bad argument format\n");
			free(version);
			free(filepathSave);
			free(filepathObjects);
			free(filepathMonsters);
			endwin();
			return -1;
		}
	}
	else if(argc == 3 && 
			((!strcmp(argv[1], "--save") && !strcmp(argv[2], "--load")) || 
				(!strcmp(argv[1], "--load") && !strcmp(argv[2], "--save")))) //LOAD DUNGEON, DISPLAY IT, SAVE IT ON ITSELF
	{
		*version = 0;
		int *rooms = (int *) malloc(sizeof(int));
		*rooms = 7;
		Room *allRooms = (Room *) malloc((*rooms) * sizeof(Room));
		loadDungeon(filepathSave, version, dungeon, rooms, allRooms);
		display(dungeon);
		writeDungeon(filepathSave, version, dungeon, rooms, allRooms);
		free(version);
		free(rooms);
		free(allRooms);
		free(filepathSave);
		free(filepathObjects);
		free(filepathMonsters);
		return 0;
	}*/
	else if(argc == 3 && !strcmp(argv[1], "--nummon"))
	{
		
		
		ifstream f;
		vector<NPC *> npcTemplates;
		vector<Object *> objectTemplates;
		f.open(filepathMonsters);
		parseMonsters(f, npcTemplates);
		f.close();
		f.open(filepathObjects);
		parseObjects(f, objectTemplates);
		f.close();
		
		int numMonsters = atoi(argv[2]);
		*version = 0;
		int *rooms = (int *) malloc(sizeof(int));
		*rooms = ((rand() % 3) + 5);
		Room *allRooms = (Room *) malloc((*rooms) * sizeof(Room));
		int *stairsL = (int *) malloc(2 * sizeof(int));
		dungeonInit(dungeon);
		generateRooms(dungeon, rooms, allRooms); 
		int source = spawnCharacter(dungeon, rooms, allRooms);
		loadStairs(dungeon, rooms, allRooms, stairsL);
		int *characterL = (int *) malloc((numMonsters + 1) * sizeof(int));
		int *characterIni = (int *) malloc(1680 * sizeof(int));
		for (int i = 0; i < 1680;i++)
		{
			characterIni[i] = 0;
		}
		
		int *objectL = (int *) malloc((NUMBER_OF_OBJECTS + 21) * sizeof(int));
		int *objectIni = (int *) malloc(1680 * sizeof(int));
		for (int i = 0; i < NUMBER_OF_OBJECTS + 21; i++)
		{
			objectL[i] = 0;
		}
		for (int i = 0; i < 1680; i++)
		{
			objectIni[i] = 0;
		}

		int tx = (source % 80) - 2;
		int ty = (source / 80) - 2;
		for (int i = 0; i < 5; i++) // 5x5 area is now lit
		{
			for (int j = 0; j < 5; j++)
			{
				if(((tx+j) > 0) && ((tx+j) < 79) && ((ty+i) < 20) && ((ty+i) > 0))
					{
						dungeon[ty + i][tx + j].isLit = 1;
						if(dungeon[ty + i][tx + j].hardness == 0)
							dungeon[ty + i][tx + j].hasSeen = 1;
					}
			}
		}
		vector<Object *> objectMap(1680);
		vector<NPC *> characterMap(1680);
		PC *pc = new PC();
		pc->symbol = '@';
		pc->speed = 10;
		pc->sequence = 0;
		pc->hp = 100;
		characterL[0] = source;
		characterIni[characterL[0]] = 1; 
		initMonsters(numMonsters, characterL, characterIni, characterMap, 
					dungeon, rooms, allRooms, npcTemplates);
		initObjects(objectL, objectIni, objectMap, 
					dungeon, rooms, allRooms, objectTemplates);
		simulateGame(numMonsters, characterL, characterIni, characterMap, objectL, objectIni, objectMap,
					dungeon, rooms, allRooms, stairsL, npcTemplates, objectTemplates, pc);
			
		for(unsigned int k = 0; k < npcTemplates.size(); k++)
		{
			free(npcTemplates[k]);
		}
		for(unsigned int k = 0; k < objectTemplates.size(); k++)
		{
			free(objectTemplates[k]);
		}
		
		f.close();
		free(filepathSave);
		free(filepathObjects);
		free(filepathMonsters);
		free(version);
		return 0;
		
	}
	else if (argc == 3) 
	{
		fprintf(stderr, "Bad argument format\n");
		endwin();
		free(version);
		free(filepathSave);
		free(filepathObjects);
		free(filepathMonsters);
		return -1;
	}
	else //GENERATE AND DISPLAY DUNGEON AS NORMAL
	{
		
		ifstream f;
		vector<NPC *> npcTemplates;
		vector<Object *> objectTemplates;
		f.open(filepathMonsters);
		parseMonsters(f, npcTemplates);
		f.close();
		f.open(filepathObjects);
		parseObjects(f, objectTemplates);
		f.close();
	
		int numMonsters = ((rand() % 14) + 8);
		*version = 0;
		int *rooms = (int *) malloc(sizeof(int));
		*rooms = ((rand() % 3) + 5);
		Room *allRooms = (Room *) malloc((*rooms) * sizeof(Room));
		int *stairsL = (int *) malloc(2 * sizeof(int));
		dungeonInit(dungeon);
		generateRooms(dungeon, rooms, allRooms); 
		int source = spawnCharacter(dungeon, rooms, allRooms);
		loadStairs(dungeon, rooms, allRooms, stairsL);
		int *characterL = (int *) malloc((numMonsters + 1) * sizeof(int));
		int *characterIni = (int *) malloc(1680 * sizeof(int));
		for (int i = 0; i < 1680;i++)
		{
			characterIni[i] = 0;
		}
		
		int *objectL = (int *) malloc((NUMBER_OF_OBJECTS + 21) * sizeof(int));
		int *objectIni = (int *) malloc(1680 * sizeof(int));
		for (int i = 0; i < NUMBER_OF_OBJECTS + 21; i++)
		{
			objectL[i] = 0;
		}
		for (int i = 0; i < 1680; i++)
		{
			objectIni[i] = 0;
		}

		int tx = (source % 80) - 2;
		int ty = (source / 80) - 2;
		for (int i = 0; i < 5; i++) // 5x5 area is now lit
		{
			for (int j = 0; j < 5; j++)
			{
				if(((tx+j) > 0) && ((tx+j) < 79) && ((ty+i) < 20) && ((ty+i) > 0))
					{
						dungeon[ty + i][tx + j].isLit = 1;
						if(dungeon[ty + i][tx + j].hardness == 0)
							dungeon[ty + i][tx + j].hasSeen = 1;
					}
			}
		}
		
		vector<Object *> objectMap(1680);
		vector<NPC *> characterMap(1680);
		PC *pc = new PC();
		pc->symbol = '@';
		pc->speed = 10;
		pc->sequence = 0;
		pc->hp = 100;
		for(int i = 0; i < 12; i++)
		{
			pc->equipment.push_back(new Object());
		}
		
		characterL[0] = source;
		characterIni[characterL[0]] = 1; 
		initMonsters(numMonsters, characterL, characterIni, characterMap, 
					dungeon, rooms, allRooms, npcTemplates);
		initObjects(objectL, objectIni, objectMap, 
					dungeon, rooms, allRooms, objectTemplates);
		simulateGame(numMonsters, characterL, characterIni, characterMap, objectL, objectIni, objectMap,
					dungeon, rooms, allRooms, stairsL, npcTemplates, objectTemplates, pc);
			
		for(unsigned int k = 0; k < npcTemplates.size(); k++)
		{
			delete npcTemplates[k];
		}
		for(unsigned int k = 0; k < objectTemplates.size(); k++)
		{
			delete objectTemplates[k];
		}
		
		free(filepathSave);
		free(filepathObjects);
		free(filepathMonsters);
		free(version);
		return 0;
	}
	return 0;
}
