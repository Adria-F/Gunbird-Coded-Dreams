#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleSceneMine.h"
#include "Enemy.h"

//Include all enemies
#include "Enemy_Balloon.h"
#include "Enemy_Torpedo.h"
#include "Enemy_Tank.h"
#include "Enemy_Flying_Machine.h"
#include "Enemy_Miners.h"
#include "Enemy_Drone.h"
#include "Enemy_Trump.h"
#include "Enemy_Falling_Drone.h"
#include "Enemy_Barrel.h"
#include "Enemy_Megaman.h"
#include "Enemy_General_Turret.h"
#include "Enemy_Antiaircraft_left.h"
#include "Enemy_Antiaircraft_right.h"
#include "Enemy_Boss1_Base.h"
#include "Enemy_CentralSide.h"
#include "Enemy_LeftSide.h"
#include "Enemy_RightSide.h"


#define SPAWN_MARGIN 75

ModuleEnemies::ModuleEnemies()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	//sprites = App->textures->Load("rtype/enemies.png");

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if(-queue[i].y < App->render->camera.y + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].y * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	if (draw_underlayed)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)

			if (enemies[i] != nullptr && (enemies[i]->lower_level)) enemies[i]->Draw(enemies[i]->sprites);
	}
	else
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && App->scene_mine->lost == false)
			{
				if (enemies[i]->die) 
					enemies[i]->DeadAnim();
				else enemies[i]->Move();
			}
		}

		for (uint i = 0; i < MAX_ENEMIES; ++i)
			if (enemies[i] != nullptr && (enemies[i]->collider == nullptr) && (enemies[i]->lower_level == false)) enemies[i]->Draw(enemies[i]->sprites);

		for (uint i = 0; i < MAX_ENEMIES; ++i)
			if (enemies[i] != nullptr && (enemies[i]->collider != nullptr) && (enemies[i]->collider->type == COLLIDER_DECORATION) && (enemies[i]->lower_level == false)) enemies[i]->Draw(enemies[i]->sprites);

		for (uint i = 0; i < MAX_ENEMIES; ++i)
			if (enemies[i] != nullptr && (enemies[i]->collider != nullptr) && (enemies[i]->collider->type == COLLIDER_ENEMY) && (enemies[i]->lower_level == false)) enemies[i]->Draw(enemies[i]->sprites);

		for (uint i = 0; i < MAX_ENEMIES; ++i)
			if (enemies[i] != nullptr && (enemies[i]->collider != nullptr) && (enemies[i]->collider->type == COLLIDER_NONE) && (enemies[i]->lower_level == false)) enemies[i]->Draw(enemies[i]->sprites);

		for (uint i = 0; i < MAX_ENEMIES; ++i)
			if (enemies[i] != nullptr && (enemies[i]->collider != nullptr) && (enemies[i]->collider->type == COLLIDER_AIR_ENEMY) && (enemies[i]->lower_level == false)) enemies[i]->Draw(enemies[i]->sprites);
	}
	
	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to despawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			if (enemies[i]->position.x < -(SPAWN_MARGIN + 1) || enemies[i]->position.x >(SCREEN_WIDTH + (SPAWN_MARGIN + 1)) || enemies[i]->position.y > (-App->render->camera.y + SCREEN_HEIGHT + (SPAWN_MARGIN + 1)) || enemies[i]->position.y < (-App->render->camera.y - (SPAWN_MARGIN + 1)))
			//if ((abs((int)App->render->camera.y) + SCREEN_HEIGHT + SPAWN_MARGIN) < enemies[i]->position.y)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.y * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
		if (queue[i].type != NO_TYPE)
		{
			queue[i].type = NO_TYPE;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, int wave, int id)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].wave = wave;
			queue[i].id = id;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for(; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if(i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::TANK:
			enemies[i] = new Enemy_Tank(info.x, info.y, info.wave);
			break;
		case ENEMY_TYPES::TORPEDO:
			enemies[i] = new Enemy_Torpedo(info.x, info.y, info.wave);
			break;
		case ENEMY_TYPES::MINER:
			enemies[i] = new Enemy_Miners(info.x, info.y, info.wave, info.id);
			break;
		case ENEMY_TYPES::TRUMP:
			enemies[i] = new Enemy_Trump(info.x, info.y, info.wave, info.id);
			break;
		case ENEMY_TYPES::BALLON:
			enemies[i] = new Enemy_Balloon(info.x, info.y);
			break;
		case ENEMY_TYPES::FLYING_MACHINE:
			enemies[i] = new Enemy_Flying_Machine(info.x, info.y);
			break;
		case ENEMY_TYPES::DRONE:
			enemies[i] = new Enemy_Drone(info.x, info.y, info.wave, info.id);
			break;
		case ENEMY_TYPES::FALLING_DRONE:
			enemies[i] = new Enemy_Faling_Drone(info.x, info.y, info.wave, info.id);
			break;
		case ENEMY_TYPES::BARREL:
			enemies[i] = new Enemy_Barrel(info.x, info.y);
			break;
		case ENEMY_TYPES::MEGAMAN:
			enemies[i] = new Enemy_Megaman(info.x, info.y);
			break;
		case ENEMY_TYPES::GENERAL_TURRET:
			enemies[i] = new Enemy_General_Turret(info.x, info.y, info.wave, info.id);
			break;
		case ENEMY_TYPES::RIGHTSIDE:
			enemies[i] = new Enemy_RightSide(info.x, info.y);
			break;
		case ENEMY_TYPES::LEFTSIDE:
			enemies[i] = new Enemy_LeftSide(info.x, info.y);
			break;
		case ENEMY_TYPES::CENTRALSIDE:
			enemies[i] = new Enemy_CentralSide(info.x, info.y);
			break;
		case ENEMY_TYPES::BOSS1_BASE:
			enemies[i] = new Enemy_Boss1_Base(info.x, info.y, info.wave, info.id);
			break;
		case ENEMY_TYPES::ANTIAIRCRAFT_LEFT:
			enemies[i] = new Enemy_Antiaircraft_left(info.x, info.y, info.id);
			break;
		case ENEMY_TYPES::ANTIAIRCRAFT_RIGHT:
			enemies[i] = new Enemy_Antiaircraft_right(info.x, info.y, info.id);
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2);
			if (enemies[i]->lives <= 0 && enemies[i]->die == false)
			{
				enemies[i]->collider->to_delete = true;
				enemies[i]->collider = nullptr;
			}
			break;
		}
	}
}