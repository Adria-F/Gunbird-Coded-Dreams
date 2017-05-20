#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"

#define MAX_ENEMIES 100

enum ENEMY_TYPES
{
	NO_TYPE,
	TANK,
	TORPEDO,
	TRUMP,
	BALLON,
	FLYING_MACHINE,
	DRONE,
	MINER,
	FALLING_DRONE,
	BARREL,
	GENERAL_TURRET,
	MEGAMAN,
	RIGHTSIDE,
	LEFTSIDE,
	CENTRALSIDE,
	BOSS1_BASE,
	ANTIAIRCRAFT
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y, wave, id;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y, int wave = 1, int id = 0);

public:

	bool draw_underlayed = false;

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	//SDL_Texture* sprites;
};

#endif // __ModuleEnemies_H__