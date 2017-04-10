#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModulePowerUp.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	bullet_graphics = App->textures->Load("assets/characters/marion.png");
	upgrade_graphics = App->textures->Load("assets/items/upgrade.png");

	// Marion Bullets
	bullet.anim.PushBack({ 166, 127, 7, 30 });
	bullet.life = 10000;
	bullet.speed.y = -8;
	bullet.anim.loop = false;
	bullet.anim.speed = 0.5f;

	// Upgrade
	upgrade.anim.PushBack({ 4, 31, 22, 13 });
	upgrade.anim.PushBack({ 54, 31, 22, 13 });
	upgrade.anim.PushBack({ 104, 31, 22, 13 });
	upgrade.anim.PushBack({ 54, 47, 22, 13 });
	upgrade.anim.PushBack({ 104, 47, 22, 13 });
	upgrade.anim.PushBack({ 54, 64, 22, 13 });
	upgrade.anim.PushBack({ 104, 64, 22, 13 });
	upgrade.anim.PushBack({ 56, 83, 22, 13 });
	upgrade.anim.PushBack({ 81, 83, 22, 13 });
	upgrade.life = 100000;
	upgrade.anim.loop = true;
	upgrade.anim.speed = 0.2f;
	
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(bullet_graphics);
	App->textures->Unload(upgrade_graphics);
	bullet_graphics = nullptr;
	upgrade_graphics = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			switch (p->type)
			{
			case P_BULLET:
				App->render->Blit(bullet_graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_UPGRADE:
				App->render->Blit(upgrade_graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			}
			if (p->fx_played == false)
			{
				p->fx_played = true;
			}
		}

		if (p->position.x < -PARTICLES_MARGIN || p->position.x > (SCREEN_WIDTH + PARTICLES_MARGIN) || p->position.y < -PARTICLES_MARGIN || p->position.y > (SCREEN_HEIGHT + PARTICLES_MARGIN))
		{
			p->life = 0;
			delete p;
			active[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, particle_type type, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Particle* temp_p = nullptr;
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->type = type;
			switch (collider_type)
			{
			case COLLIDER_PLAYER_SHOT:
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
				break;
			case COLLIDER_POWER_UP:
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, App->powerup);
				break;
			}
			active[i] = p;
			temp_p = p;
			break;
		}
	}

	return temp_p;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}
// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		App->collision->EraseCollider(collider);
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}