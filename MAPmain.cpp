//main.cpp

#include "Map.h"

using namespace std;

int main()
{
	////vector<node> MAP1;
	//Map MAP1;
	//MAP1 = MAP1.openFile("MAP-0.txt");

	Map MAP1("Maps\\MAP-0.txt");

	/*node NODE1,NODE2,NODE3;
	
	NODE1.ID=1;
	NODE2.ID=2;
	NODE3.ID=3;

	NODE1.connections.push_back(NODE2);
	NODE1.connections.push_back(NODE3);
	NODE1.connections.push_back(NODE1);

	NODE2.connections.push_back(NODE3);
	NODE2.connections.push_back(NODE1);

	MAP1.connections.push_back(NODE1);

	cout<<MAP1.connections.at(0).connections.at(0).ID<<endl;
	cout<<MAP1.connections.at(0).connections.at(1).ID<<endl;
	cout<<MAP1.connections.at(0).connections.at(2).ID<<endl<<endl;*/

	//cout<<MAP1.connections.at(0)<<endl;

	system("pause");

	return 0;
}