#pragma once

class ActionList
{
public:
	ActionList(void);
	~ActionList(void);

	bool Wait();
	void Move(int currentX, int currentY);
	void Capture(int currentX, int currentY, int cityState);
	void Attack(int currentX, int currentY);
	void Defend(int currentX, int currenty);

};