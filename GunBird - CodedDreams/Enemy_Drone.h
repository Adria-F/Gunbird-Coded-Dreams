#ifndef __DRONE_H__
#define __DRONE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Drone : public Enemy
{
public:

	Enemy_Drone(int x, int y);
	~Enemy_Drone();

	void Move();
	void ExtraAnim(SDL_Texture* texture);
	void DeadAnim();

public:

	Path path;
	Animation idle;
	Animation dead;

};

#endif // !__DRONE_H__
#pragma once
