#ifndef __BUILDING2_H__
#define __BUILDING2_H__

#include "Enemy.h" 
class Enemy_Building2 : public Enemy
{
private:

	Animation anim;
	Animation flag_anim;
	Animation dead_build2;

public:

	Enemy_Building2(int x, int y);
	~Enemy_Building2();

	void Move();
	void ExtraAnim(SDL_Texture* texture);
	void Enemy_Building2::DeadAnim();
};

#endif // !__BUILDING1_H__
