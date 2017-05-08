#ifndef __ENEMY_MINERS_H__
#define __ENEMY_MINERS_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Miners : public Enemy
{
public:

	Enemy_Miners(int x, int y);
	~Enemy_Miners();

	void Move();
	void ExtraAnim(SDL_Texture* texture);
	void DeadAnim();

public:

	Path path;
	Animation anim;
	Animation dead;

};

#endif // !__FLYING_MACHINE_H__


