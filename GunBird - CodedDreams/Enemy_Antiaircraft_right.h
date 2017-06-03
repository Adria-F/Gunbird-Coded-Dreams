#ifndef __ANTIAIRCRAFT_RIGHT_H__
#define __ANTIAIRCRAFT_RIGHT_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Antiaircraft_right : public Enemy
{
public:

	Enemy_Antiaircraft_right(int x, int y, int id);
	~Enemy_Antiaircraft_right();

	void Move();
	void DeadAnim();

public:

	Path path;

	Animation right_closed;
	Animation right_opening;
	Animation right_idle;
	Animation right_death;

	int state = 0;
	bool collider_state = 0;
};

#endif // !__ANTIAIRCRAFT_RIGHT_H__
