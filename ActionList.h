#pragma once

class ActionList{
public:
	ActionList(void);
	~ActionList(void);

	void Wait();
	void Move(int currentX, int currentY);
	void Capture(int currentX, int currentY, int cityState);
	void Attack(int currentX, int currentY);
	void Defend(int currentX, int currenty);
	
	void Execute();

	//wait = 0, move = 1...
	int action;
	//stores actions in order
	int actionList[6];

private:
	int executionOrder;
};