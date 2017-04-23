#pragma once

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"
#include "ModuleParticles.h"

class Enemy_Knights : public Enemy
{
private:
	SDL_Texture* texture_bg_upper = nullptr;
	SDL_Rect rect_background_upper;
	Path path;
	iPoint original_pos;
	Animation anim;
public:
	Enemy_Knights(int x, int y, int wave, int id);
	~Enemy_Knights();
	void Move();
	void ExtraAnim();

};

