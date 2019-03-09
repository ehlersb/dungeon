#include "queue.h"

int queueInit(Queue *q) 
{
	q->size = 0;
	q->head = q->tail = NULL;
	return 0;
}

int queueDelete(Queue *q)
{
	int i;
	int j;

	while(!queueRemove(q, &i, &j))
	;
	return 0;
}

/*int queueAdd(Queue *q, int v, int d)
{
	if(q->head)
	{
		if(!q->tail->next = malloc(sizeof(Node)))
		{
			fprintf(stderr, "Error in queueAdd\n");
			return 1;
		}
		
		q->tail = q->tail->next;
		q->tail->value = v;
		q->tail->dist = d;
		q->tail->next = NULL;
		size++;
		return 0;
	}
	else
	{
		if(!(q->tail = q->head = malloc(sizeof(*q->tail))))
		{
			fprintf(stderr, "Error in queueAdd\n");
		}
		q->tail->value = v;
		q->tail->value = d;
		q->tail->next = NULL;
		q->size++;
	}
}*/

int queueRemove(Queue *q, int *d, int *l)
{
	Node *n;
	if(!q->size)
	{
		//fprintf(stderr, "Tried to remove an empty Queue(Queue delete)\n");
		return 1;
	}
	n = q->head;
	q->head = q->head->next;
	q->size--;
	*d = n->dist;
	*l = n->location;
	free(n);
	if(!q->size)
	{
		q->tail = q->head = NULL;
	}
	return 0;
}

int queueRemoveEvent(Queue *q, int l)
{
	int temp = 0;
	Node *n = q->head;
	if(!q->size)
	{
		//fprintf(stderr, "Tried to remove an empty Queue(Queue delete)\n");
		return 1;
	}
	for(int i = 0; i < q->size; i++)
	{
		if(n->location == l)
		{
			if(n == q->head) 
			{
				q->head = q->head->next;
			}
			if(n == q->tail)
			{
				q->tail = q->tail->prev;
			}
			if(n->prev)
			{
				n->prev->next = n->next;
			}
			if(n->next)
			{
				n->next->prev = n->prev;
			}
			temp = n->dist;
			q->size--;
			free(n);
			return temp;
		}
		n=n->next;
	}
	return -1;
}

int decreasePriority(Queue *q, int location, int d)
{
	Node *temp = q->head;
	for (int i = 0; i < q->size; i++) 
	{
		if(temp->location == location) 
		{
			temp->dist = d;
			return 0;
		}
		else
		{
			temp = temp->next;
		}
	}
	return -1;
}
int decreasePriorityEvent(Queue *q, int location, int d) 
{
	Node *temp = q->head;
	for (int i = 0; i < q->size; i++) 
	{
		if(temp->location == location) 
		{
			if(temp->dist - d < 0)
			{
				temp->dist = 0;
			}
			else
			{
				temp->dist = temp->dist - d;
			}
			return 0;
		}
		
		temp = temp->next;
		
	}
	return -1;
}

int addWithPriority(Queue *q, int location, int d)
{
	Node *n = (Node *) malloc(sizeof(Node));
	n->dist = d;
	n->location = location;
	n->next = NULL;
	if(q->head) //if not empty
	{
		Node *temp = q->head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = n;
		n->prev = temp;
		q->tail = n;
		q->size++;
		return 0;
	}
	else // if empty
	{
		n->prev = NULL;
		q->head = n;
		q->tail = n;
		q->size++;
		return 0;
	}
	return 0;
}

int extractMin(Queue *q)
{
	Node *n = q->head;
	int lowest = 255;
	if(!q->size)
	{
		fprintf(stderr, "Tried to remove an empty Queue(extract min)\n");
		return -1;
	}
	for(int i = 0; i < q->size; i++) // find lowest priority
	{
		if(n->dist < lowest)
		{
			lowest = n->dist;
		}
		n = n->next;
	}
	n = q->head;
	for (int i = 0; i < q->size; i++) // remove lowest priority (chooses first lowest in Queue
	{								  // 						in the case of multiple lowests)
		if(n->dist == lowest) //if current Node dist matches
		{
			int loc = n->location;
			if(n == q->head) 
			{
				q->head = q->head->next;
			}
			if(n == q->tail)
			{
				q->tail = q->tail->prev;
			}
			if(n->prev)
			{
				n->prev->next = n->next;
			}
			if(n->next)
			{
				n->next->prev = n->prev;
			}
			
			q->size--;
			free(n);
			return loc;
		}
		n = n->next;
	}
	return -1;//dead code
}

int extractMinEvent(Queue *q, int sequences[], int *p)
{
	Node *n = q->head;
	int lowest = 255;
	if(!q->size)
	{
		fprintf(stderr, "Tried to remove an empty Queue(extract min)\n");
		return -1;
	}
	int numTies = -1;
	int seqLowest = 2000;
	for(int i = 0; i < q->size; i++) // find lowest priority
	{
		if(n->dist < lowest)
		{
			lowest = n->dist;
		}
		n = n->next;
	}
	n = q->head;
	for(int i = 0; i < q->size;i++)
	{
		if(n->dist == lowest)
		{
			numTies++;
			if(sequences[n->location] < seqLowest)
			{
				seqLowest = sequences[n->location];
			}
		}
		n = n->next;
	}
	n = q->head;
	//if numTies > 0 get and remove lowest sequence of the ties
	if(numTies > 0) 
	{
		for (int i = 0; i < q->size; i++) 
		{								  
			if(sequences[n->location] == seqLowest) //if current Node matches seqLowest
			{
				*p = n->dist;
				int loc = n->location;
				if(n == q->head) 
				{
					q->head = q->head->next;
				}
				if(n == q->tail)
				{
					q->tail = q->tail->prev;
				}
				if(n->prev)
				{
					n->prev->next = n->next;
				}
				if(n->next)
				{
					n->next->prev = n->prev;
				}
				
				q->size--;
				free(n);
				return loc;
			}
			n = n->next;
		}
	}
	else 
	{
		for (int i = 0; i < q->size; i++) // remove lowest priority (chooses first lowest in Queue
		{								  // 						in the case of multiple lowests)
			if(n->dist == lowest) //if current Node dist matches
			{
				*p = n->dist;
				int loc = n->location;
				if(n == q->head) 
				{
					q->head = q->head->next;
				}
				if(n == q->tail)
				{
					q->tail = q->tail->prev;
				}
				if(n->prev)
				{
					n->prev->next = n->next;
				}
				if(n->next)
				{
					n->next->prev = n->prev;
				}
				q->size--;
				free(n);
				return loc;
			}
			n = n->next;
		}
	}
	return -1;//dead code
}

void dijkstraNormal(Cell dungeon[][80], int source, char *normalWeightMap)
{	
	int size = 0; //num of vertices
	for (int i = 0; i < 1680;i++) 
	{
		if(dungeon[i / 80][i % 80].hardness == 0)
		{
			size++;
		}
	}

	int *verticesL = (int *) malloc(size * sizeof(int)); //locations of vertices
	int j = 0;
	for (int i = 0; i < 1680;i++) // populating verticesL
	{
		if(dungeon[i / 80][i % 80].hardness == 0)
		{
			verticesL[j++] = i;
		}
	}
	int *vertices = (int *) malloc(1680 * sizeof(int)); //vertex dists/priorities
	for (int i = 0; i < size;i++)
	{		
		if(verticesL[i] != source)
		{
			vertices[verticesL[i]] = 255;
		}
		
	}
	vertices[source] = 0; // graph initialized

	Queue *q = (Queue *) malloc(sizeof(Queue));
	queueInit(q);
	
	for (int i = 0; i < size;i++)
	{
		addWithPriority(q, verticesL[i], vertices[verticesL[i]]);
	}
	while(q->size) 
	{
		int u = extractMin(q);//returns location in 1680 array
		int numNeighbors = calculateNumNeighbors(dungeon, u);
		int *neighbors = (int *) malloc(numNeighbors * sizeof(int));
		initNeighbors(dungeon, numNeighbors, u, neighbors);
		for (int i = 0; i < numNeighbors;i++) 
		{
			int temp = vertices[u] + 1;
			if(temp < vertices[neighbors[i]])
			{
				vertices[neighbors[i]] = temp;
				decreasePriority(q, neighbors[i], temp);
			}
		}
		free(neighbors);
	}

	for (int i = 0; i < 1680;i++)
	{
		normalWeightMap[i] = ' ';
	}
	
	for (int i = 0; i < size; i++)
	{
		int temp2 = 255;
		int ivertex = verticesL[i];
		int d = MIN((vertices[ivertex]),temp2);
		/*char dist[3];
		sprintf(dist, "%d", d);
		char di = dist[strlen(dist)-1];*/
		normalWeightMap[ivertex] = (char)d;
	}
	//normalWeightMap[source] = '@';
	queueDelete(q);
	free(q);
	free(vertices);
	free(verticesL);
	
}

void dijkstraTunneling(Cell dungeon[][80], int source, char *normalWeightMap)
{	
	int *vertices = (int *) malloc(1680 * sizeof(int)); //vertex dists/priorities
	for (int i = 0; i < 1680;i++)
	{	
		vertices[i] = 255;		
	}
	vertices[source] = 0; // graph initialized

	Queue *q = (Queue *) malloc(sizeof(Queue));
	queueInit(q);
	
	for (int i = 1; i < 79;i++)
	{
		for (int j = 1; j < 20; j++) 
		{
			addWithPriority(q, ((j*80)+i), vertices[(j*80) + i]);
		}
		
	}
	while(q->size) 
	{
		int u = extractMin(q);//returns location in 1680 array
		int numNeighbors = 8; 
		int *neighbors = (int *) malloc(numNeighbors * sizeof(int)); // holds locations of each neighbor
		initNeighborsTunneling(numNeighbors, u, neighbors);
		for (int i = 0; i < numNeighbors;i++) 
		{
			int y = neighbors[i] / 80;
			int x = neighbors[i] % 80;
			int temp;
			//if(dungeon[u/80][u%80].hardness == 0) 
			//{
			//	temp = vertices[u] + 1;
			//}
			//else 
			//{
			temp = vertices[u] + (1 + (dungeon[y][x].hardness / 85));
			//	}
			if(temp < vertices[neighbors[i]])
			{
				vertices[neighbors[i]] = temp;
				decreasePriority(q, neighbors[i], temp);
			}
		}
		free(neighbors);
	}

	for (int i = 0; i < 1680;i++)
	{
		normalWeightMap[i] = ' ';
	}
	
	for (int i = 1; i < 79; i++)
	{
		for (int j = 1; j < 20;j++) 
		{
			int temp2 = 255;
			int d = MIN(vertices[i+(j*80)],temp2);
			/*char dist[3];
			sprintf(dist, "%d", d);
			char di = dist[strlen(dist)-1];*/
			normalWeightMap[i+(j*80)] = (char)d;
		}
		
	}
	//normalWeightMap[source] = '@';
	queueDelete(q);
	free(q);
	free(vertices);
	
}

/*int peek(Queue *q, int *v)
{
	if(q->size)
	{
		*v = q->head->value;
		return 0;
	}
	return 1;
}*/