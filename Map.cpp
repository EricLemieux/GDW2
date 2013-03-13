#include "Map.h"

//Constructors
Map::Map(void)
{
}
Map::Map(std::string fileName)
{
	//Opens the file that is entered as an argument to the constructor.
	std::fstream file;
	file.open(fileName);

	int count = 0;
	int i = 0;

	std::vector<std::vector<int>> numbers;
	
	std::vector<int> num;

	//When the program is not done reading the file continue to read in the file.
	while(!file.eof())
	{
		char stuff[256];
		file>>stuff;
		std::cout<<stuff<<std::endl;

		if(strcmp(stuff,"NODE:")){
			if(!strcmp(stuff,";")){
				total.push_back(num);
				num.clear();
				count++;
			}
			else
				num.push_back(atoi(stuff));
		}
	}
}

Map::~Map(void)
{
}

//This function tests if the movement is possable.
//it takes in the current position and the position the user wants to move to.
bool Map::canMove(int currentPos, int newPos)
{
	currentPos--;

	for(int count = 3; count <= total.size() ; count++)
	{
		if(total[currentPos].at(0) == (int)total[currentPos].at(count) + maxMoveDistance || total[currentPos].at(0) == (int)total[currentPos].at(count) - maxMoveDistance)
			return true;
	}

	return false;
}

//returns the size of the map.
int Map::getMapSize()
{
	return int(total.size());
}

//returns the X-Positions of all of the nodes in the map.
std::vector<int> Map::getXPosValues()
{
	for(int count = 0 ; count < total.size() ; count++)
	{
		XPosValues.push_back(total[count].at(1));
	}
	return XPosValues;
}

//Returns the Y-Positions of all of the nodes in the map.
std::vector<int> Map::getYPosValues()
{
	for(int count = 0 ; count < total.size() ; count++)
	{
		YPosValues.push_back(total[count].at(2));
	}
	return YPosValues;
}