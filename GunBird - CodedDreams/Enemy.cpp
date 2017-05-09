#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL_timer.h"

Enemy::Enemy(int x, int y, int wave, int id) : position(x, y), original_pos(x, y), wave(wave), id (id)
{
	b1 = App->textures->Load("assets/enemies/explosions/big1.png");
	explosion_b1.PushBack({ 10, 131, 69, 69 });
	explosion_b1.PushBack({ 82, 131, 69, 69 });
	explosion_b1.PushBack({ 152, 131, 69, 69 });
	explosion_b1.PushBack({ 228, 131, 69, 69 });
	explosion_b1.PushBack({ 303, 131, 69, 69 });
	explosion_b1.PushBack({ 16, 215, 68, 68 });
	explosion_b1.PushBack({ 82, 215, 68, 68 });
	explosion_b1.PushBack({ 152, 215, 68, 68 });
	explosion_b1.PushBack({ 228, 215, 68, 68 });
	explosion_b1.PushBack({ 303, 215, 68, 68 });
	explosion_b1.PushBack({ 82, 313, 68, 68 });
	explosion_b1.PushBack({ 152, 313, 68, 68 });
	explosion_b1.PushBack({ 228, 313, 68, 68 });
	explosion_b1.PushBack({ 303, 313, 68, 68 });
	explosion_b1.speed = 0.5f;
	explosion_b1.loop = false;
}

Enemy::~Enemy()
{
	App->textures->Unload(sprites);
	App->textures->Unload(NormalSprite);
	App->textures->Unload(RedSprite);
	App->textures->Unload(WhiteSprite);
	App->textures->Unload(b1);
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
		else if (RedSprite != nullptr && lives <= (initial_hp/5) && lives > 0 && Red_now >= Red_Total_time && Red_now <= (Red_Total_time + 50))
		{
			sprites = RedSprite;
		}
		else if (RedSprite != nullptr && lives <= (initial_hp/5) && lives > 0 && Red_now >= (Red_Total_time + 150))
		{
			sprites = RedSprite;
			Red_Start_time = SDL_GetTicks();
		}
		
		App->render->Blit(sprites, App->render->camera.x + position.x, App->render->camera.y + position.y, &(animation->GetCurrentFrame()));
	
		if (extra_anim && lives > 0)
			ExtraAnim(sprites);
	}
	if (lives <= 0)
		die = explode();
}

void Enemy::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_PLAYER_SHOT && die == false)
	{
		switch (collider->part->type)
		{
		case P_MARION_BULLET_P1:
			lives -= 1;
			break;
		case P_MARION_BULLET_P2:
			lives -= 2;
			break;
		case P_ASH_BULLET_P1:
			lives -= 1;
			break;
		case P_ASH_BULLET_P2:
			lives -= 2;
			break;
		default:
			lives -= 1;
			break;
		}
		hit = true;
		if (lives <= 0)
		{
			if (collider->part->type == P_MARION_BULLET_P1 || collider->part->type == P_MARION_BULLET_P2)
			{
				App->player1->points += points;
			}
			else if (collider->part->type == P_ASH_BULLET_P1 || collider->part->type == P_ASH_BULLET_P2)
			{
				App->player2->points += points;
			}
		}
	}
	else if (collider->type == COLLIDER_DECORATION)
	{
		Draw(sprites);
	}
}

void Enemy::DeadAnim()
{
	animation = nullptr;
}
bool Enemy::explode()
{
	switch (type)
	{
	case BIG1:
		App->render->Blit(b1, App->render->camera.x + position.x - 20, App->render->camera.y + position.y - 20, &(explosion_b1.GetCurrentFrame()));
		break;
	case BIG2:
		return true; //temporal
		break;
	case MID1:

		break;
	case MID2:

		break;
	case SMALL:

		break;
	}
	return (explosion_b1.GetCurrentFrameNum() == type);
}