//Map.cpp

#include "Map.h"
#include <iostream>

Map::Map(void)
{
	headOfList = tailOfList = NULL;
	sizeOfList = 0;

	//loops throught the list initialising all of the list.
	for(short n = 1; n<=21;n++)
	{
		add(n);
	}

	std::cout<<"New map list created.\n";
}

Map::~Map(void)
{
	//TODO
}

void Map::add(short ID, short p1, short p2, short p3, short p4)
{
	short p[5];
	p[1] = p1;
	p[2] = p2;
	p[3] = p3;
	p[4] = p4;

	position = headOfList;
	node *temp = new node;
	bool exit = false;

	

	for(int count = 0; count<=4; count++)
	{
		exit = false;
		while(!exit)
		{
			if(count == 0)
			{
				while(!exit)
				{
					if(position->IDNumber == ID)
					{
						temp = position;
						exit = true;
					}
					position = position->next;
				}
			}

			if(count >0 && count <=4)
			{
				if(position->IDNumber == p[count])
				{
					temp->connection[count] = position;
					exit = true;
				}
				else
					position = position->next;
			}
		}
	}

	
}

void Map::add(int i)
{
	node *temp = new node;
	temp->IDNumber = i;
	temp->next = NULL;

	if(headOfList==NULL)
	{
		headOfList = tailOfList = position = temp;
	}
	else
	{
		tailOfList->next = temp;
		tailOfList = temp;
		tailOfList->previous = position;
		position = temp;
	}
	sizeOfList++;
}

int Map::size(void)
{
	return sizeOfList;
}

node* Map::getConnections(void)
{
	return headOfList;
}