#include "ActionList.h"

ActionList::ActionList(void)
{
	executionOrder = 0;
}

void ActionList::Wait()
{
	//TODO
	executionOrder++;
}

void ActionList::Move(int currentX, int currentY)
{
	//TODO
	executionOrder++;
}
void ActionList::Capture(int currentX, int currentY, int cityState)
{
	//TODO
	executionOrder++;
}
void ActionList::Attack(int currentX, int currentY)
{
	//TODO
	executionOrder++;
}
void ActionList::Defend(int currentX, int currenty)
{
	//TODO
	executionOrder++;
}
	
void ActionList::Execute()
{
	while(executionOrder > 0)
	{
		//TODO
		executionOrder--;
	}
}