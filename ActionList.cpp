#include "ActionList.h"



//constructor, possibly turn this into a singleton later
ActionList::ActionList(){
}
//destructor
ActionList::~ActionList(){}


//index numbers 0-4 these are the actual actions
bool ActionList::Wait(){
	return true;
}
void Move(int currentX, int currentY){}
void Capture(int currentX, int currentY, int cityState){}
void Attack(int currentX, int currentY){}
void Defend(int currentX, int currenty){}

