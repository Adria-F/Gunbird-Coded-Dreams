#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 500
#define SMALL_SHOT_SPEED 3.5

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

enum particle_type
{
	P_MARION_BULLET_P1,
	P_MARION_BULLET_P2,
	P_ASH_BULLET,
	P_UPGRADE,
	P_SMALL_SHOT,
	P_BIG_SHOT,
	P_EXPLOSION
};

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	fPoint position;
	fPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	particle_type type;
	bool going_up = true;
	int damage = 1;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	Particle* AddParticle(const Particle& particle, particle_type type, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0, float x_phase = 0);

public:

	SDL_Texture* MARION_bullet_p1_texture = nullptr;
	SDL_Texture* MARION_bullet_p2_texture = nullptr;
	SDL_Texture* ASH_bullet_texture = nullptr;
	SDL_Texture* upgrade_texture = nullptr;
	SDL_Texture* small_shot_texture = nullptr;
	SDL_Texture* explosions_texture = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	fPoint vector;
	float modul;
	float y_phase;
	int distance[2];

public:

	Particle MARION_bullet_p1_particle;
	Particle MARION_bullet_p2_particle;
	Particle ASH_bullet_particle;
	Particle upgrade_particle;
	Particle small_shot_particle;
	Particle explosions_particle;
};

#endif // __MODULEPARTICLES_H__
