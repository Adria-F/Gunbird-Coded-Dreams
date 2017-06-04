#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSceneMine.h"
#include "ModuleAudio.h"
#include "ModulePowerUp.h"
#include "SDL/include/SDL_timer.h"

Player::Player(int num)
{
	if (num == 1)
		collider_type = COLLIDER_PLAYER1_SHOT;
	else if (num == 2)
		collider_type = COLLIDER_PLAYER2_SHOT;
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
		bombs = 2;
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
		bomb_timer_now = SDL_GetTicks() - bomb_timer_start;
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
					App->particles->AddParticle(*character->shot_particle_lvl1, character->shot_lvl1, position.x + 5, position.y - 45, collider_type);
				else if (shot_lvl == 2) {
					
						if (character == (ModuleCharacter*)App->ash) {
							App->particles->AddParticle(*character->shot_particle_lvl2, character->shot_lvl2, position.x, position.y - 45, collider_type);
						}
						else
							App->particles->AddParticle(*character->shot_particle_lvl2, character->shot_lvl2, position.x + 5, position.y - 45, collider_type);
				}
				else if (shot_lvl == 3)
				{
					if (character == (ModuleCharacter*)App->marion)
					{
						App->particles->AddParticle(*character->shot_particle_lvl3_left, character->shot_lvl3_left, position.x - 10, position.y - 45, collider_type, 0, 120, ANGLE);
						App->particles->AddParticle(*character->shot_particle_lvl3_right, character->shot_lvl3_right, position.x + 10, position.y - 45, collider_type, 0, 60, ANGLE);
						App->particles->AddParticle(*character->shot_particle_lvl1, character->shot_lvl1, position.x + 5, position.y - 45, collider_type);
					}
					else
					App->particles->AddParticle(*character->shot_particle_lvl3, character->shot_lvl3, position.x-5, position.y - 45, collider_type);
					App->particles->AddParticle(*character->shot_particle_lvl3_donut, character->shot_lvl3_donut_p3, position.x - 15, position.y - 45, collider_type);
				}
					else if (shot_lvl == 4)
				{
					if (character == (ModuleCharacter*)App->marion)
					{
						App->particles->AddParticle(*character->shot_particle_lvl4_left, character->shot_lvl4_left, position.x - 10, position.y - 45, collider_type, 0, 120, ANGLE);
						App->particles->AddParticle(*character->shot_particle_lvl4_right, character->shot_lvl4_right, position.x + 10, position.y - 45, collider_type, 0, 60, ANGLE);
						App->particles->AddParticle(*character->shot_particle_lvl2, character->shot_lvl2, position.x + 5, position.y - 45, collider_type);
					}
					else
					App->particles->AddParticle(*character->shot_particle_lvl4, character->shot_lvl4, position.x + 5, position.y - 45, collider_type);
				}

				start_time = SDL_GetTicks();
				bullet_counter++;
			}
		}

		//Bomb system
		if (character == (ModuleCharacter*)App->marion)
		{
			if (bomb_attacking && (bomb_count == 0 || bomb_timer_now > bomb_timer_total))
			{
				if (bomb_count > 3 && bomb_timer_now > 1500)
				{
					bomb_count = 0;
					bomb_attacking = false;
				}
				else
				{
					if (bomb_count == 0 || bomb_count == 2)
					{
						App->particles->AddParticle(character->bomb_north, character->bomb, bomb_pos.x, bomb_pos.y, collider_type);
						App->particles->AddParticle(character->bomb_south, character->bomb, bomb_pos.x, bomb_pos.y, collider_type);
						App->particles->AddParticle(character->bomb_east, character->bomb, bomb_pos.x, bomb_pos.y, collider_type);
						App->particles->AddParticle(character->bomb_west, character->bomb, bomb_pos.x, bomb_pos.y, collider_type);
						bomb_count++;
						bomb_timer_start = SDL_GetTicks();
					}
					else if (bomb_count == 1 || bomb_count == 3)
					{
						App->particles->AddParticle(character->bomb_north_west, character->bomb, bomb_pos.x, bomb_pos.y, collider_type);
						App->particles->AddParticle(character->bomb_north_east, character->bomb, bomb_pos.x, bomb_pos.y, collider_type);
						App->particles->AddParticle(character->bomb_south_west, character->bomb, bomb_pos.x, bomb_pos.y, collider_type);
						App->particles->AddParticle(character->bomb_south_east, character->bomb, bomb_pos.x, bomb_pos.y, collider_type);
						bomb_count++;
						bomb_timer_start = SDL_GetTicks();
					}
				}
				for (int i = 0; i < MAX_ACTIVE_PARTICLES; i++)
				{
					if (App->particles->active[i] != nullptr && (App->particles->active[i]->type == P_SMALL_SHOT || App->particles->active[i]->type == P_MID_SHOT || App->particles->active[i]->type == P_BIG_SHOT))
					{
						App->particles->active[i]->to_delete = true;
					}
				}
			}
		}
		else if (character == (ModuleCharacter*)App->ash)
		{
			if (bomb_attacking)
			{
				if (bomb_timer_now > 3000)
				{
					bomb_count = 0;
					bomb_attacking = false;
				}
				else if (bomb_count == 0)
				{
					App->particles->AddParticle(character->dropping_bomb, character->bomb, bomb_pos.x - 111, bomb_pos.y - 222, collider_type, 0, 360);
					bomb_count++;
				}
				else if (bomb_count == 1 && bomb_timer_now > 500)
				{
					App->particles->AddParticle(character->bomb_north, character->bomb, bomb_pos.x - 111, bomb_pos.y - 222, collider_type);
					bomb_count++;
				}
				
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