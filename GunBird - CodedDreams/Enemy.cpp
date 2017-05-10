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
	//Big1
	b1 = App->textures->Load("assets/enemies/explosions/big2.png");

	anim_b1.PushBack({ 17,37,83,74 });
	anim_b1.PushBack({ 129,33,91,85 });
	anim_b1.PushBack({ 258,25,102,94 });
	anim_b1.PushBack({ 385,24,104,102 });

	anim_b1.PushBack({ 8,141,102,102 });
	anim_b1.PushBack({ 132,140,101,103 });
	anim_b1.PushBack({ 263,137,100,105 });
	anim_b1.PushBack({ 381,144,104,106 });

	anim_b1.PushBack({ 6,266,104,105 });
	anim_b1.PushBack({ 129,265,105,105 });
	anim_b1.PushBack({ 253,275,106,106 });
	anim_b1.PushBack({ 401,281,65,80 });
	anim_b1.PushBack({ 0, 0, 0, 0 }); //last one should be always transparent
	anim_b1.speed = 0.5f;
	anim_b1.loop = false;

	//big2
	//mid1
	//mid2
	//small1
	//small2
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
	if (lives <= 0 && die == false)
		die = explode();
	if (lives <= 0 && die)
		explode();
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
	switch (explosion_type)
	{
	case BIG1:
		App->render->Blit(b1, App->render->camera.x + position.x - 20, App->render->camera.y + position.y - 20, &(anim_b1.GetCurrentFrame()));
		break;
	case BIG2:
		App->render->Blit(b2, App->render->camera.x + position.x - 20, App->render->camera.y + position.y - 20, &(anim_b2.GetCurrentFrame()));
		break;
	case MID1:
		App->render->Blit(m1, App->render->camera.x + position.x - 20, App->render->camera.y + position.y - 20, &(anim_m1.GetCurrentFrame()));
		break;
	case MID2:
		App->render->Blit(m2, App->render->camera.x + position.x - 20, App->render->camera.y + position.y - 20, &(anim_m2.GetCurrentFrame()));
		break;
	case SMALL1:
		App->render->Blit(s1, App->render->camera.x + position.x - 20, App->render->camera.y + position.y - 20, &(anim_s1.GetCurrentFrame()));
		break;
	case SMALL2:
		App->render->Blit(s2, App->render->camera.x + position.x - 20, App->render->camera.y + position.y - 20, &(anim_s2.GetCurrentFrame()));
		break;
	}
	return (anim_b1.GetCurrentFrameNum() == 4);
}