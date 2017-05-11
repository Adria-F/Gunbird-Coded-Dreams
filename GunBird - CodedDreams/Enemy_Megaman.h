#ifndef __MEGAMAN_H__
#define __MEGAMAN_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Megaman : public Enemy
{
public:

	Enemy_Megaman(int x, int y);
	~Enemy_Megaman();

	void Move();

public:

	Path path;
	Animation idle;

};

#endif // !__BALLOON_H__
