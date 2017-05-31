#ifndef __BOSS1_BASE_H__
#define __BOSS1_BASE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Boss1_Base : public Enemy
{
public:

	Enemy_Boss1_Base(int x, int y, int wave);
	~Enemy_Boss1_Base();

	void Move();
	void ExtraAnim(SDL_Texture* texture);

public:
	Path path;
	Animation base;
	Animation protection;

};

#endif // !__BALLOON_H__
