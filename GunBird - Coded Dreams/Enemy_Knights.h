#pragma once

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"
#include "ModuleParticles.h"

class Enemy_Knights : public Enemy
{
private:
	Path path;
	iPoint original_pos;
	Animation anim;
public:
	Enemy_Knights(int x, int y, int wave, int id);
	~Enemy_Knights();
	void Move();

};

