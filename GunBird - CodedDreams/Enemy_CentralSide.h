#ifndef __CENTRALSIDE_H__
#define __CENTRALSIDE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_CentralSide : public Enemy
{
public:

	Enemy_CentralSide(int x, int y);
	~Enemy_CentralSide();

	void Move();

public:

	int state = 0;
	Path path;
	Animation moving;
	Animation vault_closing;
	Animation vault_open;

};

#endif // !__BALLOON_H__
