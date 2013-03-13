#include "Map.h"

//Constructor
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