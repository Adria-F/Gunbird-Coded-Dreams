#pragma once

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"
#include "ModuleParticles.h"

class Enemy_The_Trump : public Enemy
{
private:
	Path path;
	iPoint original_pos;
	Animation anim_pilot_up;
	Animation anim_pilot_right;
	Animation anim_pilot_idle;

public:
	Enemy_The_Trump(int x, int y, int wave, int id);
	~Enemy_The_Trump();
	void Move();

};

