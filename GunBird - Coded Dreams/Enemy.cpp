#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleMarion.h"
#include "ModuleAsh.h"
#include "SDL/include/SDL_timer.h"

Enemy::Enemy(int x, int y, int wave, int id) : position(x, y), wave(wave), id (id)
{}

Enemy::~Enemy()
{
	App->textures->Unload(sprites);
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{
	Red_now = SDL_GetTicks() - Red_Start_time;

	if(collider != nullptr)
		collider->SetPos(App->render->camera.x + position.x, App->render->camera.y + position.y);

	if (animation != nullptr)
	{
		sprites = NormalSprite;
		if (hit && WhiteSprite != nullptr)
		{
			sprites = WhiteSprite;
			hit = false;
		}
		if (RedSprite != nullptr && lives <= (initial_hp/5) && Red_now >= Red_Total_time && Red_now <= (Red_Total_time + 50))
		{
			sprites = RedSprite;
		}
		if (RedSprite != nullptr && lives <= (initial_hp/5) && Red_now >= (Red_Total_time + 150))
		{
			sprites = RedSprite;
			Red_Start_time = SDL_GetTicks();
		}
		
		App->render->Blit(sprites, App->render->camera.x + position.x, App->render->camera.y + position.y, &(animation->GetCurrentFrame()));
	
		if (extra_anim && lives > 0)
			ExtraAnim(sprites);
	}
}

void Enemy::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_PLAYER_SHOT)
	{
		for (int i = 0; i < MAX_ACTIVE_PARTICLES; i++)
		{
			if (App->particles->active[i] != nullptr)
			{
				if (App->particles->active[i]->collider == collider)
				{
					lives -= App->particles->active[i]->damage;
					hit = true;
					if (lives <= 0)
					{
						if (App->particles->active[i]->type == P_MARION_BULLET_P1)
						{
							App->marion->points += points;
						}
						else if (App->particles->active[i]->type == P_MARION_BULLET_P2)
						{
							App->marion->points += points;
						}

						if (App->particles->active[i]->type == P_ASH_BULLET_P1)
						{
							App->ash->points += points;
						}
						else if (App->particles->active[i]->type == P_ASH_BULLET_P2)
						{
							App->ash->points += points;
						}
					}
					break;
				}
			}
		}
	}
	else if (collider->type == COLLIDER_BUILDING)
	{
		Draw(sprites);
	}
}

void Enemy::DeadAnim()
{
	animation = nullptr;
	collider->to_delete = true;
}