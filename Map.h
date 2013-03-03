//Map.h
//This is the class for the map file, it is a triple-ly linked list for the nodes on the map.

#pragma once

struct node
{
	short IDNumber;
	/*node *connection1;
	node *connection2;
	node *connection3;
	node *connection4;*/
	node *connection[5];

	//These are used to initialise the list
	int data;
	node *previous;
	node *next;
};

class Map
{
public:
	Map(void);
	~Map(void);

	void add(short ID, short p1, short p2, short p3, short p4);
	void add(int i);

	int size(void);
	node* getConnections(void);

private:
	node *headOfList;
	node *tailOfList;
	node *player1Pos;
	node *player2Pos;
	int sizeOfList;

	//This is used only to initialise the list.
	node *position;
};

