#ifndef __ANTIAIRCRAFT_LEFT_H__
#define __ANTIAIRCRAFT_LEFT_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Antiaircraft_left : public Enemy
{
public:

	Enemy_Antiaircraft_left(int x, int y, int id);
	~Enemy_Antiaircraft_left();

	void Move();
	void DeadAnim();

public:

	Path path;

	Animation left_closed;
	Animation left_opening;
	Animation left_idle;
	Animation left_death;
	bool collider_state = 0;


	int state = 0;

};

#endif // !__ANTIAIRCRAFT_LEFT_H__
