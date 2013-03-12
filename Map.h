//Map.h
//This is the class for the map, for the GDW semster 2 game

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#pragma once

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

	std::vector<std::vector<int>> openFile(std::string fileName);

	std::vector<std::vector<int>> total;
	std::vector<std::vector<node>> connections;
private:
};

