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
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "SDL/include/SDL_timer.h"

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
	if (App->render->debugging && App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN)
	{
		AddPowerUp(powerup_type::UPGRADE, 100, 150);
	}
	
	for (int i = 0; i < MAX_POWERUP; i++)
	{
		if (powerups[i] != nullptr && (powerups[i]->part->type == P_UPGRADE || powerups[i]->part->type == P_BOMB))
		{
			powerups[i]->Update();
			if (powerups[i]->part->position.y <= 50 && powerups[i]->part->speed.y < 0)
			{
				powerups[i]->part->speed.y = -powerups[i]->part->speed.y;
			}
			if (powerups[i]->part->position.y >= (SCREEN_HEIGHT - 50 - 13 ) && powerups[i]->part->speed.y > 0)
			{
				powerups[i]->part->speed.y = -powerups[i]->part->speed.y;
			}
			if (powerups[i]->part->position.x <= 0 || powerups[i]->part->position.x >= (SCREEN_WIDTH - 22))
			{
				powerups[i]->part->speed.x = -powerups[i]->part->speed.x;
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
			Particle* temp = nullptr;

			switch (type)
			{
			case UPGRADE:
				App->particles->upgrade_particle.speed.x = rand() % 20 + -10;
				App->particles->upgrade_particle.speed.x /= 10;
				while (App->particles->upgrade_particle.speed.x == 0)
				{
					App->particles->upgrade_particle.speed.x = rand() % 20 + -10;
					App->particles->upgrade_particle.speed.x /= 10;
				}
				App->particles->upgrade_particle.speed.y = -sqrt(1 - pow(App->particles->upgrade_particle.speed.x, 2.0));
				temp = App->particles->AddParticle(App->particles->upgrade_particle, particle_type::P_UPGRADE, x, y, COLLIDER_POWER_UP);
				break;
			case BOMB:
				App->particles->bomb_particle.speed.x = rand() % 20 + -10;
				App->particles->bomb_particle.speed.x /= 10;
				while (App->particles->bomb_particle.speed.x == 0)
				{
					App->particles->bomb_particle.speed.x = rand() % 20 + -10;
					App->particles->bomb_particle.speed.x /= 10;
				}
				App->particles->bomb_particle.speed.y = -sqrt(1 - pow(App->particles->bomb_particle.speed.x, 2.0));
				temp = App->particles->AddParticle(App->particles->bomb_particle, particle_type::P_BOMB, x, y, COLLIDER_POWER_UP);
				break;
			case COIN:
				temp = App->particles->AddParticle(App->particles->coin_particle, particle_type::P_COIN, x, y, COLLIDER_POWER_UP);
				break;
			}
			powerups[i] = new PowerUp(temp, type);
			break;
		}
	}
}

void ModulePowerUp::OnCollision(Collider* c1, Collider* c2)
{
	PowerUp* temp = nullptr;
	for (int i = 0; i < MAX_POWERUP; i++)
	{
		if (powerups[i] != nullptr && powerups[i]->part == c1->part)
		{
			temp = powerups[i];
			break;
		}
	}
	if (temp != nullptr && temp->active)
	{
		if (c2->callback == App->player1)
		{
			switch (temp->type)
			{
			case UPGRADE:
				
				for (int i = 0; i < MAX_POWERUP; i++)
				{
					if (App->player1->shot_lvl <= 4 && powerups[i] != nullptr && powerups[i]->part == c1->part)
					{
						App->audio->Load(App->player1->character->upgrade_path, App->audio->EFFECT);
						App->audio->Play(App->audio->EFFECT);
						powerups[i] = nullptr;
						App->player1->drop = false;
						App->player1->drop_timer_start = SDL_GetTicks();
						App->player1->shot_lvl += 1;
						break;
					}
					else if (App->player1->shot_lvl > 4 && powerups[i] != nullptr && powerups[i]->part == c1->part)
					{
						App->audio->Load(App->player1->character->full_upgrade_path, App->audio->EFFECT);
						App->audio->Play(App->audio->EFFECT);
						powerups[i] = nullptr;
					}
				}
				break;
			case BOMB:
				for (int i = 0; i < MAX_POWERUP; i++)
				{
					if (App->player1->bombs < 3 && powerups[i] != nullptr && powerups[i]->part == c1->part)
					{
						App->audio->Load("assets/effects/gunbird_203 [EFFECT] Collect bomb.wav", App->audio->EFFECT);
						App->audio->Play(App->audio->EFFECT);
						App->player1->bombs++;
						powerups[i] = nullptr;
					}
				}
				break;
			case COIN:
				break;
			}

		}
		else if (c2->callback == App->player2)
		{
			switch (temp->type)
			{
			case UPGRADE:
				
				for (int i = 0; i < MAX_POWERUP; i++)
				{
					if (App->player2->shot_lvl <= 4 && powerups[i] != nullptr && powerups[i]->part == c1->part)
					{
						App->audio->Load(App->player2->character->upgrade_path, App->audio->EFFECT);
						App->audio->Play(App->audio->EFFECT);
						powerups[i] = nullptr;
						App->player2->drop = false;
						App->player2->drop_timer_start = SDL_GetTicks();
						App->player2->shot_lvl += 1;
						break;
					}
					else if (App->player2->shot_lvl > 4 && powerups[i] != nullptr && powerups[i]->part == c1->part)
					{
						App->audio->Load(App->player2->character->full_upgrade_path, App->audio->EFFECT);
						App->audio->Play(App->audio->EFFECT);
					}

				}
				App->particles->OnCollision(c1, c2);
			case BOMB:
				for (int i = 0; i < MAX_POWERUP; i++)
				{
					if (App->player2->bombs < 3 && powerups[i] != nullptr && powerups[i]->part == c1->part)
					{
						App->audio->Load("assets/effects/gunbird_203 [EFFECT] Collect bomb.wav", App->audio->EFFECT);
						App->audio->Play(App->audio->EFFECT);
						App->player2->bombs++;
						powerups[i] = nullptr;
					}
				}
				break;
			case COIN:
				break;
			}
		}
		App->particles->OnCollision(c1, c2);
	}
}

bool PowerUp::Update()
{
	if (part != nullptr && part->anim.Finished() && active == false)
	{
		active = true;
	}

	return true;
}