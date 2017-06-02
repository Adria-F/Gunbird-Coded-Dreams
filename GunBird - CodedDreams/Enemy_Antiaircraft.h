#ifndef __ANTIAIRCRAFT_H__
#define __ANTIAIRCRAFT_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Antiaircraft : public Enemy
{
public:

	Enemy_Antiaircraft(int x, int y, int id);
	~Enemy_Antiaircraft();

	void Move();

public:

	Path path;
	Animation idle;

	Animation left_closed;
	Animation left_opening;
	Animation left_idle;
	Animation left_death;

	Animation right_closed;
	Animation right_opening;
	Animation right_idle;
	Animation right_death;

	int state_right;
	int state_left;

};

#endif // !__BALLOON_H__
