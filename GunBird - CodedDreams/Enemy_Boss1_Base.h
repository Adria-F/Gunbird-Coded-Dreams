#ifndef __BOSS1_BASE_H__
#define __BOSS1_BASE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Boss1_Base : public Enemy
{
public:

	Enemy_Boss1_Base(int x, int y);
	~Enemy_Boss1_Base();

	void Move();

public:

	Path path;
	Animation idle;

};

#endif // !__BALLOON_H__
