#ifndef __GENERAL_TURRET_H__
#define __GENERAL_TURRET_H__

#include "Enemy.h"
#include "Path.h"
#include "p2Point.h"
#include "ModulePlayer.h"

class Enemy_General_Turret : public Enemy
{
public:

	Enemy_General_Turret(int x, int y, int wave, int id);
	~Enemy_General_Turret();

	void Move();
	void DeadAnim();
	void ExtraAnim(SDL_Texture* texture);

public:

	Path path;
	Animation idle;
	Animation dead;

private:

	fPoint vector;
	int distance[2];
	int angle;
	Player* player;
	SDL_Rect angles[32];

};

#endif // !__BALLOON_H__