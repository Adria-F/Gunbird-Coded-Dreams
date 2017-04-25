#ifndef __BUILDING1_H__
#define __BUILDING1_H__

#include "Enemy.h"

class Enemy_Building1 : public Enemy
{
private:

	Animation anim;
	Animation flag_anim;
	Animation dead_build1;

public:

	Enemy_Building1(int x, int y);

	void Move();
	void ExtraAnim(SDL_Texture* texture);
	virtual void DeadAnim();
};

#endif // !__BUILDING1_H__

