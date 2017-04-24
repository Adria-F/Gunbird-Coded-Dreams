#ifndef __POT_H__
#define __POT_H__

#include "Enemy.h"

class Brown_Pot : public Enemy
{
private:


	SDL_Texture* texture_pot = nullptr;
	Animation pot_anim;
	SDL_Rect rect_pot;

	Animation dead_pot;

public:

	Brown_Pot(int x, int y);
	void Render();
	void CleanUp();
	
};

#endif // !__POT_H__
