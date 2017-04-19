#ifndef __BUILDING2_H__
#define __BUILDING2_H__

#include "Enemy.h" 
class Enemy_Building2 : public Enemy
{
private:

	Animation anim;
	Animation flag_anim;

public:

	Enemy_Building2(int x, int y);

	void Move();
	void ExtraAnim();
};

#endif // !__BUILDING1_H__
