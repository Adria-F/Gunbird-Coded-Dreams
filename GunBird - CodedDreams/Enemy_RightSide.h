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

public:

	Path path;
	Animation moving;

};

#endif // !__BALLOON_H__
