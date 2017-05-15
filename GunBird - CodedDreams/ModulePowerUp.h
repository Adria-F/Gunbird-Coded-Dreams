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
	COIN,
	BOMB
};

struct PowerUp
{
	Particle* part;
	powerup_type type;
	bool active;

	bool Update();
	PowerUp(Particle* part, powerup_type type): part(part), type(type), active(false)
	{}
};

class ModulePowerUp : public Module
{
public:
	int x;
	int y;
	PowerUp* powerups[MAX_POWERUP];

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
