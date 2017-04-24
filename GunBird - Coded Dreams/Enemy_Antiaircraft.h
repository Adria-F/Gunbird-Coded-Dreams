#ifndef __ANTIAIRCRAFT_H__
#define __ANITAIRCRAFT_H__

#include "Enemy.h"

class Enemy_Antiaircraft : public Enemy
{
private:

	Animation anim;
	fPoint vector;
	int distance[2];
	SDL_Rect angles[16];

	Uint32 start_time2 = 0;
	Uint32 total_time2 = (Uint32)(2.0f * 0.5f * 750.0f);
	Uint32 now2;
public:

	Enemy_Antiaircraft(int x, int y);

	void Move();
};

#endif // !__ANTIAIRCRAFT_H__
