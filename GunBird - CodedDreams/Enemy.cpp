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
	
	b1 = App->textures->Load("assets/enemies/explosions/big2.png");
	b2 = App->textures->Load("assets/enemies/explosions/big1.png");
	m1 = App->textures->Load("assets/enemies/explosions/medium1.png");
	m2 = App->textures->Load("assets/enemies/explosions/medium2.png");
	s1 = App->textures->Load("assets/enemies/explosions/small1.png");
	s2 = App->textures->Load("assets/enemies/explosions/small2.png");
	fm = App->textures->Load("assets/enemies/explosions/flying_machine.png");

	//Big1
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
	anim_s1.PushBack({ 12,10,48,37 });
	anim_s1.PushBack({ 77,11,48,37 });
	anim_s1.PushBack({ 137,13,48,37 });
	anim_s1.PushBack({ 197,12,48,37 });
	anim_s1.PushBack({ 12,61,48,37 });
	anim_s1.PushBack({ 72,62,48,37 });
	anim_s1.PushBack({ 136,62,48,37 });
	anim_s1.PushBack({ 196,62,48,37 });
	anim_s1.PushBack({ 12,110,48,37 });
	anim_s1.PushBack({ 73,111,48,37 });
	anim_s1.PushBack({ 134,111,48,37 });
	anim_s1.PushBack({ 194,111,48,37 });
	anim_s1.PushBack({ 12,153,48,37 });
	anim_s1.PushBack({ 73,153,48,37 });
	anim_s1.PushBack({ 134,153,48,37 });
	anim_s1.PushBack({ 0, 0, 0, 0 });
	anim_s1.speed = 1.0f;
	anim_s1.loop = false;
	/*
	anim_s1.life = 10000;
	anim_s1.speed.y = App->render->cam_speed;*/
	//small2
}

Enemy::~Enemy()
{
	App->textures->Unload(sprites);
	App->textures->Unload(NormalSprite);
	App->textures->Unload(RedSprite);
	App->textures->Unload(WhiteSprite);
	App->textures->Unload(b1);
	App->textures->Unload(b2);
	App->textures->Unload(m2);
	App->textures->Unload(m1);
	App->textures->Unload(s2);
	App->textures->Unload(s1);
	App->textures->Unload(fm);
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
	bool result = false;
	switch (explosion_type)
	{
	case BIG1:
		App->render->Blit(b1, App->render->camera.x + position.x - 20, App->render->camera.y + position.y - 20, &(anim_b1.GetCurrentFrame()));
		result = (anim_b1.GetCurrentFrameNum() == 4);
		break;
	case BIG2:
		App->render->Blit(b2, App->render->camera.x + position.x - 20, App->render->camera.y + position.y - 20, &(anim_b2.GetCurrentFrame()));
		result = (anim_b2.GetCurrentFrameNum() == 4);
		break;
	case MID1:
		App->render->Blit(m1, App->render->camera.x + position.x - 20, App->render->camera.y + position.y - 20, &(anim_m1.GetCurrentFrame()));
		result = (anim_m1.GetCurrentFrameNum() == 4);
		break;
	case MID2:
		App->render->Blit(m2, App->render->camera.x + position.x - 20, App->render->camera.y + position.y - 20, &(anim_m2.GetCurrentFrame()));
		result = (anim_m2.GetCurrentFrameNum() == 4);
		break;
	case SMALL1:
		App->render->Blit(s1, App->render->camera.x + position.x, App->render->camera.y + position.y, &(anim_s1.GetCurrentFrame()));
		result = (anim_s1.GetCurrentFrameNum() == 4);
		break;
	case SMALL2:
		App->render->Blit(s2, App->render->camera.x + position.x, App->render->camera.y + position.y, &(anim_s2.GetCurrentFrame()));
		result = (anim_s2.GetCurrentFrameNum() == 4);
		break;
	case FLYINGMACHINE:
		App->render->Blit(s2, App->render->camera.x + position.x, App->render->camera.y + position.y, &(anim_fm.GetCurrentFrame()));
		result = (anim_fm.GetCurrentFrameNum() == 24);
		break;
	}
	return result;
}