#include "ModulePowerUp.h"
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleMarion.h"
#include "ModuleAsh.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleDebugMode.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

ModulePowerUp::ModulePowerUp()
{
	for (int i = 0; i < MAX_POWERUP; i++)
	{
		powerups[i] = nullptr;
	}
}

ModulePowerUp::~ModulePowerUp()
{
}

bool ModulePowerUp::Start()
{
	LOG("Loading Power Up textures");
	//-----------------Upgrade Texture------------------

	return true;
}

bool ModulePowerUp::CleanUp()
{
	return true;
}

update_status ModulePowerUp::Update()
{
	if (App->debug->debugging && App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN)
	{
		App->powerup->AddPowerUp(powerup_type::UPGRADE, 100, 150);
	}
	
	for (int i = 0; i < MAX_POWERUP; i++)
	{
		if (powerups[i] != nullptr && powerups[i]->type == P_UPGRADE)
		{
			if (powerups[i]->position.y <= 50 || powerups[i]->position.y >= (SCREEN_HEIGHT - 50 - 13))
			{
				powerups[i]->speed.y = -powerups[i]->speed.y;
			}
			if (powerups[i]->position.x <= 0 || powerups[i]->position.x >= (SCREEN_WIDTH - 22))
			{
				powerups[i]->speed.x = -powerups[i]->speed.x;
			}
		}
	}
	
	return UPDATE_CONTINUE;
}

void ModulePowerUp::AddPowerUp(powerup_type type, int x, int y)
{
	srand(time(NULL));
	for (int i = 0; i < MAX_POWERUP; i++)
	{
		if (powerups[i] == nullptr)
		{
			App->particles->upgrade_particle.speed.x = rand() % 20 + -10;
			App->particles->upgrade_particle.speed.x /= 10;
			while (App->particles->upgrade_particle.speed.x == 0)
			{
				App->particles->upgrade_particle.speed.x = rand() % 20 + -10;
				App->particles->upgrade_particle.speed.x /= 10;
			}
			App->particles->upgrade_particle.speed.y = - sqrt(1-pow(App->particles->upgrade_particle.speed.x, 2.0));
			powerups[i] = App->particles->AddParticle(App->particles->upgrade_particle, particle_type::P_UPGRADE, x, y, COLLIDER_POWER_UP);
			break;
		}
	}
}

void ModulePowerUp::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->callback == App->marion)
	{
		App->audio->Load("assets/music/upgrade_marion.wav", App->audio->EFFECT);
		App->audio->Play(App->audio->EFFECT);
		for (int i = 0; i < MAX_POWERUP; i++)
		{
			if (powerups[i] != nullptr && powerups[i]->collider == c1)
			{
				powerups[i] = nullptr;
				App->marion->shot_lvl += 1;
				break;
			}
		}
		App->particles->OnCollision(c1, c2);
	}
	else if (c2->callback == App->ash)
	{
		App->audio->Load("assets/music/upgrade_ash.wav", App->audio->EFFECT);
		App->audio->Play(App->audio->EFFECT);
		for (int i = 0; i < MAX_POWERUP; i++)
		{
			if (powerups[i] != nullptr && powerups[i]->collider == c1)
			{
				powerups[i] = nullptr;
				App->ash->shot_lvl += 1;
				break;
			}
		}
		App->particles->OnCollision(c1, c2);
	}
}