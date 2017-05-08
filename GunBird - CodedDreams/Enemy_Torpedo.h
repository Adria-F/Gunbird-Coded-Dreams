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
	void ExtraAnim(SDL_Texture* texture);
	void DeadAnim();

public:

	Path path;
	Animation idle;
	Animation dead;

};

#endif // !__BALLOON_H__
#pragma once
