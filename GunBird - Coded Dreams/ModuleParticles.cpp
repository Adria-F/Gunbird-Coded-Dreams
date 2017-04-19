#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModulePowerUp.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneCastle.h"
#include "ModuleHighscores.h"
#include "ModulePlayer.h"

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
	MARION_bullet_texture = App->textures->Load("assets/characters/marion.png");
	ASH_bullet_texture = App->textures->Load("assets/characters/ash.png");
	upgrade_texture = App->textures->Load("assets/items/upgrade.png");
	small_shot_texture = App->textures->Load("assets/enemies/basic_shoot.png");

	// Marion Bullets
	MARION_bullet_particle.anim.PushBack({ 166, 127, 7, 30 });
	MARION_bullet_particle.life = 10000;
	MARION_bullet_particle.speed.y = -8;
	MARION_bullet_particle.anim.loop = false;
	MARION_bullet_particle.anim.speed = 0.5f;

	// Ash Bullets
	ASH_bullet_particle.anim.PushBack({ 27, 222, 14, 6 });
	ASH_bullet_particle.life = 10000;
	ASH_bullet_particle.speed.y = -8;
	ASH_bullet_particle.anim.loop = false;
	ASH_bullet_particle.anim.speed = 0.5f;

	// Upgrade
	upgrade_particle.anim.PushBack({ 4, 31, 22, 13 });
	upgrade_particle.anim.PushBack({ 54, 31, 22, 13 });
	upgrade_particle.anim.PushBack({ 104, 31, 22, 13 });
	upgrade_particle.anim.PushBack({ 54, 47, 22, 13 });
	upgrade_particle.anim.PushBack({ 104, 47, 22, 13 });
	upgrade_particle.anim.PushBack({ 54, 64, 22, 13 });
	upgrade_particle.anim.PushBack({ 104, 64, 22, 13 });
	upgrade_particle.anim.PushBack({ 56, 83, 22, 13 });
	upgrade_particle.anim.PushBack({ 81, 83, 22, 13 });
	upgrade_particle.life = 100000;
	upgrade_particle.anim.loop = true;
	upgrade_particle.anim.speed = 0.2f;

	// Small shot
	small_shot_particle.anim.PushBack({ 9, 9, 6, 6});
	small_shot_particle.anim.PushBack({ 41, 9, 6, 6 });
	small_shot_particle.anim.PushBack({ 73, 9, 6, 6 });
	small_shot_particle.anim.PushBack({ 105, 9, 6, 6 });
	small_shot_particle.anim.PushBack({ 137, 9, 6, 6 });
	small_shot_particle.anim.PushBack({ 185, 9, 6, 6 });
	small_shot_particle.anim.PushBack({ 9, 25, 6, 6 });
	small_shot_particle.anim.PushBack({ 41, 25, 6, 6 });
	small_shot_particle.life = 100000;
	small_shot_particle.speed.x = 0;
	small_shot_particle.speed.y = 0;
	small_shot_particle.anim.loop = true;
	small_shot_particle.anim.speed = 0.5f;
	
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(MARION_bullet_texture);
	App->textures->Unload(ASH_bullet_texture);
	App->textures->Unload(upgrade_texture);
	App->textures->Unload(small_shot_texture);

	MARION_bullet_texture = nullptr;
	ASH_bullet_texture = nullptr;
	upgrade_texture = nullptr;
	small_shot_texture = nullptr;

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
			case P_MARION_BULLET:
				App->render->Blit(MARION_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_ASH_BULLET:
				App->render->Blit(ASH_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_UPGRADE:
				App->render->Blit(upgrade_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			case P_SMALL_SHOT:
				App->render->Blit(small_shot_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
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

Particle* ModuleParticles::AddParticle(const Particle& particle, particle_type type, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, float x_phase)
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
			case COLLIDER_ENEMY_SHOT:
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
				switch (type)
				{
				case P_SMALL_SHOT:
					y_phase = 16 + (((x - App->player->position.x) / (y - App->player->position.y)) * 12);
					if (App->player->position.x - x < 0)
					{
						if (x_phase < 0)
						{
							y_phase = -y_phase;
						}
					}
					else
					{
						if (x_phase > 0)
						{
							y_phase = -y_phase;
						}
					}
					vector.x = App->player->position.x + 10 + x_phase - x;
					vector.y = App->player->position.y - 16 + y_phase - y;
					modul = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
					vector.x /= modul;
					vector.y /= modul;
					p->speed.x = vector.x * SMALL_SHOT_SPEED;
					p->speed.y = vector.y * SMALL_SHOT_SPEED;
				}
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
		if (c1->type == COLLIDER_ENEMY_SHOT && c2->callback == (Module*)App->player)
		{
			App->render->moving_scene = false;
			App->fade->FadeToBlack(App->scene_castle, App->highscores);
		}

		if (c1->type == COLLIDER_ENEMY_SHOT && c2->callback == (Module*)App->player2)
		{
			App->render->moving_scene = false;
			App->fade->FadeToBlack(App->scene_castle, App->highscores);
		}
		
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
		collider->to_delete = true;
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