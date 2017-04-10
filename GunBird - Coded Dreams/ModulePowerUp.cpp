#include "ModulePowerUp.h"
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

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
	for (int i = 0; i < MAX_POWERUP; i++)
	{
		if (powerups[i] != nullptr)
		{
			if (powerups[i]->position.y < 50)
			{
				powerups[i]->going_up = false;
			}
			else if (powerups[i]->position.y > 250)
			{
				powerups[i]->going_up = true;
			}
			if (powerups[i]->going_up)
			{
				powerups[i]->position.y -= 1;
			}
			else
			{
				powerups[i]->position.y += 3;
			}
		}
	}
	
	return UPDATE_CONTINUE;
}

void ModulePowerUp::AddPowerUp(powerup_type type, int x, int y)
{
	for (int i = 0; i < MAX_POWERUP; i++)
	{
		if (powerups[i] == nullptr)
		{
			App->particles->upgrade.speed.x = 0;
			App->particles->upgrade.speed.y = -1;
			powerups[i] = App->particles->AddParticle(App->particles->upgrade, particle_type::P_UPGRADE, x, y, COLLIDER_POWER_UP);
			break;
		}
	}
}

void ModulePowerUp::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->callback == App->player)
	{
		App->audio->Load("assets/music/upgrade_marion.wav", App->audio->EFFECT);
		App->audio->Play(App->audio->EFFECT);
		App->particles->OnCollision(c1, c2);
	}
}