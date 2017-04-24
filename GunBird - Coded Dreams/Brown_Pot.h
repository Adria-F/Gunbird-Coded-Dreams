#ifndef __POT_H__
#define __POT_H__

#include "Enemy.h"

class Brown_Pot : public Enemy
{
private:

	Animation anim;
	
	Animation dead_pot;

public:

	Brown_Pot(int x, int y);

	virtual void DeadAnim();
};

#endif // !__POT_H__
