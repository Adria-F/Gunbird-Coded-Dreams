#ifndef __LEFTSIDE_H__
#define __LEFTSIDE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_LeftSide : public Enemy
{
public:

	Enemy_LeftSide(int x, int y);
	~Enemy_LeftSide();

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
