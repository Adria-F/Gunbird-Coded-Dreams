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
#include "ModuleMarion.h"
#include "ModuleAsh.h"
#include "ModuleDebugMode.h"

#include "SDL/include/SDL_timer.h"

#define PI 3.14159265

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
	MARION_bullet_p1_texture = App->textures->Load("assets/characters/marion.png");
	MARION_bullet_p2_texture = App->textures->Load("assets/characters/marion.png");

	ASH_bullet_p1_texture = App->textures->Load("assets/characters/ash.png");
	ASH_bullet_p2_texture = App->textures->Load("assets/characters/ash.png");

	upgrade_texture = App->textures->Load("assets/items/upgrade.png");
	small_shot_texture = App->textures->Load("assets/enemies/basic_shoot.png");
	explosions_texture = App->textures->Load("assets/enemies/Balloon.png");
	big_shot_texture = App->textures->Load("assets/enemies/antiarcraft_bullets.png");
	explosion_building1_texture = App->textures->Load("assets/enemies/explosions/castle_flags_explosion.png");
	explosion_antiaircraft_texture = App->textures->Load("assets/enemies/explosions/castle_antiaircraft_explosion.png");
	explosion_torpedo_texture = App->textures->Load("assets/enemies/explosions/castle_torpedo_explosion.png");
	explosion_pot_texture = App->textures->Load("assets/enemies/explosions/castle_pot_explosion.png");

	// Marion Bullets
	MARION_bullet_p1_particle.anim.PushBack({ 166, 127, 7, 30 });
	MARION_bullet_p1_particle.life = 10000;
	MARION_bullet_p1_particle.speed.y = -8;
	MARION_bullet_p1_particle.anim.loop = false;
	MARION_bullet_p1_particle.anim.speed = 0.5f;
	MARION_bullet_p1_particle.damage = 1;

	MARION_bullet_p2_particle.anim.PushBack({ 192, 127, 15, 29 });
	MARION_bullet_p2_particle.life = 10000;
	MARION_bullet_p2_particle.speed.y = -8;
	MARION_bullet_p2_particle.anim.loop = false;
	MARION_bullet_p2_particle.anim.speed = 0.5f;
	MARION_bullet_p2_particle.damage = 2;

	// Ash Bullets
	ASH_bullet_p1_particle.anim.PushBack({ 175, 29, 9, 29});
	ASH_bullet_p1_particle.life = 10000;
	ASH_bullet_p1_particle.speed.y = -8;
	ASH_bullet_p1_particle.anim.loop = false;
	ASH_bullet_p1_particle.anim.speed = 0.5f;
	ASH_bullet_p1_particle.damage = 1;

	ASH_bullet_p2_particle.anim.PushBack({ 170, 68, 19, 37 });
	ASH_bullet_p2_particle.life = 10000;
	ASH_bullet_p2_particle.speed.y = -8;
	ASH_bullet_p2_particle.anim.loop = false;
	ASH_bullet_p2_particle.anim.speed = 0.5f;
	ASH_bullet_p2_particle.damage = 2;

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



	// Big shot 
	big_shot_particle.anim.PushBack({ 96, 97, 12, 12 });
	big_shot_particle.anim.PushBack({ 153, 98, 12, 12 });
	big_shot_particle.life = 100000;
	big_shot_particle.speed.x = 0;
	big_shot_particle.speed.y = 0;
	big_shot_particle.anim.loop = true;
	big_shot_particle.anim.speed = 0.5f;

	//exploisons
	{
		// Balloon exploison
		explosions_particle.anim.PushBack({ 5, 117, 92, 86 });
		explosions_particle.anim.PushBack({ 104, 114, 101, 93 });
		explosions_particle.anim.PushBack({ 212, 109, 105, 102 });
		explosions_particle.anim.PushBack({ 322, 110, 99, 101 });
		explosions_particle.life = 100000;
		explosions_particle.speed.y = App->render->cam_speed;
		explosions_particle.anim.loop = false;
		explosions_particle.anim.speed = 1.0f;

		// Building 1 exploison

		exploison_building1_particle.anim.PushBack({ 14,18,99,108 });
		exploison_building1_particle.anim.PushBack({ 118,9,126,126 });
		exploison_building1_particle.anim.PushBack({ 245,9,126,126 });
		exploison_building1_particle.anim.PushBack({ 372,9,126,126 });
		exploison_building1_particle.anim.PushBack({ 6,145,115,115 });
		exploison_building1_particle.anim.PushBack({ 126,145,115,115 });
		exploison_building1_particle.anim.PushBack({ 248,145,115,115 });
		exploison_building1_particle.anim.PushBack({ 368,144,115,115 });
		exploison_building1_particle.anim.PushBack({ 8,275,115,115 });
		exploison_building1_particle.anim.PushBack({ 128,275,115,115 });
		exploison_building1_particle.anim.PushBack({ 253,275,115,115 });
		exploison_building1_particle.anim.PushBack({ 0, 0, 0, 0 });
		exploison_building1_particle.life = 100000;
		exploison_building1_particle.speed.y = App->render->cam_speed;
		exploison_building1_particle.anim.loop = false;
		exploison_building1_particle.anim.speed = 1.0f;

		// Torpedo explosion
		exploison_torpedo_particle.anim.PushBack({ 12,10,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 77,11,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 137,13,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 197,12,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 12,61,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 72,62,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 136,62,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 196,62,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 12,110,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 73,111,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 134,111,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 194,111,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 12,153,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 73,153,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 134,153,48,37 });
		exploison_torpedo_particle.anim.PushBack({ 0, 0, 0, 0 });
		exploison_torpedo_particle.life = 10000;
		exploison_torpedo_particle.speed.y = App->render->cam_speed;
		exploison_torpedo_particle.anim.loop = false;
		exploison_torpedo_particle.anim.speed = 1.0f;

		// Antiaircraft explosion
		exploison_antiaricraft_particle.anim.PushBack({ 18, 27, 56, 56 });
		exploison_antiaricraft_particle.anim.PushBack({ 88, 27, 56, 56 });
		exploison_antiaricraft_particle.anim.PushBack({ 148, 18, 74, 74 });
		exploison_antiaricraft_particle.anim.PushBack({ 226, 18, 74, 74 });
		exploison_antiaricraft_particle.anim.PushBack({ 303, 18, 74, 74 });
		exploison_antiaricraft_particle.anim.PushBack({ 13, 104, 67, 66 });
		exploison_antiaricraft_particle.anim.PushBack({ 151, 105, 67 , 66 });
		exploison_antiaricraft_particle.anim.PushBack({ 224, 107 , 67, 66 });
		exploison_antiaricraft_particle.anim.PushBack({ 302, 107 , 67, 66 });
		exploison_antiaricraft_particle.anim.PushBack({ 11, 197 , 63, 73 });
		exploison_antiaricraft_particle.anim.PushBack({ 160, 199 , 63, 73 });
		exploison_antiaricraft_particle.anim.PushBack({ 228, 199 , 67, 66 });
		exploison_antiaricraft_particle.anim.PushBack({ 0, 0, 0, 0 });
		exploison_antiaricraft_particle.life = 10000;
		exploison_antiaricraft_particle.speed.y = App->render->cam_speed;
		exploison_antiaricraft_particle.anim.loop = false;
		exploison_antiaricraft_particle.anim.speed = 1.0f;

		//pot explosion
		exploison_pot_particle.anim.PushBack({ 37, 20, 56, 56 });
		exploison_pot_particle.anim.PushBack({ 97, 20, 56, 56 });
		exploison_pot_particle.anim.PushBack({ 169, 11, 74, 74 });
		exploison_pot_particle.anim.PushBack({ 241, 16, 74, 74 });
		exploison_pot_particle.anim.PushBack({ 320, 14, 74, 74 });
		exploison_pot_particle.anim.PushBack({ 25, 99, 67, 66 });
		exploison_pot_particle.anim.PushBack({ 101, 98, 67 , 66 });
		exploison_pot_particle.anim.PushBack({ 172, 99 , 67, 66 });
		exploison_pot_particle.anim.PushBack({ 247, 99 , 67, 66 });
		exploison_pot_particle.anim.PushBack({ 324, 100 , 63, 73 });
		exploison_pot_particle.anim.PushBack({ 28, 190 , 63, 73 });
		exploison_pot_particle.anim.PushBack({ 105, 191 , 67, 66 });
		exploison_pot_particle.anim.PushBack({ 182, 192 , 63, 73 });
		exploison_pot_particle.anim.PushBack({ 255, 191 , 67, 66 });
		exploison_pot_particle.anim.PushBack({ 0, 0, 0, 0 });
		exploison_pot_particle.life = 100000;
		exploison_pot_particle.speed.y = App->render->cam_speed;
		exploison_pot_particle.anim.loop = false;
		exploison_pot_particle.anim.speed = 1.0f;
	}
	
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(MARION_bullet_p1_texture);
	App->textures->Unload(MARION_bullet_p2_texture);

	App->textures->Unload(ASH_bullet_p1_texture);
	App->textures->Unload(ASH_bullet_p2_texture);

	App->textures->Unload(upgrade_texture);
	App->textures->Unload(small_shot_texture);
	App->textures->Unload(explosions_texture);
	App->textures->Unload(big_shot_texture);

	MARION_bullet_p1_texture = nullptr;
	MARION_bullet_p2_texture = nullptr;

	ASH_bullet_p1_texture = nullptr;
	ASH_bullet_p2_texture = nullptr;

	upgrade_texture = nullptr;
	small_shot_texture = nullptr;
	explosions_texture = nullptr;
	big_shot_texture = nullptr;

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
	Particle* p = new Particle;
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		p = active[i];

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
			case P_MARION_BULLET_P1:
				App->render->Blit(MARION_bullet_p1_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_MARION_BULLET_P2:
				App->render->Blit(MARION_bullet_p2_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;

			case P_ASH_BULLET_P1:
				App->render->Blit(ASH_bullet_p1_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_ASH_BULLET_P2:
				App->render->Blit(ASH_bullet_p2_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_UPGRADE:
				App->render->Blit(upgrade_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_SMALL_SHOT:
				App->render->Blit(small_shot_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_BIG_SHOT:
				App->render->Blit(big_shot_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_EXPLOSION:
				App->render->Blit(explosions_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_EXPLOSION_BUILDING1:
				App->render->Blit(explosion_building1_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_EXPLOSION_TORPEDO:
				App->render->Blit(explosion_torpedo_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_EXPLOSION_ANTIAIRCRAFT:
				App->render->Blit(explosion_antiaircraft_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_EXPLOSION_POT:
				App->render->Blit(explosion_pot_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			}

			if (p->fx_played == false)
			{
				p->fx_played = true;
			}

			if (p->position.x < -PARTICLES_MARGIN || p->position.x >(SCREEN_WIDTH + PARTICLES_MARGIN) || p->position.y < -PARTICLES_MARGIN || p->position.y >(SCREEN_HEIGHT + PARTICLES_MARGIN))
			{
				p->life = 0;
				delete p;
				active[i] = nullptr;
			}
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
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this, p);
				break;
			case COLLIDER_POWER_UP:
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, App->powerup);
				break;
			case COLLIDER_ENEMY_SHOT:
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
				switch (type)
				{
				case P_SMALL_SHOT:
					ModulePlayer* player;
					vector.x = (App->marion->position.x - (App->render->camera.x + x));
					vector.y = (App->marion->position.y - (App->render->camera.y + y));
					distance[0] = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
					vector.x = (App->ash->position.x - (App->render->camera.x + x));
					vector.y = (App->ash->position.y - (App->render->camera.y + y));
					distance[1] = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
					if (distance[0] < distance[1])
						player = App->marion;
					else
						player = App->ash;
					
					y_phase = 16 + (((x - player->position.x) / (y - player->position.y)) * 12);
					if (player->position.x - x < 0)
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
					vector.x = player->position.x + 10 + x_phase - x;
					vector.y = player->position.y - 16 + y_phase - y;
					modul = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
					vector.x /= modul;
					vector.y /= modul;
					p->speed.x = vector.x * SMALL_SHOT_SPEED;
					p->speed.y = vector.y * SMALL_SHOT_SPEED;
					break;

				case P_BIG_SHOT:
					
					vector.x = (x_phase < 90 || x_phase > 270)? 1 : -1;
					vector.y = vector.x * tan(x_phase * PI / 180);
					vector.y = -vector.y;

					modul = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
					vector.x /= modul;
					vector.y /= modul;
					p->speed.x = vector.x * BIG_SHOT_SPEED;
					p->speed.y = vector.y * BIG_SHOT_SPEED;
					break;
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
		if (App->debug->debugging == false && c1->type == COLLIDER_ENEMY_SHOT && c2->callback == (Module*)App->marion)
		{
			App->render->moving_scene = false;
			App->fade->FadeToBlack(App->scene_castle, App->highscores);
		}
		if (App->debug->debugging == false && c1->type == COLLIDER_ENEMY_SHOT && c2->callback == (Module*)App->ash)
		{
			App->render->moving_scene = false;
			App->fade->FadeToBlack(App->scene_castle, App->highscores);
		}
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			//friendly shots with enemy. Animation here!
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
	fx(p.fx), born(p.born), life(p.life), damage(p.damage)
{}

Particle::~Particle()
{
	if (collider != nullptr)
	{
		collider->to_delete = true;
	}
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
		{
			ret = false;
		}
	}
	else
	{
		if (anim.Finished())
		{
			ret = false;
		}
	}
	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
	{
		collider->SetPos(position.x, position.y);
	}

	return ret;
}