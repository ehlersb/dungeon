#include "character.h"

extern const char object_symbol[] = { //JEREMEY'S CODE
  '*', /* objtype_no_type */
  '|', /* objtype_WEAPON */
  ')', /* objtype_OFFHAND */
  '}', /* objtype_RANGED */
  '~', /* objtype_LIGHT */
  '[', /* objtype_ARMOR */
  ']', /* objtype_HELMET */
  '(', /* objtype_CLOAK */
  '{', /* objtype_GLOVES */
  '\\', /* objtype_BOOTS */
  '"', /* objtype_AMULET */
  '=', /* objtype_RING */
  '`', /* objtype_SCROLL */
  '?', /* objtype_BOOK */
  '!', /* objtype_FLASK */
  '$', /* objtype_GOLD */
  '/', /* objtype_AMMUNITION */
  ',', /* objtype_FOOD */
  '-', /* objtype_WAND */
  '%', /* objtype_CONTAINER */
};

using namespace std;


void initMonsters(int numMonsters, int *characterL, int *characterIni, vector<NPC *> &characterMap, 
	Cell dungeon[][80], int *rooms, Room *allRooms, vector<NPC *> &npcTemplates)
{
	
	for (int i = 0; i < numMonsters; i++)
	{
		NPC *n = new NPC();
		n->characteristics = 0x0;
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
		int rChar = rand() % npcTemplates.size();
		while(((npcTemplates[rChar]->characteristics & UNIQ) == UNIQ) && (npcTemplates[rChar]->isSpawned == 1 || npcTemplates[rChar]->hasDied == 1))
		{
			rChar = rand() % npcTemplates.size();
		}
		
		int temp = npcTemplates[rChar]->speedDice.roll();
		n->speed = temp;
		n->symbol = npcTemplates[rChar]->symbol;
		n->sequence = i + 1;
		n->hp = npcTemplates[rChar]->hpDice.roll();
		n->damDice = npcTemplates[rChar]->damDice;
		n->characteristics = n->characteristics | npcTemplates[rChar]->characteristics;
		n->lastLocation = -1;
		n->isSpawned = 1;
		npcTemplates[rChar]->isSpawned = 1;
		n->hasDied = 0;
		n->color = npcTemplates[rChar]->color;
		n->name = npcTemplates[rChar]->name;
		n->desc = npcTemplates[rChar]->desc;
		characterMap[(rPosY * 80) + (rPosX)] = n;
		characterL[i+1] = (rPosY * 80) + (rPosX);
		dungeon[rPosY][rPosX].graphic = n->symbol;
		characterIni[(rPosY * 80) + (rPosX)] = 1;
	}
	
	for(int i = 0; i < numMonsters; i++)
	{
		if(canSee(i + 1, characterL, dungeon))
			((NPC *)characterMap[characterL[i+1]])->lastLocation = characterL[0];
	}
}

void initObjects(int *objectL, int *objectIni, vector<Object *> &objectMap,
	Cell dungeon[][80], int *rooms, Room *allRooms, vector<Object *> &objectTemplates)
{
	
	for (int i = 0; i < NUMBER_OF_OBJECTS; i++)
	{
		Object *o = new Object();
		int rRoom = rand() % (*rooms);
		int baseX = allRooms[rRoom].posx;
		int baseY = allRooms[rRoom].posy;
		int rOffsetX = (rand() % allRooms[rRoom].sizex);
		int rOffsetY = (rand() % allRooms[rRoom].sizey);
		int rPosX = baseX + rOffsetX;
		int rPosY = baseY + rOffsetY;
		int rChar = rand() % objectTemplates.size();
		while(dungeon[rPosY][rPosX].graphic == '<' 
		|| dungeon[rPosY][rPosX].graphic == '>' 
		|| objectIni[(rPosY * 80) + (rPosX)] == 1) 
		{
			rRoom = rand() % (*rooms);
			baseX = allRooms[rRoom].posx;
			baseY = allRooms[rRoom].posy;
			rOffsetX = (rand() % allRooms[rRoom].sizex);
			rOffsetY = (rand() % allRooms[rRoom].sizey);
			rPosX = baseX + rOffsetX;
			rPosY = baseY + rOffsetY;
		}
		
		o->type = objectTemplates[rChar]->type;
		o->color = objectTemplates[rChar]->color;
		o->hit = objectTemplates[rChar]->hitDice.roll();
		o->damDice = objectTemplates[rChar]->damDice;
		
		o->name = objectTemplates[rChar]->name;
		o->desc = objectTemplates[rChar]->desc;
		o->weight = objectTemplates[rChar]->weightDice.roll();
		o->hit = objectTemplates[rChar]->hitDice.roll();
		o->attr = objectTemplates[rChar]->attrDice.roll();
		o->val = objectTemplates[rChar]->valDice.roll();
		o->dodge = objectTemplates[rChar]->dodgeDice.roll();
		o->def = objectTemplates[rChar]->defDice.roll();
		o->speed = objectTemplates[rChar]->speedDice.roll();
		objectMap[(rPosY * 80) + (rPosX)] = o;
		dungeon[rPosY][rPosX].objectNum = o->type;
		if(dungeon[rPosY][rPosX].graphic == '.')
			dungeon[rPosY][rPosX].graphic = object_symbol[o->type];
		objectL[i] = (rPosY * 80) + (rPosX);
		objectIni[(rPosY * 80) + (rPosX)] = 1;
	}
}

int canSee(int i, int *characterL, Cell dungeon[][80]) // where i is ith monster in characterL
{
	
	int rise = (characterL[0] / 80) - (characterL[i] / 80);
	int run = (characterL[0] % 80) - (characterL[i] % 80);
	if (rise >= 0 && run >= 0) // rise + run +
	{
		if (rise == 0)// if y coordinates match
		{
			for(int j = 0; j < run; j++)
			{
				if(dungeon[characterL[i] / 80][(characterL[i] % 80) + j].hardness >= 1)
				return 0;
			}
			return 1;
		}
		else if (run == 0)// if x coordinates match
		{
			for(int j = 0; j < rise; j++)
			{
				if(dungeon[(characterL[i] / 80) + j][characterL[i] % 80].hardness >= 1)
				return 0;
			}
			return 1;
		}
		else if (rise == run)
		{
			for(int j = 0; j < rise; j++)
			{
				if(dungeon[(characterL[i] / 80) + j][(characterL[i] % 80) + j].hardness >= 1)
				return 0;
			}
			return 1;
		}
		
		else // check if they are in same room
		{	
			for(int j = 0; j < run; j++)
			{
				for(int k = 0; k < rise; k++)
				{
					if(dungeon[(characterL[i] / 80) + k][(characterL[i] % 80) + j].hardness >= 1)
					return 0;
				}
			}
			return 1;
		}
	}
	else if (rise <=0 && run >= 0) // rise - run +
	{
		if (rise == 0)
		{
			for(int j = 0; j < run; j++)
			{
				if(dungeon[characterL[i] / 80][(characterL[i] % 80) + j].hardness >= 1)
				return 0;
			}
			return 1;
		}
		else if (run == 0)
		{
			for(int j = 0; j < abs(rise); j++)
			{
				if(dungeon[(characterL[i] / 80) - j][characterL[i] % 80].hardness >= 1)
				return 0;
			}
			return 1;
		}
		else if (abs(rise) == abs(run))
		{
			for(int j = 0; j < abs(rise); j++)
			{
				if(dungeon[(characterL[i] / 80) - j][(characterL[i] % 80) + j].hardness >= 1)
				return 0;
			}
			return 1;
		}
		else
		{	
			for(int j = 0; j < run; j++)
			{
				for(int k = 0; k < abs(rise); k++)
				{
					if(dungeon[(characterL[i] / 80) - k][(characterL[i] % 80) + j].hardness >= 1)
					return 0;
				}
			}
			return 1;
		}
	}
	else if (rise >= 0 && run <= 0) // rise + run -
	{
		if (rise == 0)
		{
			for(int j = 0; j < abs(run); j++)
			{
				if(dungeon[characterL[i] / 80][(characterL[i] % 80) - j].hardness >= 1)
				return 0;
			}
			return 1;
		}
		else if (run == 0)
		{
			for(int j = 0; j < rise; j++)
			{
				if(dungeon[(characterL[i] / 80) + j][characterL[i] % 80].hardness >= 1)
				return 0;
			}
			return 1;
		}
		else if (abs(rise) == abs(run))
		{
			for(int j = 0; j < rise; j++)
			{
				if(dungeon[(characterL[i] / 80) + j][(characterL[i] % 80) - j].hardness >= 1)
				return 0;
			}
			return 1;
		}
		else
		{	
			for(int j = 0; j < abs(run); j++)
			{
				for(int k = 0; k < rise; k++)
				{
					if(dungeon[(characterL[i] / 80) + k][(characterL[i] % 80) - j].hardness >= 1)
					return 0;
				}
			}
			return 1;
		}
	}
	else if (rise >= 0 && run >= 0) // rise - run -
	{
		if (rise == 0)
		{
			for(int j = 0; j < abs(run); j++)
			{
				if(dungeon[characterL[i] / 80][(characterL[i] % 80) - j].hardness >= 1)
				return 0;
			}
			return 1;
		}
		else if (run == 0)
		{
			for(int j = 0; j < abs(rise); j++)
			{
				if(dungeon[(characterL[i] / 80) - j][characterL[i] % 80].hardness >= 1)
				return 0;
			}
			return 1;
		}
		else if (abs(rise) == abs(run))
		{
			for(int j = 0; j < abs(rise); j++)
			{
				if(dungeon[(characterL[i] / 80) - j][(characterL[i] % 80) - j].hardness >= 1)
				return 0;
			}
			return 1;
		}
		else
		{	
			for(int j = 0; j < abs(run); j++)
			{
				for(int k = 0; k < abs(rise); k++)
				{
					if(dungeon[(characterL[i] / 80) - k][(characterL[i] % 80) - j].hardness >= 1)
					return 0;
				}
			}
			return 1;
		}
	}
	return 0; //dead code
}

int parseMonsters(std::ifstream &f, std::vector<NPC *> &npcTemplates) 
{
	if(!f) 
		{
			cerr << "error opening monster_desc.txt" << endl;
		}
		string s;
		getline(f, s);
		if(!f.eof())
		{
			if(s != "")
				{
				if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
					s.erase(s.size()-1,1);
				}
			if(s != "RLG327 MONSTER DESCRIPTION 1") 
			{
				cerr << "incorrect description file format (first line incorrect)" << endl;
				//exit(1);
			}
		}
		while(!f.eof())
		{
			bool failed = false; //these detect errors; useful for debugging as well as telling
			int name = 0;
			int symb = 0;
			int desc = 0;
			int color = 0;
			int speed = 0;
			int abil = 0;
			int hp = 0;
			int dam = 0;
			int invalidLines = 0;   //the parser to throw out the current monster
			//vector<string> thisMonster;
			getline(f, s);
			if(f.eof())
				break;
			if(s != "")
			{
			if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
				s.erase(s.size()-1,1);
			}
			NPC *npcTemp = new NPC();
			while(s != "BEGIN MONSTER" && !(f.eof())) 
			{
				getline(f, s);
				if(f.eof())
					break;
				if(s != "")
				{
				if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
					s.erase(s.size()-1,1);
				}
			}
			if(f.eof())
				break;
			getline(f, s); //line after BEGIN MONSTER
			if(f.eof())
				break;
			if(s != "")
				{
				if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
					s.erase(s.size()-1,1);
				}
			while(1) // this current monster block
			{
				
				string buf;
				vector<string> tokens;
				stringstream ss(s);
			
				while (ss >> buf)
					tokens.push_back(buf); //tokens now has every word split by whitespace
				
				if(tokens[0] == "NAME") 
				{
					name++;
					if(!(tokens.size() >= 2))
						name++;
					s.erase(0,5);
					string b = s;
					npcTemp->name += b;
				}
				else if(tokens[0] == "SYMB")
				{
					symb++;
					if(tokens.size() != 2)
					{
						symb++;
					}
					else if(tokens[1].size() != 1)
					{
						symb++;
					}
					else
					{
						string temp;
						temp+= tokens[1];
						npcTemp->symbol = temp[0];
					//	thisMonster.push_back(temp);
					}
				}
				else if(tokens[0] == "COLOR")
				{
					color++;
					if(!(tokens.size() >= 2))
						color++;
					string temp;
					unsigned int i = 1;
					while (i < tokens.size())
					{
						temp+= (tokens[i++] + " ");
					}
					if(tokens[1] == "BLACK")
					{
						npcTemp->color = COLOR_BLACK;
					}
					else if(tokens[1] == "RED")
					{
						npcTemp->color = COLOR_RED;
					}
					else if(tokens[1] == "GREEN")
					{
						npcTemp->color = COLOR_GREEN;
					}
					else if(tokens[1] == "YELLOW")
					{
						npcTemp->color = COLOR_YELLOW;
					}
					else if(tokens[1] == "BLUE")
					{
						npcTemp->color = COLOR_BLUE;
					}
					else if(tokens[1] == "MAGENTA")
					{
						npcTemp->color = COLOR_MAGENTA;
					}
					else if(tokens[1] == "CYAN")
					{
						npcTemp->color = COLOR_CYAN;
					}
					else if(tokens[1] == "WHITE")
					{
						npcTemp->color = COLOR_WHITE;
					}
					temp.erase(temp.size()-1,1);
				//	thisMonster.push_back(temp);
				}
				else if(tokens[0] == "DESC")
				{
					vector<string> fullDesc;
					desc++;
					if(tokens.size() != 1)
						desc++;
					getline(f, s); //gets line after DESC
					if(f.eof())
						break;
					if(s != "")
				{
				if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
					s.erase(s.size()-1,1);
				}
					
					while(1) // read all desc
					{
						if (s.size() > 77)
						{
							desc++;
						}
							
					//	thisMonster.push_back(s);
						
						fullDesc.push_back(s);	
						
						getline(f, s); 
						if(f.eof())
							break;
						if(s != "")
				{
				if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
					s.erase(s.size()-1,1);
				}
						if(s == "." || f.eof() || s == "END")
							break;		
					}
					string temp2;
					for(unsigned int j = 0; j < fullDesc.size(); j++)
					{
						temp2+=fullDesc[j];
						temp2+='\n';
					}
					string b2 = temp2;
					npcTemp->desc += b2;
				}
				else if(tokens[0] == "SPEED")
				{
					Dice d;
					int plusPos;
					int dPos;
					string base;
					string dice;
					string sides;
					speed++;
					if(tokens.size() != 2)
						speed++;
					string temp;
					unsigned int i = 1;
					while (i < tokens.size())
					{
						temp+= (tokens[i++] + " ");
					}
					temp.erase(temp.size()-1,1);
					plusPos = temp.find_first_of('+') + 1;
					dPos = temp.find_first_of('d') + 1;
					base = temp.substr(0,plusPos);
					dice = temp.substr(plusPos, dPos - plusPos);
					sides = temp.substr(dPos, temp.size() - dPos);
					d.base = atoi(base.c_str());
					d.dice = atoi(dice.c_str());
					d.sides = atoi(sides.c_str());
					npcTemp->speedDice = d;
					//thisMonster.push_back(temp);
				}
				else if(tokens[0] == "ABIL")
				{
					npcTemp->characteristics = 0x0;
					abil++;
					if(!(tokens.size() >= 2))
						abil++;
					string temp;
					unsigned int i = 1;
					while (i < tokens.size())
					{
						temp+= (tokens[i++] + " ");
					}
					for (unsigned int j = 1; j < tokens.size(); j++)
					{
						if(tokens[j] == "SMART")
						{
							npcTemp->characteristics = npcTemp->characteristics | INTELLIGENT;
						}
						else if(tokens[j] == "TELE")
						{
							npcTemp->characteristics = npcTemp->characteristics | TELEPATHIC;
						}
						else if(tokens[j] == "TUNNEL")
						{
							npcTemp->characteristics = npcTemp->characteristics | TUNNELING;
						}
						else if(tokens[j] == "ERRATIC")
						{
							npcTemp->characteristics = npcTemp->characteristics | ERRATIC;
						}
						else if(tokens[j] == "PASS")
						{
							npcTemp->characteristics = npcTemp->characteristics | PASS;
						}
						else if(tokens[j] == "PICKUP")
						{
							npcTemp->characteristics = npcTemp->characteristics | PICKUP;
						}
						else if(tokens[j] == "DESTROY")
						{
							npcTemp->characteristics = npcTemp->characteristics | DESTROY;
						}
						else if(tokens[j] == "UNIQ")
						{
							npcTemp->characteristics = npcTemp->characteristics | UNIQ;
						}
					}
					temp.erase(temp.size()-1,1);
					//thisMonster.push_back(temp);
				}
				else if(tokens[0] == "HP")
				{
					Dice d;
					int plusPos;
					int dPos;
					string base;
					string dice;
					string sides;
					hp++;
					if(tokens.size() != 2)
						hp++;
					string temp;
					unsigned int i = 1;
					while (i < tokens.size())
					{
						temp+= (tokens[i++] + " ");
					}
					temp.erase(temp.size()-1,1);
					plusPos = temp.find_first_of('+') + 1;
					dPos = temp.find_first_of('d') + 1;
					base = temp.substr(0,plusPos);
					dice = temp.substr(plusPos, dPos - plusPos);
					sides = temp.substr(dPos, temp.size() - dPos);
					d.base = atoi(base.c_str());
					d.dice = atoi(dice.c_str());
					d.sides = atoi(sides.c_str());
					npcTemp->hpDice = d;
					//thisMonster.push_back(temp);
				}
				else if(tokens[0] == "DAM")
				{
					Dice d;
					int plusPos;
					int dPos;
					string base;
					string dice;
					string sides;
					dam++;
					if(tokens.size() != 2)
						dam++;
					string temp;
					unsigned int i = 1;
					while (i < tokens.size())
					{
						temp+= (tokens[i++] + " ");
					}
					temp.erase(temp.size()-1,1);
					plusPos = temp.find_first_of('+') + 1;
					dPos = temp.find_first_of('d') + 1;
					base = temp.substr(0,plusPos);
					dice = temp.substr(plusPos, dPos - plusPos);
					sides = temp.substr(dPos, temp.size() - dPos);
					d.base = atoi(base.c_str());
					d.dice = atoi(dice.c_str());
					d.sides = atoi(sides.c_str());
					npcTemp->damDice = d;
				//	thisMonster.push_back(temp);
				}
				else 
				{
					invalidLines++;
				}
				getline(f, s); 
				if(f.eof())
					break;
				if(s != "")
				{
				if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
					s.erase(s.size()-1,1);
				}
				while(s == "")
				{
				getline(f,s);
				if(f.eof())
					break;
				if(s != "")
				{
				if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
					s.erase(s.size()-1,1);
				}
				}
				if(s == "END" || s == "BEGIN MONSTER" || s == "EN")
					break;
			
			}
			
			if(name != 1 || symb != 1 || desc != 1 || color != 1 || 
			speed != 1 || abil != 1 || hp != 1 || dam != 1 || invalidLines != 0)
				{
				failed = true;
				}
			if(failed) 
			{
				delete npcTemp;
			}
			else
			{
				//for (unsigned int i = 0; i < thisMonster.size(); i++) 
			//	{
			//		cout << thisMonster[i] << endl;
			//	}
			//	cout << "\n";
				npcTemp->isSpawned = 0;
				npcTemp->hasDied = 0;
				npcTemplates.push_back(npcTemp);
			}
			if(f.eof())
				break;
			if(s == "EN")
				break;
			
		}
	return 0;
}

int parseObjects(std::ifstream &f, std::vector<Object *> &objectTemplates)
{
	if(!f) 
		{
			cerr << "error opening object_desc.txt" << endl;
		}
		string s;
		getline(f, s);
		if(!f.eof())
		{
			if(s != "")
				{
				if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
					s.erase(s.size()-1,1);
				}
			if(s != "RLG327 OBJECT DESCRIPTION 1") 
			{
				cerr << "incorrect description file format (first line incorrect)" << endl;
				//exit(1);
			}
		}
		while(!f.eof())
		{
			bool failed = false; //these detect errors; useful for debugging as well as telling
			int name = 0;
			int type = 0;
			int desc = 0;
			int color = 0;
			int speed = 0;
			int attr = 0;
			int hit = 0;
			int dam = 0;
			int dodge = 0;
			int def = 0;
			int val = 0;
			int weight = 0;
			int invalidLines = 0;   //the parser to throw out the current object
			getline(f, s);
			if(f.eof())
				break;
			if(s != "")
			{
			if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
				s.erase(s.size()-1,1);
			}
			Object *objectTemp = new Object();
			
			while(s != "BEGIN OBJECT" && !(f.eof())) 
			{
				getline(f, s);
				if(f.eof())
					break;
				if(s != "")
				{
				if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
					s.erase(s.size()-1,1);
				}
			}
			if(f.eof())
				break;
			getline(f, s); //line after BEGIN OBJECT
			if(f.eof())
				break;
			if(s != "")
				{
				if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
					s.erase(s.size()-1,1);
				}
			while(1) // this current object block
			{
				
				string buf;
				vector<string> tokens;
				stringstream ss(s);
			
				while (ss >> buf)
					tokens.push_back(buf); //tokens now has every word split by whitespace
				
				if(tokens[0] == "NAME") 
				{
					name++;
					if(!(tokens.size() >= 2))
						name++;
					s.erase(0,5);
					string b = s;
					objectTemp->name += b;
				}
				
				else if(tokens[0] == "TYPE") 
				{
					type++;
					if(!(tokens.size() == 2))
						type++;
					if(tokens[1] == "WEAPON")
					objectTemp->type = 1;
					else if(tokens[1] == "OFFHAND")
					objectTemp->type = 2;
					else if(tokens[1] == "RANGED")
					objectTemp->type = 3;
					else if(tokens[1] == "LIGHT")
					objectTemp->type = 4;
					else if(tokens[1] == "ARMOR")
					objectTemp->type = 5;
					else if(tokens[1] == "HELMET")
					objectTemp->type = 6;
					else if(tokens[1] == "CLOAK")
					objectTemp->type = 7;
					else if(tokens[1] == "GLOVES")
					objectTemp->type = 8;
					else if(tokens[1] == "BOOTS")
					objectTemp->type = 9;
					else if(tokens[1] == "AMULET")
					objectTemp->type = 10;
					else if(tokens[1] == "RING")
					objectTemp->type = 11;
					else if(tokens[1] == "SCROLL")
					objectTemp->type = 12;
					else if(tokens[1] == "BOOK")
					objectTemp->type = 13;
					else if(tokens[1] == "FLASK")
					objectTemp->type = 14;
					else if(tokens[1] == "GOLD")
					objectTemp->type = 15;
					else if(tokens[1] == "AMMUNITION")
					objectTemp->type = 16;
					else if(tokens[1] == "FOOD")
					objectTemp->type = 17;
					else if(tokens[1] == "WAND")
					objectTemp->type = 18;
					else if(tokens[1] == "CONTAINER")
					objectTemp->type = 19;
					else 
					objectTemp->type = 0;
	
				}
				
				else if(tokens[0] == "COLOR")
				{
					color++;
					if(!(tokens.size() >= 2))
						color++;
					string temp;
					unsigned int i = 1;
					while (i < tokens.size())
					temp+= (tokens[i++] + " ");
					if(tokens[1] == "BLACK")
					objectTemp->color = COLOR_BLACK;
					else if(tokens[1] == "RED")
					objectTemp->color = COLOR_RED;
					else if(tokens[1] == "GREEN")
					objectTemp->color = COLOR_GREEN;
					else if(tokens[1] == "YELLOW")
					objectTemp->color = COLOR_YELLOW;
					else if(tokens[1] == "BLUE")
					objectTemp->color = COLOR_BLUE;
					else if(tokens[1] == "MAGENTA")
					objectTemp->color = COLOR_MAGENTA;
					else if(tokens[1] == "CYAN")
					objectTemp->color = COLOR_CYAN;
					else if(tokens[1] == "WHITE")
					objectTemp->color = COLOR_WHITE;
					temp.erase(temp.size()-1,1);
				}
				else if(tokens[0] == "DESC")
				{
					vector<string> fullDesc;
					desc++;
					if(tokens.size() != 1)
						desc++;
					getline(f, s); //gets line after DESC
					if(f.eof())
						break;
					if(s != "")
					{
						if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
							s.erase(s.size()-1,1);
					}
					
					while(1) // read all desc
					{
						if (s.size() > 77)
						{
							desc++;
						}
							
						
						fullDesc.push_back(s);	
						
						getline(f, s); 
						if(f.eof())
							break;
						if(s != "")
					{
						if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
							s.erase(s.size()-1,1);
					}
						if(s == "." || f.eof() || s == "END")
							break;		
					}
					string temp2;
					for(unsigned int j = 0; j < fullDesc.size(); j++)
					{
						temp2+=fullDesc[j];
						temp2+='\n';
					}
					string b2 = temp2;
					objectTemp->desc += b2;
				}
				else if(tokens[0] == "SPEED")
				{
					Dice d;
					int plusPos;
					int dPos;
					string base;
					string dice;
					string sides;
					speed++;
					if(tokens.size() != 2)
						speed++;
					string temp;
					unsigned int i = 1;
					while (i < tokens.size())
					{
						temp+= (tokens[i++] + " ");
					}
					temp.erase(temp.size()-1,1);
					plusPos = temp.find_first_of('+') + 1;
					dPos = temp.find_first_of('d') + 1;
					base = temp.substr(0,plusPos);
					dice = temp.substr(plusPos, dPos - plusPos);
					sides = temp.substr(dPos, temp.size() - dPos);
					d.base = atoi(base.c_str());
					d.dice = atoi(dice.c_str());
					d.sides = atoi(sides.c_str());
					objectTemp->speedDice = d;
				}
				else if(tokens[0] == "HIT")
				{
					Dice d;
					int plusPos;
					int dPos;
					string base;
					string dice;
					string sides;
					hit++;
					if(tokens.size() != 2)
						hit++;
					string temp;
					unsigned int i = 1;
					while (i < tokens.size())
					{
						temp+= (tokens[i++] + " ");
					}
					temp.erase(temp.size()-1,1);
					plusPos = temp.find_first_of('+') + 1;
					dPos = temp.find_first_of('d') + 1;
					base = temp.substr(0,plusPos);
					dice = temp.substr(plusPos, dPos - plusPos);
					sides = temp.substr(dPos, temp.size() - dPos);
					d.base = atoi(base.c_str());
					d.dice = atoi(dice.c_str());
					d.sides = atoi(sides.c_str());
					objectTemp->hitDice = d;
				}
				else if(tokens[0] == "WEIGHT")
				{
					Dice d;
					int plusPos;
					int dPos;
					string base;
					string dice;
					string sides;
					weight++;
					if(tokens.size() != 2)
						weight++;
					string temp;
					unsigned int i = 1;
					while (i < tokens.size())
					{
						temp+= (tokens[i++] + " ");
					}
					temp.erase(temp.size()-1,1);
					plusPos = temp.find_first_of('+') + 1;
					dPos = temp.find_first_of('d') + 1;
					base = temp.substr(0,plusPos);
					dice = temp.substr(plusPos, dPos - plusPos);
					sides = temp.substr(dPos, temp.size() - dPos);
					d.base = atoi(base.c_str());
					d.dice = atoi(dice.c_str());
					d.sides = atoi(sides.c_str());
					objectTemp->weightDice = d;
				}
				else if(tokens[0] == "ATTR")
				{
					Dice d;
					int plusPos;
					int dPos;
					string base;
					string dice;
					string sides;
					attr++;
					if(tokens.size() != 2)
						attr++;
					string temp;
					unsigned int i = 1;
					while (i < tokens.size())
					{
						temp+= (tokens[i++] + " ");
					}
					temp.erase(temp.size()-1,1);
					plusPos = temp.find_first_of('+') + 1;
					dPos = temp.find_first_of('d') + 1;
					base = temp.substr(0,plusPos);
					dice = temp.substr(plusPos, dPos - plusPos);
					sides = temp.substr(dPos, temp.size() - dPos);
					d.base = atoi(base.c_str());
					d.dice = atoi(dice.c_str());
					d.sides = atoi(sides.c_str());
					objectTemp->attrDice = d;
				}
				else if(tokens[0] == "VAL")
				{
					Dice d;
					int plusPos;
					int dPos;
					string base;
					string dice;
					string sides;
					val++;
					if(tokens.size() != 2)
						val++;
					string temp;
					unsigned int i = 1;
					while (i < tokens.size())
					{
						temp+= (tokens[i++] + " ");
					}
					temp.erase(temp.size()-1,1);
					plusPos = temp.find_first_of('+') + 1;
					dPos = temp.find_first_of('d') + 1;
					base = temp.substr(0,plusPos);
					dice = temp.substr(plusPos, dPos - plusPos);
					sides = temp.substr(dPos, temp.size() - dPos);
					d.base = atoi(base.c_str());
					d.dice = atoi(dice.c_str());
					d.sides = atoi(sides.c_str());
					objectTemp->valDice = d;
				}
				else if(tokens[0] == "DODGE")
				{
					Dice d;
					int plusPos;
					int dPos;
					string base;
					string dice;
					string sides;
					dodge++;
					if(tokens.size() != 2)
						dodge++;
					string temp;
					unsigned int i = 1;
					while (i < tokens.size())
					{
						temp+= (tokens[i++] + " ");
					}
					temp.erase(temp.size()-1,1);
					plusPos = temp.find_first_of('+') + 1;
					dPos = temp.find_first_of('d') + 1;
					base = temp.substr(0,plusPos);
					dice = temp.substr(plusPos, dPos - plusPos);
					sides = temp.substr(dPos, temp.size() - dPos);
					d.base = atoi(base.c_str());
					d.dice = atoi(dice.c_str());
					d.sides = atoi(sides.c_str());
					objectTemp->dodgeDice = d;
				}
				else if(tokens[0] == "DEF")
				{
					Dice d;
					int plusPos;
					int dPos;
					string base;
					string dice;
					string sides;
					def++;
					if(tokens.size() != 2)
						def++;
					string temp;
					unsigned int i = 1;
					while (i < tokens.size())
					{
						temp+= (tokens[i++] + " ");
					}
					temp.erase(temp.size()-1,1);
					plusPos = temp.find_first_of('+') + 1;
					dPos = temp.find_first_of('d') + 1;
					base = temp.substr(0,plusPos);
					dice = temp.substr(plusPos, dPos - plusPos);
					sides = temp.substr(dPos, temp.size() - dPos);
					d.base = atoi(base.c_str());
					d.dice = atoi(dice.c_str());
					d.sides = atoi(sides.c_str());
					objectTemp->defDice = d;
				}
				else if(tokens[0] == "DAM")
				{
					Dice d;
					int plusPos;
					int dPos;
					string base;
					string dice;
					string sides;
					dam++;
					if(tokens.size() != 2)
						dam++;
					string temp;
					unsigned int i = 1;
					while (i < tokens.size())
					{
						temp+= (tokens[i++] + " ");
					}
					temp.erase(temp.size()-1,1);
					plusPos = temp.find_first_of('+') + 1;
					dPos = temp.find_first_of('d') + 1;
					base = temp.substr(0,plusPos);
					dice = temp.substr(plusPos, dPos - plusPos);
					sides = temp.substr(dPos, temp.size() - dPos);
					d.base = atoi(base.c_str());
					d.dice = atoi(dice.c_str());
					d.sides = atoi(sides.c_str());
					objectTemp->damDice = d;
				}
				else 
				{
					invalidLines++;
				}
				getline(f, s); 
				if(f.eof())
					break;
				if(s != "")
				{
				if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
					s.erase(s.size()-1,1);
				}
				while(s == "")
				{
				getline(f,s);
				if(f.eof())
					break;
				if(s != "")
				{
				if(s[s.size()- 1] == '\n' || s[s.size()- 1] == '\r')
					s.erase(s.size()-1,1);
				}
				}
				if(s == "END" || s == "BEGIN OBJECT" || s == "EN")
					break;
			
			}
			
			if(name != 1 || type != 1 || desc != 1 || color != 1 || 
			speed != 1 || attr != 1 || hit != 1 || dam != 1 || dodge != 1 || 
			def != 1 || weight != 1 || val != 1 || invalidLines != 0)
				{
				failed = true;
				}
			if(failed) 
			{
				delete objectTemp;
			}
			else
			{
				objectTemplates.push_back(objectTemp);
			}
			if(f.eof())
				break;
			if(s == "EN")
				break;
			
		}
	return 0;
}