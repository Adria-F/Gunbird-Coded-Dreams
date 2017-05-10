#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
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
	return true;
}

update_status Player::Update()
{
	if (character != nullptr)
	{
		now = SDL_GetTicks() - start_time;
		
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
				App->particles->AddParticle(*character->shot_particle_lvl1, character->shot_lvl1, position.x + 5, position.y - 45, COLLIDER_PLAYER_SHOT);
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