#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSceneMine.h"
#include "ModuleAudio.h"
#include "ModulePowerUp.h"
#include "SDL/include/SDL_timer.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Start()
{
	if (character != nullptr)
	{
		points = 0;
		lives = 3;
		shot_lvl = 1;
		character->Start();
		position.y = 266;
		if (this == App->player1 && App->player2->IsEnabled())
			position.x = 50;
		else if (this == App->player2)
			position.x = 150;
		else
			position.x = 100;
		Pcollider = App->collision->AddCollider({ 0, 0, 18, 32}, COLLIDER_PLAYER, this);
	}

	return true;
}

bool Player::CleanUp()
{
	if (character != nullptr)
		character->CleanUp();
	if (Pcollider != nullptr)
		Pcollider->to_delete = true;
	return true;
}

update_status Player::Update()
{
	if (character != nullptr)
	{
		now = SDL_GetTicks() - start_time;
		
		drop_timer_now = SDL_GetTicks() - drop_timer_start;
		if (drop_timer_now >= drop_timer_total)
		{
			drop = true;
		}
		
		character->current_animation = &character->idle;
		
		//Update god mode
		if (App->render->god_mode)
			Pcollider->type = COLLIDER_NONE;
		else
			Pcollider->type = COLLIDER_PLAYER;

		if (going_up && position.y > 32)
		{
			position.y -= CHARACTER_SPEED;
		}
		if (going_left)
		{
			character->current_animation = &character->left;

			if (position.x > 0)
			{
				position.x -= CHARACTER_SPEED;
			}
		}
		if (going_down && position.y < SCREEN_HEIGHT)
		{
			position.y += CHARACTER_SPEED;
		}
		if (going_right)
		{
			character->current_animation = &character->right;
			if (position.x < SCREEN_WIDTH - 18)
			{
				position.x += CHARACTER_SPEED;
			}
		}

		//Blit
		SDL_Rect rect = character->current_animation->GetCurrentFrame();

		//Move graphics render

		App->render->Blit(character->texture_graphics, position.x, position.y - rect.h, &rect);

		//Shot system
		if ((bullet_counter == 0 || now >= total_time) && shot && bullet_counter <= MAX_BULLETS)
		{
			if (bullet_counter == MAX_BULLETS)
			{
				shot = false;
				start_time = SDL_GetTicks();
			}
			else
			{
				if (shot_lvl == 1)
					App->particles->AddParticle(*character->shot_particle_lvl1, character->shot_lvl1, position.x + 5, position.y - 45, COLLIDER_PLAYER_SHOT);
				else if (shot_lvl == 2)
					App->particles->AddParticle(*character->shot_particle_lvl2, character->shot_lvl2, position.x + 5, position.y - 45, COLLIDER_PLAYER_SHOT);
				else if (shot_lvl == 3)
				{
					if (character == (ModuleCharacter*)App->marion)
					{
						App->particles->AddParticle(*character->shot_particle_lvl3_left, character->shot_lvl3_left, position.x + 5, position.y - 45, COLLIDER_PLAYER_SHOT, 0, 120, ANGLE);
						App->particles->AddParticle(*character->shot_particle_lvl3_right, character->shot_lvl3_right, position.x + 5, position.y - 45, COLLIDER_PLAYER_SHOT, 0, 60, ANGLE);
						App->particles->AddParticle(*character->shot_particle_lvl1, character->shot_lvl1, position.x + 5, position.y - 45, COLLIDER_PLAYER_SHOT);
					}
					else
					App->particles->AddParticle(*character->shot_particle_lvl3, character->shot_lvl3, position.x + 5, position.y - 45, COLLIDER_PLAYER_SHOT);
				}
					
				else if (shot_lvl == 4)
				{
					if (character == (ModuleCharacter*)App->marion)
					{
						App->particles->AddParticle(*character->shot_particle_lvl4_left, character->shot_lvl4_left, position.x + 5, position.y - 45, COLLIDER_PLAYER_SHOT, 0, 120, ANGLE);
						App->particles->AddParticle(*character->shot_particle_lvl4_right, character->shot_lvl4_right, position.x + 5, position.y - 45, COLLIDER_PLAYER_SHOT, 0, 60, ANGLE);
						App->particles->AddParticle(*character->shot_particle_lvl2, character->shot_lvl2, position.x + 5, position.y - 45, COLLIDER_PLAYER_SHOT);
					}
					else
					App->particles->AddParticle(*character->shot_particle_lvl4, character->shot_lvl4, position.x + 5, position.y - 45, COLLIDER_PLAYER_SHOT);
				}

				start_time = SDL_GetTicks();
				bullet_counter++;
			}
		}

		//Update collider position
		Pcollider->SetPos(position.x, position.y - 32);
	}
	return UPDATE_CONTINUE;
}

void Player::setCharacter(ModuleCharacter* character)
{
	this->character = character;
}

void Player::OnCollision(Collider* c1, Collider* c2)
{
	if (App->render->god_mode == false && c2->type == COLLIDER_ENEMY_SHOT && App->scene_mine->lost == false)
	{
		hit_timer_now = SDL_GetTicks() - hit_timer_start;
		if (hit_timer_now > hit_timer_total)
		{
			hit_timer_start = SDL_GetTicks();
			lives -= 1;
		}
		if (lives == 0)
			Disable();
	}
	if (c2->type == COLLIDER_AIR_ENEMY)
	{
		onhit_now = SDL_GetTicks() - onhit_start_time;
		//activate onhit animation
		going_onhit = true;
		//sound when hit flying enemy (Torpedo)
		if (onhit_now > onhit_total_time)
		{
			going_onhit = false;
			onhit_start_time = SDL_GetTicks();
			App->audio->Load("assets/effects/gunbird_205 [EFFECT] Collide with Objects.wav", App->audio->EFFECT);
			for (int i = 0; i < 3; i++)
			{
				App->audio->Play(App->audio->EFFECT);
			}
		}

		if (drop && shot_lvl > 1)
		{
			App->powerup->AddPowerUp(UPGRADE, (c2->rect.x + c2->rect.w / 2), (c2->rect.y + c2->rect.h / 2));
			shot_lvl -= 1;
			drop = false;
			drop_timer_start = SDL_GetTicks();
		}
	}
}