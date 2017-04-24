#ifndef __MODULEPOWERUP_H__
#define __MODULEPOWERUP_H__

#include "Module.h"
#include "ModulePlayer.h"

#define MAX_POWERUP 5

struct SDL_Texture;
struct Particle;
struct Collider;

enum powerup_type
{
	UPGRADE,
	BOMB
};

class ModulePowerUp : public Module
{
public:
	int x;
	int y;
	Particle* powerups[MAX_POWERUP];

public:

	ModulePowerUp();
	~ModulePowerUp();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);
	void AddPowerUp(powerup_type type, int x, int y);
};

#endif // !__MODULEPOWERUP_H__
