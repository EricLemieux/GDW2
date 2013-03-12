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

	//std::vector<std::vector<int>> total;

	int count = 0;
	int i = 0;

	std::vector<std::vector<int>> numbers;
	
	std::vector<int> num;

	//When the program is not done reading the file continue to read in the file.
	while(!file.eof())
	{
		

		//short num;
		
		char stuff[256];
		file>>stuff;
		std::cout<<stuff<<std::endl;

		if(strcmp(stuff,"NODE:")){
			//num.push_back(atoi(stuff));
			/////////numbers.at(i).push_back(atoi(stuff));	//TODO FIX THIS FUCKER!

			num.push_back(atoi(stuff));
			//numbers.push_back(num);
			//numbers.at(0).push_back(2);

			//numbers.at(0).push_back(1);	
			//numbers.at(count).push_back(num);
			//numbers.push_back(num);
			if(!strcmp(stuff,";")){
				//total.at(count).at(i).push_back(numbers);
				total.push_back(num);
				num.clear();
				count++;
			}
			i++;
		}
	}
	//this doesnt really do anything, I just needed it so i could put a breakpoint.
	//TODO remove this thing.
	std::cout<<"end\n";
}

Map::~Map(void)
{
}

//creates the vector using the file given.
std::vector<std::vector<int>> Map::openFile(std::string fileName)
{
	//Opens the file that is entered as an argument to the constructor.
	std::fstream file;
	file.open(fileName);

	std::vector<std::vector<int>> total;

	int count = 0;

	//When the program is not done reading the file coninue to read in the file.
	while(!file.eof())
	{
		std::vector<int> numbers;
		short num;
		char stuff[256];
		file>>stuff;
		std::cout<<stuff<<std::endl;

		//gets the usefull numbers from the text file.
		//So bacically the node number, the X and Y cordinents, and all of the conections that node has.
		if(strcmp(stuff,"NODE:")){
			num = atoi(stuff);
			numbers.push_back(num);
			if(strcmp(stuff,";")){
				count++;
				total.push_back(numbers);
			}
		}
	}
	//this doesnt really do anything, I just needed it so i could put a breakpoint.
	//TODO remove this thing.
	std::cout<<"end\n";

	return total;
}