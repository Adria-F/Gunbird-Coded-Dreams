#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	Animation* animation = nullptr;
	

public:
	iPoint position;
	SDL_Texture* sprites = nullptr;
	int lives;
	bool extra_anim = false;
	bool dead = false;
	int wave;
	int id = -1;
	Collider* collider = nullptr;

public:
	Enemy(int x, int y, int wave = 1, int id = 0);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void ExtraAnim() {};
	virtual void DeadAnim();
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);
};

#endif // __ENEMY_H__