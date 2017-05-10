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
	Animation anim_b1;
	Animation anim_b2;
	Animation anim_m1;
	Animation anim_m2;
	Animation anim_s1;
	Animation anim_s2;

public:
	enum Explosions
	{
		//Josep: M'he fixat que en pr�cticament totes les animacions 
		//de mort acaben en el fotograma 4... 
		//no ser� tan �til com em pensava aix�, pero far� la feina
		//aqu� hi han coses que no est�n acabades (perque totes neceiten el fotograma
		//4)
		BIG1 = 1,
		BIG2,
		MID1,
		MID2,
		SMALL1,
		SMALL2,
		FLYINGMACHINE
	};
	fPoint position;
	fPoint original_pos;
	SDL_Texture* sprites = nullptr; //Using texture
	SDL_Texture* NormalSprite = nullptr;
	SDL_Texture* RedSprite = nullptr;
	SDL_Texture* WhiteSprite = nullptr;
	
	//Explosions textures
	SDL_Texture* b1;

	//Time between red ticks
	Uint32 Red_now;
	Uint32 Red_Start_time;
	Uint32 Red_Total_time = (Uint32)(2.0f * 0.5f * 700.0f);
	int lives; //Hit points
	int initial_hp; //To calculate when to turn red
	bool hit; //When to turn white
	bool extra_anim = false; //Something moving over basic animation?
	bool die = false;
	bool lower_level = false; //Is the enemy behing the overlayed map?
	Explosions type;
	
	int wave;
	int id = -1; //Id of an enemy inside a wave
	int points = 0; //Points that give to the player
	Collider* collider = nullptr;

public:
	Enemy(int x, int y, int wave = 1, int id = 0);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void ExtraAnim(SDL_Texture* texture) {};
	virtual void DeadAnim();
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);
	virtual bool explode();
};

#endif // __ENEMY_H__