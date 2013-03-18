//Map.h
//This is the class for the map, for the GDW semester 2 game

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#pragma once

//The maximum distance that the user can move using the move command.
const static short maxMoveDistance = 1;
//The maximum distance the player can attack, using the attack command.
const static short maxAttackDistance = 2;
//The aximum distance the user can click and still select the node.
const static int maxDistFromNode = 100;

struct node{
	std::vector<int> connections;
	short whoControls;	//stores who controlls the node, 0 for neutral, 1 for player, -1 for enemy.
	int XPos, YPos;
};

class Map
{
public:
	Map(void);
	Map(std::string fileName);
	~Map(void);

	bool canMove(int currentPos, int newPos);
	bool canAttack(int currentPos, int PosAttacking);

	int getMapSize();

	std::vector<int> getNodes(int x, int y);

	//std::vector<int> getXPosValues();
	//std::vector<int> getYPosValues();

	std::vector<node> total;

private:
	//std::vector<std::vector<int>> total;
	

	//int mapSize;
	//std::vector<int> XPosValues;
	//std::vector<int> YPosValues;
};

