#ifndef __BALLOON_H__
#define __BALLOON_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Balloon : public Enemy
{
public:

	Enemy_Balloon(int x, int y);
	~Enemy_Balloon();

	void Move();
	void ExtraAnim(SDL_Texture* texture);
	void DeadAnim();

public:

	Path path;
	Animation idle;
	Animation dead;

};

#endif // !__BALLOON_H__
