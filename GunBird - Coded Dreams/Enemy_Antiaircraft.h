#ifndef __ANTIAIRCRAFT_H__
#define __ANITAIRCRAFT_H__

#include "Enemy.h"

class Enemy_Antiaircraft : public Enemy
{
private:

	int shot_sequ = 0;
	Animation anim;
	Animation open_anim;
	fPoint vector;
	int distance[2];
	SDL_Rect angles[16];

	Uint32 start_time = 0;
	Uint32 total_time = (Uint32)(2.0f * 0.5f * 750.0f);
	Uint32 now;
	
public:

	Enemy_Antiaircraft(int x, int y);

	void Move();
	void ExtraAnim();
};

#endif // !__ANTIAIRCRAFT_H__
