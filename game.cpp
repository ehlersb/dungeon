#include "game.h"
using namespace std;
void simulateGame(int numMonsters, int *characterL, int *characterIni, 
					vector<NPC *> &characterMap, int *objectL, int *objectIni, 
					vector<Object *> &objectMap, Cell dungeon[][80], int *rooms, Room allRooms[], 
					int *stairsL, vector<NPC *> &npcTemplates, vector<Object *> &objectTemplates, PC *pc)
{
	unsigned int spongeBobIndex;
	for(unsigned int k = 0; k < npcTemplates.size(); k++)
	{
		if(npcTemplates[k]->name == "SpongeBob SquarePants")
		{
			spongeBobIndex = k;
			break;
		}
	}
	
	int fogON = 1;
	int n = numMonsters;
	int *curMonsters = (int *)malloc(sizeof(int));
	*curMonsters = n;
	char *normalWeightMap = (char *)malloc(1680 * sizeof(char));
	char *tunnelWeightMap = (char *)malloc(1680 * sizeof(char));

	int moveNum = 0;

	dijkstraNormal(dungeon, characterL[0], normalWeightMap);

	dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);

	int r;
	int r1;
	int inputQuit = 0;
	Queue *q = (Queue *)malloc(sizeof(Queue));
	queueInit(q);
	for (int i = 0; i < numMonsters + 1; i++)
	{
		addWithPriority(q, characterL[i], 0);
	}
	clear();
	displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
	refresh();
	while (characterIni[characterL[0]] && !(npcTemplates[spongeBobIndex]->hasDied)) //pc is not null (true)
	{
		int usedStairs = 0;
		r1 = rand() % 1000;
		if (r1 < 500)
		{
			r = 1;
		}
		else
		{
			r = 0;
		}
		
		int sequences[1680];
		for (int i = 0; i < numMonsters + 1; i++)
		{
			if(characterIni[characterL[i]])
			{
				if(characterL[i] != characterL[0])
				{
					sequences[characterL[i]] = characterMap[characterL[i]]->sequence;
				}
				else
				{
					sequences[characterL[i]] = pc->sequence;
				}
			}
		}
		
		
		moveNum++;
		int *p = (int *)malloc(sizeof(int));
		int u = extractMinEvent(q, sequences, p); //extract min
		int uX = u % 80;
		int uY = u / 80;
		int cur = 0;
		for (int i = 0; i < numMonsters + 1; i++)
		{
			decreasePriorityEvent(q, characterL[i], *p);
		}

		if ((u == characterL[0])) //pc move
		{
			int moveMade = 0;
			while (!moveMade)
			{
				int inputK = getch();
				switch (inputK)
				{
				case '7':
				{
					if (dungeon[uY - 1][uX - 1].hardness == 0)
					{
						moveCharacter(q, 8, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case 'y':
				{
					if (dungeon[uY - 1][uX - 1].hardness == 0)
					{
						moveCharacter(q, 8, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case '8':
				{
					if (dungeon[uY - 1][uX].hardness == 0)
					{
						moveCharacter(q, 1, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case 'k':
				{
					if (dungeon[uY - 1][uX].hardness == 0)
					{
						moveCharacter(q, 1, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case '9':
				{
					if (dungeon[uY - 1][uX + 1].hardness == 0)
					{
						moveCharacter(q, 2, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case 'u':
				{
					if (dungeon[uY - 1][uX + 1].hardness == 0)
					{
						moveCharacter(q, 2, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case '6':
				{
					if (dungeon[uY][uX + 1].hardness == 0)
					{
						moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case 'l':
				{
					if (dungeon[uY][uX + 1].hardness == 0)
					{
						moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case '3':
				{
					if (dungeon[uY + 1][uX + 1].hardness == 0)
					{
						moveCharacter(q, 4, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case 'n':
				{
					if (dungeon[uY + 1][uX + 1].hardness == 0)
					{
						moveCharacter(q, 4, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case '2':
				{
					if (dungeon[uY + 1][uX].hardness == 0)
					{
						moveCharacter(q, 5, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case 'j':
				{
					if (dungeon[uY + 1][uX].hardness == 0)
					{
						moveCharacter(q, 5, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case '1':
				{
					if (dungeon[uY + 1][uX - 1].hardness == 0)
					{
						moveCharacter(q, 6, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case 'b':
				{
					if (dungeon[uY + 1][uX - 1].hardness == 0)
					{
						moveCharacter(q, 6, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case '4':
				{
					if (dungeon[uY][uX - 1].hardness == 0)
					{
						moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case 'h':
				{
					if (dungeon[uY][uX - 1].hardness == 0)
					{
						moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						moveMade = 1;
					}
					break;
				}
				case '>':
				{
					if (stairsL[0] == u)
					{
						for (int i = 1; i < numMonsters + 1; i++)
						{
							if (characterIni[characterL[i]])
							{
								delete characterMap[characterL[i]];
								characterIni[characterL[i]] = 0;
							}
						}
						for (int i = 0; i < NUMBER_OF_OBJECTS + 21; i++)
						{
							if (objectIni[objectL[i]])
							{
								delete objectMap[objectL[i]];
								objectIni[objectL[i]] = 0;
							}
						}
						free(objectIni);
						free(objectL);
						free(characterIni);
						free(characterL);
						free(stairsL);
						free(rooms);
						free(allRooms);

						moveMade = 1;
						usedStairs = 1;

						*curMonsters = numMonsters = ((rand() % 16) + 4);
		
						rooms = (int *) malloc(sizeof(int));
						*rooms = ((rand() % 3) + 5);
						allRooms = (Room *) malloc((*rooms) * sizeof(Room));
						stairsL = (int *) malloc(2 * sizeof(int));
						dungeonInit(dungeon);
						generateRooms(dungeon, rooms, allRooms); 
						int source = spawnCharacter(dungeon, rooms, allRooms);
						loadStairs(dungeon, rooms, allRooms, stairsL);
						characterL = (int *) malloc((numMonsters + 1) * sizeof(int));
						characterIni = (int *) malloc(1680 * sizeof(int));
						for (int i = 0; i < 1680;i++)
						{
							characterIni[i] = 0;
						}
					
						objectL = (int *) malloc((NUMBER_OF_OBJECTS + 21) * sizeof(int));
						objectIni = (int *) malloc(1680 * sizeof(int));
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
						characterL[0] = source;
						characterIni[characterL[0]] = 1; 
						initMonsters(numMonsters, characterL, characterIni, characterMap, 
									dungeon, rooms, allRooms, npcTemplates);
						initObjects(objectL, objectIni, objectMap, 
									dungeon, rooms, allRooms, objectTemplates);
						queueDelete(q);
						queueInit(q);
						for (int i = 1; i < numMonsters + 1; i++)
						{
							addWithPriority(q, characterL[i], 0);
						}
						dijkstraNormal(dungeon, characterL[0], normalWeightMap);
						dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
					}
					break;
				}
				case '<':
				{
					if (stairsL[1] == u)
					{
						for (int i = 1; i < numMonsters + 1; i++)
						{
							if (characterIni[characterL[i]])
							{
								delete characterMap[characterL[i]];
								characterIni[characterL[i]] = 0;
							}
						}
						for (int i = 0; i < NUMBER_OF_OBJECTS + 21; i++)
						{
							if (objectIni[objectL[i]])
							{
								delete objectMap[objectL[i]];
								objectIni[objectL[i]] = 0;
							}
						}
						free(objectIni);
						free(objectL);
						free(characterIni);
						free(characterL);
						free(stairsL);
						free(rooms);
						free(allRooms);

						moveMade = 1;
						usedStairs = 1;
						
						for(unsigned int i = 0; i < npcTemplates.size(); i++)
						{
							npcTemplates[i]->isSpawned = 0;
						}

						*curMonsters = numMonsters = ((rand() % 16) + 4);
		
						rooms = (int *) malloc(sizeof(int));
						*rooms = ((rand() % 3) + 5);
						allRooms = (Room *) malloc((*rooms) * sizeof(Room));
						stairsL = (int *) malloc(2 * sizeof(int));
						dungeonInit(dungeon);
						generateRooms(dungeon, rooms, allRooms); 
						int source = spawnCharacter(dungeon, rooms, allRooms);
						loadStairs(dungeon, rooms, allRooms, stairsL);
						characterL = (int *) malloc((numMonsters + 1) * sizeof(int));
						characterIni = (int *) malloc(1680 * sizeof(int));
						for (int i = 0; i < 1680;i++)
						{
							characterIni[i] = 0;
						}
					
						objectL = (int *) malloc((NUMBER_OF_OBJECTS + 21) * sizeof(int));
						objectIni = (int *) malloc(1680 * sizeof(int));
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
						characterL[0] = source;
						characterIni[characterL[0]] = 1; 
						initMonsters(numMonsters, characterL, characterIni, characterMap, 
									dungeon, rooms, allRooms, npcTemplates);
						initObjects(objectL, objectIni, objectMap, 
									dungeon, rooms, allRooms, objectTemplates);
						queueDelete(q);
						queueInit(q);
						for (int i = 1; i < numMonsters + 1; i++)
						{
							addWithPriority(q, characterL[i], 0);
						}
						dijkstraNormal(dungeon, characterL[0], normalWeightMap);
						dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
					}
					break;
				}
				case '5':
				{
					int ty = (u / 80) - 2;
					int tx = (u % 80) - 2;
					moveMade = 1;
					for (int i = 0; i < 5; i++) //next 5x5 area is now lit
					{
						for (int j = 0; j < 5; j++)
						{
							if (((tx + j) > 0) && ((tx + j) < 79) && ((ty + i) < 20) && ((ty + i) > 0))
							{
								dungeon[ty + i][tx + j].isLit = 1;
								if(dungeon[ty + i][tx + j].hardness == 0)
									dungeon[ty + i][tx + j].hasSeen = 1;
							}
						}
					}
					break; //done
				}
				case ' ':
				{
					int ty = (u / 80) - 2;
					int tx = (u % 80) - 2;
					moveMade = 1;
					for (int i = 0; i < 5; i++) //next 5x5 area is now lit
					{
						for (int j = 0; j < 5; j++)
						{
							if (((tx + j) > 0) && ((tx + j) < 79) && ((ty + i) < 20) && ((ty + i) > 0))
							{
								dungeon[ty + i][tx + j].isLit = 1;
								if(dungeon[ty + i][tx + j].hardness == 0)
									dungeon[ty + i][tx + j].hasSeen = 1;
							}
						}
					}
					break; //done
				}
				case 'm':
				{
					char mList[40 * (*curMonsters)];
					char buffer[40];
					const char *banner = "Monster List";
					for (int i = 0; i < 40 * (*curMonsters); i++)
					{
						*(mList + i) = ' ';
					}
					int inputExit = 0;
					int mListOffset = 0;
					int mLine = 0;
					for (int i = 0; i < numMonsters; i++) // populating mList with Monster List details
					{
						for (int j = 0; j < 40; j++)
						{
							*(buffer + j) = ' ';
						}

						if (characterIni[characterL[i + 1]])
						{
							int tYM = characterL[i + 1] / 80;
							int tXM = characterL[i + 1] % 80;
							int tYPC = characterL[0] / 80;
							int tXPC = characterL[0] % 80;
							int rise = tYM - tYPC; // - north + south
							int run = tXM - tXPC;  // - west + east
							const char *yDir;
							const char *xDir;
							char tSymbol = characterMap[(tYM * 80) + tXM]->symbol;
							if (rise < 0)
							{
								yDir = "north";
								rise = abs(rise);
							}
							else if (rise > 0)
							{
								yDir = "south";
							}
							if (run < 0)
							{
								xDir = "west";
								run = abs(run);
							}
							else if (run > 0)
							{
								xDir = "east";
							}
							if (rise == 0)
							{
								snprintf(buffer, sizeof(buffer), "%c: %d due %s.", tSymbol, run, xDir);
							}
							else if (run == 0)
							{
								snprintf(buffer, sizeof(buffer), "%c: %d due %s.", tSymbol, rise, yDir);
							}
							else
							{
								snprintf(buffer, sizeof(buffer), "%c: %d %s, %d %s.", tSymbol, run, xDir, rise, yDir);
							}
							strcpy((mList + ((mLine * 40))), buffer);
							mLine++;
						}
					}
					char x = ' ';

					for (int i = 0; i < 12; i++)
					{
						mvaddch(1, i + 33, banner[i]);
					}
					for (int i = 0; i < 13; i++)
					{
						mvaddch(1, i + 1, ' ');
					}

					for (int i = 0; i < 40; i++) // horizontal
					{
						mvaddch(0, i + 20, '+');
						mvaddch(2, i + 20, '+');
						mvaddch(23, i + 20, '+');
					}

					for (int i = 0; i < 24; i++) // vertical
					{
						mvaddch(i, 0 + 19, '+');
						mvaddch(i, 40 + 19, '+');
					}

					for (int i = 3; i < 23; i++) // initial Monster List display
					{
						for (int j = 1; j < 40; j++)
						{
							if (i - 2 > *curMonsters)
							{
								x = ' ';
							}
							else
							{
								x = mList[((i - 3) * 40) + (j - 1)];
								if (x == '.')
									mList[((i - 3) * 40) + (j - 1) + 1] = ' ';
							}
							mvaddch((i - 3) + 3, (j - 1) + 20, x);
						}
					}
					refresh(); // initial Monster List display
					while (!inputExit)
					{
						int inputM = getch();
						switch (inputM)
						{
							case KEY_UP:
							{
								if ((*curMonsters > 20) && mListOffset > 0)
								{
									mListOffset--;

									for (int i = 3; i < 23; i++) // key up Monster List display
									{
										for (int j = 1; j < 40; j++)
										{
											if (i - 2 > *curMonsters)
											{
												x = ' ';
											}
											else
											{
												x = mList[((i - 3 + mListOffset) * 40) + (j - 1)];
												if (x == '.')
													mList[((i - 3 + mListOffset) * 40) + (j - 1) + 1] = ' ';
											}
											mvaddch((i - 3) + 3, (j - 1) + 20, x);
										}
									}
									refresh();
								}
								break;
							}
							case KEY_DOWN:
							{
								if ((*curMonsters > 20) && mListOffset + 20 < *curMonsters)
								{
									mListOffset++;

									for (int i = 3; i < 23; i++) // key down Monster List display
									{
										for (int j = 1; j < 40; j++)
										{
											if (i - 2 > *curMonsters)
											{
												x = ' ';
											}
											else
											{
												x = mList[((i - 3 + mListOffset) * 40) + (j - 1)];
												if (x == '.')
													mList[((i - 3 + mListOffset) * 40) + (j - 1) + 1] = ' ';
											}
											mvaddch((i - 3) + 3, (j - 1) + 20, x);
										}
									}
									refresh();
								}
								break;
							}
							case ESC:
							{
								inputExit = 1;
								clear();
								if (fogON)
								{
									displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								else
								{
									display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								refresh();
								break;
							}
							default:
							{
								break;
							}
						}
					}
					break;
				}
				case 'w':
				{
					int inputExit = 0;
					while(!inputExit)
					{
						clear();
						for(int i = 0; i < 10; i++)
						{
							char y = '0' + (i);
							mvaddch(i+1,0,y);
							mvaddch(i+1,1,':');
							mvaddch(i+1,2,' ');
						}
						for(unsigned int i = 0; i < pc->carrySlots.size(); i++)
						{
							for(unsigned int j = 3; j < pc->carrySlots[i]->name.size() + 3; j++)
							{
								char x = pc->carrySlots[i]->name[j-3];
								mvaddch(i+1,j,x);
							}
						}
						refresh();
						int inputW = getch();
						switch (inputW)
						{
							case ESC:
							{
								inputExit = 1;
								clear();
								if (fogON)
								{
									displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								else
								{
									display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								refresh();
								break;
							}
							case '0':
							case '1':
							case '2':
							case '3':
							case '4':
							case '5':
							case '6':
							case '7':
							case '8':
							case '9':
							{
								int compare = inputW - '0';
								if(((int) pc->carrySlots.size()) <= compare)
								{
									const char *ctemp = "Invalid input0";
									for(int i = 0; ctemp[i] != '0'; i++)
									{
										mvaddch(0,i,ctemp[i]);
									}
									refresh();
									usleep(300000);
								}
								else
								{
									int tempT = pc->carrySlots[compare]->type;
									if(tempT == 11)
									{
										if(pc->equipment[11]->damDice.sides == 0) //if ring2 empty
										{
											iter_swap(pc->carrySlots.begin() + compare, pc->equipment.begin() + 11);
											delete pc->carrySlots[compare];
											pc->carrySlots.erase(pc->carrySlots.begin() + compare);
										}
										else if(pc->equipment[10]->damDice.sides == 0)//if ring1 empty
										{
											iter_swap(pc->carrySlots.begin() + compare, pc->equipment.begin() + 10);
											delete pc->carrySlots[compare];
											pc->carrySlots.erase(pc->carrySlots.begin() + compare);
										}
										else //true swap
										{
											iter_swap(pc->carrySlots.begin() + compare, pc->equipment.begin() + 10);
										}
									}
									else 
									{
										if(pc->equipment[tempT-1]->damDice.sides == 0) // if equip slot empty
										{
											iter_swap(pc->carrySlots.begin() + compare, pc->equipment.begin() + (tempT - 1));
											delete pc->carrySlots[compare];
											pc->carrySlots.erase(pc->carrySlots.begin() + compare);
										}
										else
										{
											iter_swap(pc->carrySlots.begin() + compare, pc->equipment.begin() + (tempT - 1));
										}
									}
									pc->speed+= pc->equipment[tempT - 1]->speed;
									inputExit = 1;
									clear();
									if (fogON)
									{	
										displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
									}
									else
									{
										display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
									}
									refresh();
									break;			
								}
								break;
							}
							default:
							{
								break;
							}
						}
					}
					break;
				}
				case 't':
				{
					if(pc->carrySlots.size() == 10)
					{
						const char *cctemp = "You can't take off an item; your inventory is full!0";
						for(int i = 0; cctemp[i] != '0'; i++)
						{
							mvaddch(0,i,cctemp[i]);
						}
						refresh();
						usleep(300000);
						clear();
						if (fogON)
						{
							displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
						}
						else
						{
							display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
						}
						refresh();
						break;
					}
					int inputExit = 0;
					while(!inputExit)
					{
						
						
						clear();
						char c = 'a';
						for(int i = 0; i < 12; i++)
						{
							mvaddch(i,0,c);
							mvaddch(i,1,':');
							mvaddch(i,2,' ');
							c++;
						}
						for(int i = 0; i < 12; i++)
						{
							if(pc->equipment[i]->damDice.sides != 0)
							{
								for(unsigned int j = 3; j < pc->equipment[i]->name.size() + 3; j++)
								{
									char x = pc->equipment[i]->name[j - 3];
									mvaddch(i,j,x);
								}
							}
						}
						refresh();
						int inputT = getch();
						switch (inputT)
						{
							case ESC:
							{
								inputExit = 1;
								clear();
								if (fogON)
								{
									displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								else
								{
									display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								refresh();
								break;
							}
							case 'a':
							case 'b':
							case 'c':
							case 'd':
							case 'e':
							case 'f':
							case 'g':
							case 'h':
							case 'i':
							case 'j':
							case 'k':
							case 'l':
							{
								int trueIndex = inputT - 97;
								if(pc->equipment[trueIndex]->damDice.sides == 0)
								{
									const char *ctemp = "You have nothing equipped there!0";
									for(int i = 0; ctemp[i] != '0'; i++)
									{
										mvaddch(0,i,ctemp[i]);
									}
									refresh();
									usleep(300000);
								}
								else
								{
									pc->speed-= pc->equipment[trueIndex]->speed;
									pc->carrySlots.push_back(new Object());
									iter_swap(pc->equipment.begin() + trueIndex, pc->carrySlots.begin() + (pc->carrySlots.size() - 1));
									
									inputExit = 1;
									clear();
									if (fogON)
									{	
										displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
									}
									else
									{
										display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
									}
									refresh();
									break;
								}
								break;
							}
							default:
							{
								break;
							}
						}
					}
					break;
				}
				case 'd':
				{
					if((dungeon[uY][uX].objectNum != -1) || stairsL[0] == u || stairsL[1] == u)
					{
						const char *cctemp = "You can't drop an item here!0";
						for(int i = 0; cctemp[i] != '0'; i++)
						{
							mvaddch(0,i,cctemp[i]);
						}
						refresh();
						usleep(300000);
						clear();
						if (fogON)
						{
							displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
						}
						else
						{
							display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
						}
						refresh();
						break;
					}
					int inputExit = 0;
					while(!inputExit)
					{
						
						
						clear();
						for(int i = 0; i < 10; i++)
						{
							char y = '0' + (i);
							mvaddch(i+1,0,y);
							mvaddch(i+1,1,':');
							mvaddch(i+1,2,' ');
						}
						for(unsigned int i = 0; i < pc->carrySlots.size(); i++)
						{
							for(unsigned int j = 3; j < pc->carrySlots[i]->name.size() + 3; j++)
							{
								char x = pc->carrySlots[i]->name[j-3];
								mvaddch(i+1,j,x);
							}
						}
						refresh();
						int inputD = getch();
						switch (inputD)
						{
							case ESC:
							{
								inputExit = 1;
								clear();
								if (fogON)
								{
									displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								else
								{
									display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								refresh();
								break;
							}
							case '0':
							case '1':
							case '2':
							case '3':
							case '4':
							case '5':
							case '6':
							case '7':
							case '8':
							case '9':
							{
								int compare = inputD - '0';
								if(((int) pc->carrySlots.size()) <= compare)
								{
									const char *ctemp = "Invalid input0";
									for(int i = 0; ctemp[i] != '0'; i++)
									{
										mvaddch(0,i,ctemp[i]);
									}
									refresh();
									usleep(300000);
								}
								else
								{
									objectMap[characterL[0]] = new Object();
									// objectMap[characterL[0]] = pc->carrySlots[compare];
									for(int i = 0; i < NUMBER_OF_OBJECTS + 21; i++)
									{
										if(objectL[i] == 0)
										{
											int tempInt = characterL[0];
											objectL[i] = tempInt;
											objectIni[characterL[0]] = 1;
											dungeon[uY][uX].objectNum = pc->carrySlots[compare]->type;
											break;
										}
									}
									iter_swap(objectMap.begin() + characterL[0], pc->carrySlots.begin() + compare);
									delete pc->carrySlots[compare];
									pc->carrySlots.erase(pc->carrySlots.begin() + compare);
									inputExit = 1;
									clear();
									if (fogON)
									{	
										displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
									}
									else
									{
										display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
									}
									refresh();
									break;			
								}
								break;
							}
							default:
							{
								break;
							}
						}
					}
					break;
				}
				case 'x':
				{
					int inputExit = 0;
					while(!inputExit)
					{
						clear();
						for(int i = 0; i < 10; i++)
						{
							char y = '0' + (i);
							mvaddch(i+1,0,y);
							mvaddch(i+1,1,':');
							mvaddch(i+1,2,' ');
						}
						for(unsigned int i = 0; i < pc->carrySlots.size(); i++)
						{
							for(unsigned int j = 3; j < pc->carrySlots[i]->name.size() + 3; j++)
							{
								char x = pc->carrySlots[i]->name[j-3];
								mvaddch(i+1,j,x);
							}
						}
						refresh();
						int inputX = getch();
						switch (inputX)
						{
							case ESC:
							{
								inputExit = 1;
								clear();
								if (fogON)
								{
									displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								else
								{
									display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								refresh();
								break;
							}
							case '0':
							case '1':
							case '2':
							case '3':
							case '4':
							case '5':
							case '6':
							case '7':
							case '8':
							case '9':
							{
								int compare = inputX - '0';
								if(((int) pc->carrySlots.size()) <= compare)
								{
									const char *ctemp = "Invalid input0";
									for(int i = 0; ctemp[i] != '0'; i++)
									{
										mvaddch(0,i,ctemp[i]);
									}
									refresh();
									usleep(300000);
								}
								else
								{
									delete pc->carrySlots[compare];
									pc->carrySlots.erase(pc->carrySlots.begin() + compare);
									inputExit = 1;
									clear();
									if (fogON)
									{	
										displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
									}
									else
									{
										display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
									}
									refresh();
									break;			
								}
								break;
							}
							default:
							{
								break;
							}
						}
					}
					break;
				}
				case 'i':
				{
					int inputExit = 0;
					while(!inputExit)
					{
						clear();
						for(int i = 0; i < 10; i++)
						{
							char y = '0' + (i);
							mvaddch(i,0,y);
							mvaddch(i,1,':');
							mvaddch(i,2,' ');
						}
						for(unsigned int i = 0; i < pc->carrySlots.size(); i++)
						{
							for(unsigned int j = 3; j < pc->carrySlots[i]->name.size() + 3; j++)
							{
								char x = pc->carrySlots[i]->name[j-3];
								mvaddch(i,j,x);
							}
						}
						refresh();
						int inputI = getch();
						switch (inputI)
						{
							case ESC:
							{
								inputExit = 1;
								clear();
								if (fogON)
								{
									displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								else
								{
									display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								refresh();
								break;
							}
							default:
							{
								break;
							}
						}
					}
					break;
				}
				case 'e':
				{
					int inputExit = 0;
					while(!inputExit)
					{
						clear();
						char c = 'a';
						for(int i = 0; i < 12; i++)
						{
							mvaddch(i,0,c);
							mvaddch(i,1,':');
							mvaddch(i,2,' ');
							c++;
						}
						for(int i = 0; i < 12; i++)
						{
							if(pc->equipment[i]->damDice.sides != 0)
							{
								for(unsigned int j = 3; j < pc->equipment[i]->name.size() + 3; j++)
								{
									char x = pc->equipment[i]->name[j - 3];
									mvaddch(i,j,x);
								}
							}
						}
						refresh();
						int inputE = getch();
						switch (inputE)
						{
							case ESC:
							{
								inputExit = 1;
								clear();
								if (fogON)
								{
									displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								else
								{
									display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								refresh();
								break;
							}
							default:
							{
								break;
							}
						}
					}
					break;
				}
				case 'I':
				{
					int inputExit = 0;
					while(!inputExit)
					{
						clear();
						for(int i = 0; i < 10; i++)
						{
							char y = '0' + (i);
							mvaddch(i+1,0,y);
							mvaddch(i+1,1,':');
							mvaddch(i+1,2,' ');
						}
						for(unsigned int i = 0; i < pc->carrySlots.size(); i++)
						{
							for(unsigned int j = 3; j < pc->carrySlots[i]->name.size() + 3; j++)
							{
								char x = pc->carrySlots[i]->name[j-3];
								mvaddch(i+1,j,x);
							}
						}
						refresh();
						int inputII = getch();
						switch (inputII)
						{
							case ESC:
							{
								inputExit = 1;
								clear();
								if (fogON)
								{
									displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								else
								{
									display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								refresh();
								break;
							}
							case '0':
							case '1':
							case '2':
							case '3':
							case '4':
							case '5':
							case '6':
							case '7':
							case '8':
							case '9':
							{
								int compare = inputII - '0';
								if(((int) pc->carrySlots.size()) <= compare)
								{
									const char *ctemp = "Invalid input0";
									for(int i = 0; ctemp[i] != '0'; i++)
									{
										mvaddch(0,i,ctemp[i]);
									}
									refresh();
									usleep(300000);
								}
								else
								{
									clear();
									for(unsigned int i = 0, j = 0, k = 0; i < pc->carrySlots[compare]->desc.size(); i++)
									{
										if(pc->carrySlots[compare]->desc[i] == '\n')
										{
											j++;
											k = 0;
										}
										else
										{
											mvaddch(j,k,pc->carrySlots[compare]->desc[i]);
											k++;
										}
									}
									refresh();
									while(!inputExit)
									{
										int inputIII = getch();
										if(inputIII == ESC)
										{
											inputExit = 1;
											clear();
											if (fogON)
											{
												displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
											}
											else
											{
												display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
											}
											refresh();
											break;
										}
									}
								}
								break;
							}
							default:
							{
								break;
							}
						}
					}
					break;
				}
				case 'L':
				{
					
					int tpCursor = characterL[0];
					clear();
					if (fogON)
					{
						displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
					}
					else						
					{
						display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
					}
					mvaddch((tpCursor / 80) + 1, tpCursor % 80, '*');
					refresh();
					int inputExit = 0;
					while(!inputExit)
					{
						int inputL = getch();
						switch (inputL)
						{
							case KEY_UP:
							{
								if((tpCursor / 80) != 1)
								{
								tpCursor -= 80;
								clear();
								if (fogON)
								{
									displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								else
								{
									display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								mvaddch((tpCursor / 80) + 1, tpCursor % 80, '*');
								refresh();
								}
								break;
							}
							case KEY_DOWN:
							{
								if((tpCursor / 80) != 19)
								{
								tpCursor += 80;
								clear();
								if (fogON)
								{
									displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								else
								{
									display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								mvaddch((tpCursor / 80) + 1, tpCursor % 80, '*');
								refresh();
								}
								break;
							}
							case KEY_LEFT:
							{
								if((tpCursor % 80) != 1)
								{
								tpCursor -= 1;
								clear();
								if (fogON)
								{
									displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								else
								{
									display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								mvaddch((tpCursor / 80) + 1, tpCursor % 80, '*');
								refresh();
								}
								break;
							}
							case KEY_RIGHT:
							{ 
								if((tpCursor % 80) != 78)
								{
								tpCursor += 1;
								clear();
								if (fogON)
								{
									displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								else
								{
									display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								mvaddch((tpCursor / 80) + 1, tpCursor % 80, '*');
								refresh();
								}
								break;
							}
							case 't':
							{
								if (tpCursor != characterL[0] && characterIni[tpCursor])
								{
									clear();
									for(unsigned int i = 0, j = 0, k = 0; i < characterMap[tpCursor]->desc.size(); i++)
									{
										if(characterMap[tpCursor]->desc[i] == '\n')
										{
											j++;
											k = 0;
										}
										else
										{
											mvaddch(j,k,characterMap[tpCursor]->desc[i]);
											k++;
										}
									}
									refresh();
									
									while(!inputExit)
									{
										int inputLL = getch();
										if(inputLL == ESC)
										{
											inputExit = 1;
											clear();
											if (fogON)
											{
												displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
											}
											else
											{
												display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
											}
											refresh();
										}
									}
								}
								break;
							}
							case ESC:
							{
								inputExit = 1;
								clear();
								if (fogON)
								{
									displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								else
								{
									display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								refresh();
								break;
							}
							default:
							{
								break;
							}
						}
					}
					break;
				}
				
				case 'Q':
				{
					inputQuit = 1;
					moveMade = 1;
					break; //done
				}
				case 'f':
				{
					if (fogON)
					{
						fogON = 0;
					}
					else
					{
						fogON = 1;
					}
					clear();
					if (fogON)
					{
						displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
					}
					else
					{
						display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
					}
					refresh();
					break;
				}
				case 'g':
				{
					int TPDone = 0;
					int tpCursor = characterL[0];
					clear();
					display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
					mvaddch((tpCursor / 80) + 1, tpCursor % 80, '*');
					refresh();
					while (!TPDone)
					{
						int inputT = getch();
						switch (inputT)
						{
							case KEY_UP:
							{
								if((tpCursor / 80) != 1)
								{
								tpCursor -= 80;
								clear();
								display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								mvaddch((tpCursor / 80) + 1, tpCursor % 80, '*');
								refresh();
								}
								break;
							}
							case KEY_DOWN:
							{
								if((tpCursor / 80) != 19)
								{
								tpCursor += 80;
								clear();
								display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								mvaddch((tpCursor / 80) + 1, tpCursor % 80, '*');
								refresh();
								}
								break;
							}
							case KEY_LEFT:
							{
								if((tpCursor % 80) != 1)
								{
								tpCursor -= 1;
								clear();
								display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								mvaddch((tpCursor / 80) + 1, tpCursor % 80, '*');
								refresh();
								}
								break;
							}
							case KEY_RIGHT:
							{ 
								if((tpCursor % 80) != 78)
								{
								tpCursor += 1;
								clear();
								display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								mvaddch((tpCursor / 80) + 1, tpCursor % 80, '*');
								refresh();
								}
								break;
							}
							case 't':
							{
								if (tpCursor != characterL[0])
								{
									teleportCharacter(q, tpCursor, characterL[0], numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
									moveMade = 1;
									TPDone = 1;
									clear();
									if (fogON)
									{
										displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
									}
									else
									{
										display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
									}
									refresh();
								}
								break;
							}
							case 'r':
							{
								int rTPy = (rand() % 19) + 1;
								int rTPx = (rand() % 78) + 1;
								tpCursor = (rTPy * 80) + rTPx;
								while(tpCursor == characterL[0])
								{
									rTPy = (rand() % 19) + 1;
									rTPx = (rand() % 78) + 1;
									tpCursor = (rTPy * 80) + rTPx;
								}
								teleportCharacter(q, tpCursor, characterL[0], numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
								moveMade = 1;
								TPDone = 1;
								clear();
								if (fogON)
								{
									displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								else
								{
									display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
								}
								refresh();
								break;
							}
							default:
							{
								break;
							}
						}
					}
				}
				default:
				{
					break;
				}
				}
			}

			/*
			if(dungeon[uY][uX + 1].hardness == 0)
			{
				moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
			}
			else if(dungeon[uY][uX - 1].hardness == 0)
			{
				moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
			}*/
		}
		else //npc move
		{
			for (int i = 1; i < numMonsters + 1; i++)
			{
				if (characterL[i] == u)
				{
					cur = i;
					break;
				}
			}

			switch (characterMap[u]->characteristics & 0xf)
			{
			case 0x0: //0000
			{
				int j = -1;
				for (int i = 0; i < numMonsters; i++)
				{
					if (u == characterL[i + 1])
					{
						j = i + 1;
						break;
					}
				}
				if (canSee(j, characterL, dungeon))
				{

					if ((uX > ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // + +
					{
						moveCharacter(q, 8, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX < ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // - -
					{
						moveCharacter(q, 4, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX < ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // - +
					{
						moveCharacter(q, 2, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX > ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // + -
					{
						moveCharacter(q, 6, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX == ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // = -
					{
						moveCharacter(q, 5, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX == ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // = +
					{
						moveCharacter(q, 1, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX < ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // - =
					{
						moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX > ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // + =
					{
						moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
				}
				break;
			}
			case 0x1: //0001
			{
				if (characterMap[u]->lastLocation != -1) // if last location is known to monster
				{
					dijkstraNormal(dungeon, characterMap[u]->lastLocation, normalWeightMap);

					int lowest = 9;
					int j = 0;
					int n;
					for (int i = 1; i < 9; i++)
					{
						j = getMoveLiteral(i);
						if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness == 0)
						{
							n = (char)normalWeightMap[u + j];
							if (n < lowest)
								lowest = n;
						}
					}

					for (int i = 1; i < 9; i++)
					{
						j = getMoveLiteral(i);
						if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness == 0)
						{
							n = (char)normalWeightMap[u + j];
							if (n == lowest)
							{
								moveCharacter(q, i, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
								break;
							}
						}
					}
				}

				if (characterIni[characterL[0]])
				{
					dijkstraNormal(dungeon, characterL[0], normalWeightMap);
				}
				break;
			}
			case 0x2: //0010
			{
				int l = -1;
				if ((uX > ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // + +
				{
					l = getMoveLiteral(8);
					if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
						moveCharacter(q, 8, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else if ((uX < ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // - -
				{
					l = getMoveLiteral(4);
					if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
						moveCharacter(q, 4, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else if ((uX < ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // - +
				{
					l = getMoveLiteral(2);
					if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
						moveCharacter(q, 2, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else if ((uX > ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // + -
				{
					l = getMoveLiteral(6);
					if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
						moveCharacter(q, 6, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else if ((uX == ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // = -
				{
					l = getMoveLiteral(5);
					if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
						moveCharacter(q, 5, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else if ((uX == ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // = +
				{
					l = getMoveLiteral(1);
					if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
						moveCharacter(q, 1, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else if ((uX < ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // - =
				{
					l = getMoveLiteral(3);
					if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
						moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else if ((uX > ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // + =
				{
					l = getMoveLiteral(7);
					if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
						moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				break;
			}
			case 0x3: //0011
			{
				dijkstraNormal(dungeon, characterL[0], normalWeightMap);
				int lowest = 9;
				int j = 0;
				int n;

				for (int i = 1; i < 9; i++)
				{
					j = getMoveLiteral(i);
					if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness == 0)
					{
						n = (char)normalWeightMap[u + j];
						if (n < lowest)
							lowest = n;
					}
				}

				for (int i = 1; i < 9; i++)
				{
					j = getMoveLiteral(i);
					if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness == 0)
					{
						n = (char)normalWeightMap[u + j];
						if (n == lowest)
						{
							moveCharacter(q, i, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
							break;
						}
					}
				}
				break;
			}
			case 0x4: //0100
			{
				int j = -1;
				for (int i = 0; i < numMonsters; i++)
				{
					if (u == characterL[i + 1])
					{
						j = i + 1;
						break;
					}
				}
				if (canSee(j, characterL, dungeon))
				{

					if ((uX > ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // + +
					{
						moveCharacter(q, 8, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX < ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // - -
					{
						moveCharacter(q, 4, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX < ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // - +
					{
						moveCharacter(q, 2, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX > ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // + -
					{
						moveCharacter(q, 6, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX == ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // = -
					{
						moveCharacter(q, 5, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX == ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // = +
					{
						moveCharacter(q, 1, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX < ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // - =
					{
						moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX > ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // + =
					{
						moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}

					if (characterIni[characterL[0]])
					{
						dijkstraNormal(dungeon, characterL[0], normalWeightMap);
						dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
					}
				}
				break;
			}
			case 0x5: //0101
			{
				if (characterMap[u]->lastLocation != -1) // if last location is known to monster
				{
					dijkstraTunneling(dungeon, characterMap[u]->lastLocation, tunnelWeightMap);
					int n;
					int lowest = 9;
					int j = 0;
					for (int i = 1; i < 9; i++)
					{
						j = getMoveLiteral(i);
						if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness < 255)
						{
							n = (char)tunnelWeightMap[u + j];
							if (n < lowest)
								lowest = n;
						}
					}

					for (int i = 1; i < 9; i++)
					{
						j = getMoveLiteral(i);
						if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness < 255)
						{
							n = (char)tunnelWeightMap[u + j];
							if (n == lowest)
							{
								moveCharacter(q, i, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
								if (characterIni[characterL[0]])
								{
									dijkstraNormal(dungeon, characterL[0], normalWeightMap);
									dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
								}
								break;
							}
						}
					}
				}
				break;
			}
			case 0x6: //0110
			{
				if ((uX > ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // + +
				{
					moveCharacter(q, 8, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else if ((uX < ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // - -
				{
					moveCharacter(q, 4, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else if ((uX < ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // - +
				{
					moveCharacter(q, 2, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else if ((uX > ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // + -
				{
					moveCharacter(q, 6, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else if ((uX == ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // = -
				{
					moveCharacter(q, 5, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else if ((uX == ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // = +
				{
					moveCharacter(q, 1, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else if ((uX < ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // - =
				{
					moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else if ((uX > ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // + =
				{
					moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				if (characterIni[characterL[0]])
				{
					dijkstraNormal(dungeon, characterL[0], normalWeightMap);
					dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
				}
				break;
			}
			case 0x7: //0111
			{
				dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
				int lowest = 9;
				int j = 0;
				int n;
				for (int i = 1; i < 9; i++)
				{
					j = getMoveLiteral(i);
					if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness < 255)
					{
						n = (char)tunnelWeightMap[u + j];
						if (n < lowest)
							lowest = n;
					}
				}

				for (int i = 1; i < 9; i++)
				{
					j = getMoveLiteral(i);
					if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness < 255)
					{
						n = (char)tunnelWeightMap[u + j];
						if (n == lowest)
						{
							moveCharacter(q, i, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
							if (characterIni[characterL[0]])
							{
								dijkstraNormal(dungeon, characterL[0], normalWeightMap);
								dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
							}
							break;
						}
					}
				}
				break;
			}
			case 0x8: //1000
			{
				if (r)
				{
					int direction = (rand() % 8) + 1;
					int l = getMoveLiteral(direction);
					while (dungeon[uY + (l / 80)][uX + (l % 80)].hardness != 0)
					{
						direction = (rand() % 8) + 1;
						l = getMoveLiteral(direction);
					}
					moveCharacter(q, direction, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else
				{
					int j = -1;
					for (int i = 0; i < numMonsters; i++)
					{
						if (u == characterL[i + 1])
						{
							j = i + 1;
							break;
						}
					}
					if (canSee(j, characterL, dungeon))
					{

						if ((uX > ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // + +
						{
							moveCharacter(q, 8, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
						else if ((uX < ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // - -
						{
							moveCharacter(q, 4, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
						else if ((uX < ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // - +
						{
							moveCharacter(q, 2, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
						else if ((uX > ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // + -
						{
							moveCharacter(q, 6, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
						else if ((uX == ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // = -
						{
							moveCharacter(q, 5, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
						else if ((uX == ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // = +
						{
							moveCharacter(q, 1, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
						else if ((uX < ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // - =
						{
							moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
						else if ((uX > ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // + =
						{
							moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
					}
				}
				break;
			}
			case 0x9: //1001
			{
				if (r)
				{
					int direction = (rand() % 8) + 1;
					int l = getMoveLiteral(direction);
					while (dungeon[uY + (l / 80)][uX + (l % 80)].hardness != 0)
					{
						direction = (rand() % 8) + 1;
						l = getMoveLiteral(direction);
					}
					moveCharacter(q, direction, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else
				{
					if (characterMap[u]->lastLocation != -1) // if last location is known to monster
					{
						dijkstraNormal(dungeon, characterMap[u]->lastLocation, normalWeightMap);

						int lowest = 9;
						int j = 0;
						int n;
						for (int i = 1; i < 9; i++)
						{
							j = getMoveLiteral(i);
							if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness == 0)
							{
								n = (char)normalWeightMap[u + j];
								if (n < lowest)
									lowest = n;
							}
						}

						for (int i = 1; i < 9; i++)
						{
							j = getMoveLiteral(i);
							if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness == 0)
							{
								n = (char)normalWeightMap[u + j];
								if (n == lowest)
								{
									moveCharacter(q, i, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
									break;
								}
							}
						}
					}

					if (characterIni[characterL[0]])
					{
						dijkstraNormal(dungeon, characterL[0], normalWeightMap);
					}
				}
				break;
			}
			case 0xa: //1010
			{
				if (r)
				{
					int direction = (rand() % 8) + 1;
					int l = getMoveLiteral(direction);
					while (dungeon[uY + (l / 80)][uX + (l % 80)].hardness != 0)
					{
						direction = (rand() % 8) + 1;
						l = getMoveLiteral(direction);
					}
					moveCharacter(q, direction, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else
				{
					int l = -1;
					if ((uX > ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // + +
					{
						l = getMoveLiteral(8);
						if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
							moveCharacter(q, 8, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX < ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // - -
					{
						l = getMoveLiteral(4);
						if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
							moveCharacter(q, 4, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX < ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // - +
					{
						l = getMoveLiteral(2);
						if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
							moveCharacter(q, 2, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX > ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // + -
					{
						l = getMoveLiteral(6);
						if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
							moveCharacter(q, 6, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX == ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // = -
					{
						l = getMoveLiteral(5);
						if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
							moveCharacter(q, 5, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX == ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // = +
					{
						l = getMoveLiteral(1);
						if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
							moveCharacter(q, 1, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX < ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // - =
					{
						l = getMoveLiteral(3);
						if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
							moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX > ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // + =
					{
						l = getMoveLiteral(7);
						if (dungeon[uY + (l / 80)][uX + (l % 80)].hardness == 0)
							moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
				}
				break;
			}
			case 0xb: //1011
			{
				if (r)
				{
					int direction = (rand() % 8) + 1;
					int l = getMoveLiteral(direction);
					while (dungeon[uY + (l / 80)][uX + (l % 80)].hardness != 0)
					{
						direction = (rand() % 8) + 1;
						l = getMoveLiteral(direction);
					}
					moveCharacter(q, direction, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
				}
				else
				{
					dijkstraNormal(dungeon, characterL[0], normalWeightMap);
					int lowest = 9;
					int j = 0;
					int n;

					for (int i = 1; i < 9; i++)
					{
						j = getMoveLiteral(i);
						if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness == 0)
						{
							n = (char)normalWeightMap[u + j];
							if (n < lowest)
								lowest = n;
						}
					}

					for (int i = 1; i < 9; i++)
					{
						j = getMoveLiteral(i);
						if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness == 0)
						{
							n = (char)normalWeightMap[u + j];
							if (n == lowest)
							{
								moveCharacter(q, i, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
								break;
							}
						}
					}
				}
				break;
			}
			case 0xc: //1100
			{
				if (r)
				{
					if (uX < 78 && uX > 1 && uY > 1 && uY < 19)
					{
						int direction = (rand() % 8) + 1;
						moveCharacter(q, direction, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}

					else if (uX == 1)
						moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					else if (uX == 78)
						moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					else if (uY == 1)
						moveCharacter(q, 5, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					else if (uY == 19)
						moveCharacter(q, 1, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					if (characterIni[characterL[0]])
					{
						dijkstraNormal(dungeon, characterL[0], normalWeightMap);
						dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
					}
				}
				else
				{
					int j = -1;
					for (int i = 0; i < numMonsters; i++)
					{
						if (u == characterL[i + 1])
						{
							j = i + 1;
							break;
						}
					}
					if (canSee(j, characterL, dungeon))
					{

						if ((uX > ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // + +
						{
							moveCharacter(q, 8, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
						else if ((uX < ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // - -
						{
							moveCharacter(q, 4, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
						else if ((uX < ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // - +
						{
							moveCharacter(q, 2, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
						else if ((uX > ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // + -
						{
							moveCharacter(q, 6, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
						else if ((uX == ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // = -
						{
							moveCharacter(q, 5, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
						else if ((uX == ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // = +
						{
							moveCharacter(q, 1, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
						else if ((uX < ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // - =
						{
							moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
						else if ((uX > ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // + =
						{
							moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
						}
					}
				}
				break;
			}
			case 0xd: //1101
			{
				if (r)
				{
					if (uX < 78 && uX > 1 && uY > 1 && uY < 19)
					{
						int direction = (rand() % 8) + 1;
						moveCharacter(q, direction, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}

					else if (uX == 1)
						moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					else if (uX == 78)
						moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					else if (uY == 1)
						moveCharacter(q, 5, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					else if (uY == 19)
						moveCharacter(q, 1, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					if (characterIni[characterL[0]])
					{
						dijkstraNormal(dungeon, characterL[0], normalWeightMap);
						dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
					}
				}
				else
				{
					if (characterMap[u]->lastLocation != -1) // if last location is known to monster
					{
						dijkstraTunneling(dungeon, characterMap[u]->lastLocation, tunnelWeightMap);

						int lowest = 9;
						int j = 0;
						int n;
						for (int i = 1; i < 9; i++)
						{
							j = getMoveLiteral(i);
							if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness < 255)
							{
								n = (char)tunnelWeightMap[u + j];
								if (n < lowest)
									lowest = n;
							}
						}

						for (int i = 1; i < 9; i++)
						{
							j = getMoveLiteral(i);
							if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness < 255)
							{
								n = (char)tunnelWeightMap[u + j];
								if (n == lowest)
								{
									moveCharacter(q, i, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
									if (characterIni[characterL[0]])
									{
										dijkstraNormal(dungeon, characterL[0], normalWeightMap);
										dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
									}
									break;
								}
							}
						}
					}
				}
				break;
			}
			case 0xe: //1110
			{
				if (r)
				{
					if (uX < 78 && uX > 1 && uY > 1 && uY < 19)
					{
						int direction = (rand() % 8) + 1;
						moveCharacter(q, direction, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}

					else if (uX == 1)
						moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					else if (uX == 78)
						moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					else if (uY == 1)
						moveCharacter(q, 5, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					else if (uY == 19)
						moveCharacter(q, 1, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					if (characterIni[characterL[0]])
					{
						dijkstraNormal(dungeon, characterL[0], normalWeightMap);
						dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
					}
				}
				else
				{
					if ((uX > ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // + +
					{
						moveCharacter(q, 8, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX < ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // - -
					{
						moveCharacter(q, 4, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX < ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // - +
					{
						moveCharacter(q, 2, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX > ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // + -
					{
						moveCharacter(q, 6, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX == ((characterL[0]) % 80)) && (uY < ((characterL[0]) / 80))) // = -
					{
						moveCharacter(q, 5, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX == ((characterL[0]) % 80)) && (uY > ((characterL[0]) / 80))) // = +
					{
						moveCharacter(q, 1, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX < ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // - =
					{
						moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					else if ((uX > ((characterL[0]) % 80)) && (uY == ((characterL[0]) / 80))) // + =
					{
						moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}
					if (characterIni[characterL[0]])
					{
						dijkstraNormal(dungeon, characterL[0], normalWeightMap);
						dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
					}
				}
				break;
			}
			case 0xf: //1111
			{
				if (r)
				{
					if (uX < 78 && uX > 1 && uY > 1 && uY < 19)
					{
						int direction = (rand() % 8) + 1;
						moveCharacter(q, direction, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					}

					else if (uX == 1)
						moveCharacter(q, 3, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					else if (uX == 78)
						moveCharacter(q, 7, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					else if (uY == 1)
						moveCharacter(q, 5, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					else if (uY == 19)
						moveCharacter(q, 1, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
					if (characterIni[characterL[0]])
					{
						dijkstraNormal(dungeon, characterL[0], normalWeightMap);
						dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
					}
				}
				else
				{
					dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
					int lowest = 9;
					int j = 0;
					int n;
					for (int i = 1; i < 9; i++)
					{
						j = getMoveLiteral(i);
						if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness < 255)
						{
							n = (char)tunnelWeightMap[u + j];
							if (n < lowest)
								lowest = n;
						}
					}

					for (int i = 1; i < 9; i++)
					{
						j = getMoveLiteral(i);
						if (dungeon[uY + (j / 80)][uX + (j % 80)].hardness < 255)
						{
							n = (char)tunnelWeightMap[u + j];
							if (n == lowest)
							{
								moveCharacter(q, i, u, numMonsters, curMonsters, characterL, characterIni, characterMap, dungeon, stairsL, spongeBobIndex, npcTemplates, pc, objectIni, objectL, objectMap);
								if (characterIni[characterL[0]])
								{
									dijkstraNormal(dungeon, characterL[0], normalWeightMap);
									dijkstraTunneling(dungeon, characterL[0], tunnelWeightMap);
								}
								break;
							}
						}
					}
				}
				break;
			}
			}
		}

		for (int i = 0; i < numMonsters; i++)
		{
			if (characterIni[characterL[i + 1]] && characterIni[characterL[0]])
			{
				if (canSee(i + 1, characterL, dungeon))
				{
					characterMap[characterL[i + 1]]->lastLocation = characterL[0];
				}
			}
		}
		//printf("\n");
		//printf("move %d",moveNum);
		//printf("\n");
		u = characterL[cur];
		//display

		clear();
		if (fogON)
		{
			displayFog(dungeon, stairsL, characterIni, characterL, characterMap, objectIni, objectMap);
		}
		else
		{
			display(dungeon, characterIni, characterL, characterMap, objectIni, objectMap);
		}
		refresh();

		//put back in Queue
		if (usedStairs)
		{
			addWithPriority(q, u, 0);
		}
		else
		{
			if(u == characterL[0])
				addWithPriority(q, u, (1000 / MAX(pc->speed,1)));
			else
				addWithPriority(q, u, (1000 / MAX(characterMap[u]->speed,1)));
		}
		//usleep(150000);
		free(p);
		if (inputQuit)
			break;
	}

	/*for(int i = 0; i < numMonsters; i++)
	{
		if(characterIni[characterL[i]])
		{
			free(characterMap[characterL[i]]);
			free(characterMap[characterL[i]]);
		}
	}*/
	queueDelete(q);
	free(q);
	free(normalWeightMap);
	free(tunnelWeightMap);
	endwin();
	if (npcTemplates[spongeBobIndex]->hasDied)
	{
		printf("You Win!");
	}
	else
		printf("You lose...");

	printf("\n");
	for (int i = 1; i < numMonsters + 1; i++)
	{
		if (characterIni[characterL[i]])
		{
			delete characterMap[characterL[i]];
			characterIni[characterL[i]] = 0;
		}
	}
	for (int i = 0; i < NUMBER_OF_OBJECTS + 21; i++)
	{
		if (objectIni[objectL[i]])
		{
			delete objectMap[objectL[i]];
			objectIni[objectL[i]] = 0;
		}
	}
	for(unsigned int i = 0; i < pc->carrySlots.size(); i++)
	{
		delete pc->carrySlots[i];
	}
	for(unsigned int i = 0; i < pc->equipment.size(); i++)
	{
		delete pc->equipment[i];
	}
	delete pc;
	free(objectIni);
	free(objectL);
	free(characterIni);
	free(characterL);
	free(stairsL);
	free(rooms);
	free(allRooms);
	free(curMonsters);
}
// 8 1 2
// 7   3
// 6 5 4
int moveCharacter(Queue *q, int direction, int location, int numMonsters, int *curMonsters, 
	int *characterL, int *characterIni, vector<NPC *> &characterMap, Cell dungeon[][80], int *stairsL,
	unsigned int spongeBobIndex, vector<NPC *> &npcTemplates, PC *pc, int *objectIni, int *objectL, vector<Object *> &objectMap)
{
	int x = location % 80;
	int y = location / 80;
	int l = getMoveLiteral(direction);
	int lx = (l + location) % 80;
	int ly = (l + location) / 80;
	int killedCharacter = 0;
	int moved = 0;
	int swapped = 0;
	if (characterL[0] == location) //mover is PC
	{
		
		if(characterIni[location + l]) //spot moving to has Character
		{
			int totaldamage = 0;
			if(pc->equipment[0]->damDice.sides == 0) //Does work.
			{
				totaldamage += (rand()% 4) + 1;
			}
			else 
			{
				totaldamage += pc->equipment[0]->damDice.roll();
			}
			for(unsigned int i = 1; i < 12; i++)
			{
				if(pc->equipment[i]->damDice.sides == 0)
					;
				else
					totaldamage += pc->equipment[i]->damDice.roll();
			}
			characterMap[location + l]->hp -= totaldamage;
			if(characterMap[location + l]-> hp <= 0)
			{
				killedCharacter = 1;
				moved = 1;
			}
		}
		else
			moved = 1;
		
		if(killedCharacter)
		{
			if(((characterMap[location + l]->characteristics) & UNIQ) == UNIQ)
			{
				for (unsigned int i = 0; i < npcTemplates.size(); i++)
				{
					if (npcTemplates[i]->name == characterMap[location + l]->name)
					{
						npcTemplates[i]->hasDied = 1;
						break;
					}
				}
			}
		
			queueRemoveEvent(q, location + l);
			delete characterMap[location + l];
			(*curMonsters)--;
		
		}
		if(moved) 
		{
			if (objectIni[location + l]) //spot moving to has object
			{
				if(pc->carrySlots.size() < 10)
				{
					pc->carrySlots.push_back(new Object());
					iter_swap(pc->carrySlots.begin() + (pc->carrySlots.size() - 1), objectMap.begin() + (location + l));
					delete objectMap[location + l];
					dungeon[ly][lx].objectNum = -1;
					objectL[location + l] = 0;
					objectIni[location + l] = 0;
					
				}//pickup item if have spaceb
				//else do nothing
			}
			dungeon[y + (l / 80)][x + (l % 80)].graphic = pc->symbol;
			
			int tx = x - 2;
			int ty = y - 2;
			for (int i = 0; i < 5; i++) //previous 5x5 area is no longer lit
			{
				for (int j = 0; j < 5; j++)
				{
					if (((tx + j) > 0) && ((tx + j) < 79) && ((ty + i) < 20) && ((ty + i) > 0))
						dungeon[ty + i][tx + j].isLit = 0;
				}
			}

			tx = lx - 2;
			ty = ly - 2;
			for (int i = 0; i < 5; i++) //next 5x5 area is now lit
			{
				for (int j = 0; j < 5; j++)
				{
					if (((tx + j) > 0) && ((tx + j) < 79) && ((ty + i) < 20) && ((ty + i) > 0))
					{
						dungeon[ty + i][tx + j].isLit = 1;
						if(dungeon[ty + i][tx + j].hardness == 0)
							dungeon[ty + i][tx + j].hasSeen = 1;
					}
				}
			}
		}
	}
	else // mover is NPC
	{ 

		if (characterIni[location + l]) // if spot moving to has character
		{
			if(characterL[0] == location + l) // if character attacking is pc
			{
				pc->hp -= characterMap[location]->damDice.roll();
				if(pc->hp <= 0)
				{
					killedCharacter = 1;
					moved = 1;
				}
			}
			else
			{

				iter_swap(characterMap.begin() + location, characterMap.begin() + location + l);
				int tempD = queueRemoveEvent(q, location + l);
				addWithPriority(q,location,tempD);
				swapped = 1;
			}
			
		}
		else
			moved = 1;
		if(killedCharacter)
		{
			if(characterL[0] != location + l) // if character killing is not PC
			{
				if(((characterMap[location + l]->characteristics) & UNIQ) == UNIQ) // if killed character is UNIQ
				{
					for (unsigned int i = 0; i < npcTemplates.size(); i++)
					{
						if (npcTemplates[i]->name == characterMap[location + l]->name)
						{
							npcTemplates[i]->hasDied = 1;
							break;
						}
					}
				}
				queueRemoveEvent(q, location + l);
				delete characterMap[location + l];
				(*curMonsters)--;
			}
			else 
			{
				queueRemoveEvent(q, location + l);
			}
			
		}
		if(moved)
		{
			NPC *n = new NPC();
			
			characterMap[location + l] = characterMap[location];

			characterMap[location] = n;

			delete n;
			dungeon[ly][lx].graphic = characterMap[location + l]->symbol;
			
			if (dungeon[y + (l / 80)][x + (l % 80)].hardness > 0 && dungeon[y + (l / 80)][x + (l % 80)].hardness < 255) // if new loc rock
			{
				dungeon[y + (l / 80)][x + (l % 80)].hardness = 0;
			} //spot moving to gets graphic and hardness updated

			int tx = (characterL[0] % 80) - 2;
			int ty = (characterL[0] / 80) - 2;
			for (int i = 0; i < 5; i++) //next 5x5 area is now lit
			{
				for (int j = 0; j < 5; j++)
				{
					if (((tx + j) > 0) && ((tx + j) < 79) && ((ty + i) < 20) && ((ty + i) > 0))
					{
						dungeon[ty + i][tx + j].isLit = 1;
						if(dungeon[ty + i][tx + j].hardness == 0)
							dungeon[ty + i][tx + j].hasSeen = 1;
					}
				}
			}
		}
	
	}
	
	if(swapped)
	{
		int temp = 0;
		int sourceIndex = 0;
		int targetIndex = 0;
		dungeon[ly][lx].graphic = characterMap[location+l]->symbol;
		dungeon[y][x].graphic = characterMap[location]->symbol;
		for (int i = 0; i < numMonsters + 1; i++) // update characterL for swapping Characters
		{
			if (location == characterL[i])
			{
				sourceIndex = i;
			}
			else if(location + l == characterL[i])
			{
				targetIndex = i;	
			}
		}
		temp = characterL[sourceIndex];
		characterL[sourceIndex] = characterL[targetIndex];
		characterL[targetIndex] = temp;
	}
	if(moved && (swapped == 0))//might need parentheses
	{
		
		if (characterIni[location + l])
		{
			for (int i = 0; i < numMonsters + 1; i++) // update characterL and characterIni for killed Character
			{
				if ((location + l) == characterL[i])
					characterL[i] = 0;
			}
		}

		if (dungeon[y][x].isRoom) // applies to all - updates previous space occupied
		{
			if(dungeon[y][x].objectNum == -1)
			dungeon[y][x].graphic = '.';
			else
			dungeon[y][x].graphic = object_symbol[dungeon[y][x].objectNum];
		}
		else
		{
			if(dungeon[y][x].objectNum == -1)
			{
				dungeon[y][x].hardness = 0;
				dungeon[y][x].graphic = '#';
			}
			else
			dungeon[y][x].graphic = object_symbol[dungeon[y][x].objectNum];
		}

		characterIni[location] = 0; //update characterIni for dead (if dead) and moved Character
		characterIni[location + l] = 1;

		if (location == stairsL[0]) // handles if staircase was covered
			dungeon[y][x].graphic = '>';
		if (location == stairsL[1]) // handles if staircase was covered
			dungeon[y][x].graphic = '<';

		for (int i = 0; i < numMonsters + 1; i++) // update characterL for moving Character
		{
			if (location == characterL[i])
			{
				characterL[i] = location + l;
				break;
			}
		}
	}
	return 0;
}

int teleportCharacter(Queue *q, int destination, int location, int numMonsters, int *curMonsters, 
	int *characterL, int *characterIni, vector<NPC *> &characterMap, Cell dungeon[][80], int *stairsL, 
	unsigned int spongeBobIndex, vector<NPC *> &npcTemplates, PC *pc, int *objectIni, int *objectL, vector<Object *> &objectMap)
{
	int x = location % 80;
	int y = location / 80;
	int lx = (destination) % 80;
	int ly = (destination) / 80;
	
	int moved = 0;
	int killedCharacter = 0;
	
	if (dungeon[destination / 80][destination % 80].hardness > 0 && dungeon[destination / 80][destination % 80].hardness < 255) // if new loc rock
	{
		dungeon[destination / 80][destination % 80].hardness = 0;
		moved = 1;
	}

	if (characterIni[destination]) //spot moving to has Character
	{
		int totaldamage = 0;
		if(pc->equipment[0]->damDice.sides == 0) //Does work.
		{
			totaldamage += (rand()% 4) + 1;
		}
		else 
		{
			totaldamage += pc->equipment[0]->damDice.roll();
		}
		for(unsigned int i = 1; i < 12; i++)
		{
			if(pc->equipment[i]->damDice.sides == 0)
				;
			else
				totaldamage += pc->equipment[i]->damDice.roll();
		}
		characterMap[destination]->hp -= totaldamage;
		if(characterMap[destination]->hp <= 0)
		{
			killedCharacter = 1;
			moved = 1;
		}
	}
	else
		moved = 1;

	if(killedCharacter)
	{
		if(((characterMap[destination]->characteristics) & UNIQ) == UNIQ) // if killed character is UNIQ
			{
				for (unsigned int i = 0; i < npcTemplates.size(); i++)
				{
					if (npcTemplates[i]->name == characterMap[destination]->name)
					{
						npcTemplates[i]->hasDied = 1;
						break;
					}
				}
			}
			queueRemoveEvent(q, destination);
			delete characterMap[destination];
			(*curMonsters)--;
		
		if (characterIni[destination])
		{
			for (int i = 0; i < numMonsters + 1; i++) // update characterL and characterIni for killed Character
			{
				if ((destination) == characterL[i])
					characterL[i] = 0;
			}
		}
	}
	if(moved)
	{
		if (objectIni[destination]) //spot moving to has object
		{
			if(pc->carrySlots.size() < 10)
			{
				pc->carrySlots.push_back(new Object());
				iter_swap(pc->carrySlots.begin() + (pc->carrySlots.size() - 1), objectMap.begin() + destination);
				delete objectMap[destination];
				dungeon[ly][lx].objectNum = -1;
				objectL[destination] = 0;
				objectIni[destination] = 0;
				
			}//pickup item if have space
				//else do nothing
		}
		int tx = x - 2;
		int ty = y - 2;
		for (int i = 0; i < 5; i++) //previous 5x5 area is no longer lit
		{
			for (int j = 0; j < 5; j++)
			{
				if (((tx + j) > 0) && ((tx + j) < 79) && ((ty + i) < 20) && ((ty + i) > 0))
					dungeon[ty + i][tx + j].isLit = 0;
			}
		}

		tx = lx - 2;
		ty = ly - 2;
		for (int i = 0; i < 5; i++) //next 5x5 area is now lit
		{
			for (int j = 0; j < 5; j++)
			{
				if (((tx + j) > 0) && ((tx + j) < 79) && ((ty + i) < 20) && ((ty + i) > 0))
				{
					dungeon[ty + i][tx + j].isLit = 1;
					if(dungeon[ty + i][tx + j].hardness == 0)
						dungeon[ty + i][tx + j].hasSeen = 1;
				}
			}
		}
		
		dungeon[ly][lx].graphic = '@';
		
		if (dungeon[y][x].isRoom) // applies to all - updates previous space occupied
		{
			if(dungeon[y][x].objectNum == -1)
			dungeon[y][x].graphic = '.';
			else
			dungeon[y][x].graphic = object_symbol[dungeon[y][x].objectNum];
		}
		else
		{
			if(dungeon[y][x].objectNum == -1)
			{
				dungeon[y][x].hardness = 0;
				dungeon[y][x].graphic = '#';
			}
			else
			dungeon[y][x].graphic = object_symbol[dungeon[y][x].objectNum];
		}
		dungeon[destination / 80][destination % 80].graphic = pc->symbol;
		characterIni[location] = 0; //update characterIni for dead (if dead) and moved Character
		characterIni[destination] = 1;

		if (location == stairsL[0]) // handles if staircase was covered
			dungeon[y][x].graphic = '>';
		if (location == stairsL[1]) // handles if staircase was covered
			dungeon[y][x].graphic = '<';

		for (int i = 0; i < numMonsters + 1; i++) // update characterL for moving Character
		{
			if (location == characterL[i])
			{
				characterL[i] = destination;
				break;
			}
		}
	}
	return 0;
}

int getMoveLiteral(int d)
{
	if (d == 1)
		return -80;
	if (d == 2)
		return -79;
	if (d == 3)
		return 1;
	if (d == 4)
		return 81;
	if (d == 5)
		return 80;
	if (d == 6)
		return 79;
	if (d == 7)
		return -1;
	if (d == 8)
		return -81;
	return 0;
}