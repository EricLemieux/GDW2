//Map.h
//This is the class for the map, for the GDW semester 2 game

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#pragma once

//The maximum distance that the user can move using the move command.
static short maxMoveDistance = 1;

struct node{
	std::vector<node> connections;
	int ID;
	int data;
};

class Map
{
public:
	Map(void);
	Map(std::string fileName);
	~Map(void);

	bool canMove(int currentPos, int newPos);

	int getMapSize();

	std::vector<int> getXPosValues();
	std::vector<int> getYPosValues();

private:
	std::vector<std::vector<int>> total;

	int mapSize;
	std::vector<int> XPosValues;
	std::vector<int> YPosValues;
};

