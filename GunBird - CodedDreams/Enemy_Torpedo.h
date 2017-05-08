#ifndef __TORPEDO_H__
#define __TORPEDO_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Torpedo : public Enemy
{
public:

	Enemy_Torpedo(int x, int y);
	~Enemy_Torpedo();

	void Move();
	
public:

	Path path;
	Animation idle;
	
};

#endif // !__TORPEDO_H__
