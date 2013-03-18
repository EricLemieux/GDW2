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

	//std::vector<std::vector<int>> numbers;
	
	std::vector<int> num;
	node newNode;

	//When the program is not done reading the file continue to read in the file.
	while(!file.eof())
	{
		char stuff[256];
		file>>stuff;
		std::cout<<stuff<<std::endl;

		if(strcmp(stuff,"NODE:")){
			if(!strcmp(stuff,";")){
				//total.push_back(num);
				//total.push_back(some node yet to be made);
				newNode.whoControls = 0;
				total.push_back(newNode);
				newNode.connections.clear();
				//num.clear();
				count++;
				i = -1;
			}
			else
				if(i == 0)
					newNode.XPos = atoi(stuff);
				else if(i == 1)
					newNode.YPos = atoi(stuff);
				else
				{
					newNode.connections.push_back(atoi(stuff));
				}
			i++;
		}
	}
}

Map::~Map(void)
{
	//TODO?
}

//This function tests if the movement is possible.
//it takes in the current position and the position the user wants to move to.
bool Map::canMove(int currentPos, int newPos)
{
	currentPos--;
	for(int i = 0; i<total.at(currentPos).connections.size(); i++)
	{
		if(total.at(currentPos).connections.at(i) == newPos)
			return true;
	}
	return false;
}

bool Map::canAttack(int currentPos, int posAttcking)
{
	//TODO or not...
	return true;
}

//returns what node the user has clicked on.
std::vector<int> Map::getNodes(int x, int y)
{
	std::vector<int> nodesToBeReturned;
	for(int i = 0; i < total.size(); i++)
	{
		if(total.at(i).XPos > x-50 && total.at(i).XPos < x+50)
		{
			if(total.at(i).YPos > y-50 && total.at(i).YPos < y+50)
			{
				nodesToBeReturned.push_back(i);
			}
		}
	}
	return nodesToBeReturned;
}

/*//returns the size of the map.
int Map::getMapSize()
{
	return int(total.size());
}*/

/*//returns the X-Positions of all of the nodes in the map.
std::vector<int> Map::getXPosValues()
{
	for(int count = 0 ; count < total.size() ; count++)
	{
		XPosValues.push_back(newNode.XPos);
	}
	return XPosValues;
}

//Returns the Y-Positions of all of the nodes in the map.
std::vector<int> Map::getYPosValues()
{
	for(int count = 0 ; count < total.size() ; count++)
	{
		//YPosValues.push_back(newNode.YPos);
	}
	return YPosValues;
}*/