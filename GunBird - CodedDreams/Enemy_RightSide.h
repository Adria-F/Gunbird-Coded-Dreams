#ifndef __RIGHTSIDE_H__
#define __RIGHTSIDE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_RightSide : public Enemy
{
public:

	Enemy_RightSide(int x, int y);
	~Enemy_RightSide();

	void Move();
	void DeadAnim();
	void Drop();

public:

	int state = 0;
	bool collider_state = 0;
	Path path;
	Animation moving;
	Animation dead;
	Animation notmoving;

};

#endif // !__BALLOON_H__
