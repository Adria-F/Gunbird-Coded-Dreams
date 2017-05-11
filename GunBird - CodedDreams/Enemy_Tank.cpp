#include "Enemy_Tank.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Tank::Enemy_Tank(int x, int y, int wave) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/tankk.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_tank.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_tank.png");

	//Set animation steps, speed and loop
	open.PushBack({ 126, 11, 105, 61 });
	open.PushBack({ 250, 12, 105, 61 });
	open.PushBack({ 377, 11, 105, 61 });
	open.PushBack({ 5, 89, 105, 61 });
	open.PushBack({ 127, 88, 105, 61 });
	open.PushBack({ 252, 87, 105, 61 });
	open.PushBack({ 376, 88, 105, 61 });
	open.PushBack({ 6, 157, 105, 61 });
	open.PushBack({ 125, 154, 105, 61 });
	open.speed = 0.1f;
	open.loop = false;

	shooting.PushBack({ 5, 267, 105, 61 });
	shooting.PushBack({ 123, 268, 105, 61 });
	shooting.PushBack({ 245, 265, 105, 61 });
	shooting.PushBack({ 368, 263, 105, 61 });
	shooting.PushBack({ 5, 330, 105, 61 });

	dead.PushBack({ 6, 14, 105, 59 });
	dead.speed = 0.1f;
	dead.loop = true;
	
	//Set path
	path.PushBack({ -0.5f, 0.09f }, 100, &open);//Josep: He posat el 0.09f perque no es mogi cap a dalt. Suposo quen no era la teva intenció
	path.PushBack({ -0.5f, 0.09f }, 100, &shooting);//Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

											   //Set lives, initial_hp, points adn extra_anim
	lives = 52;
	initial_hp = lives;
	points = 5000;
	extra_anim = false;
	explosion_type = BIG1; //Explosion type

						   //Add and save collider
	collider = App->collision->AddCollider({ x, y, 100, 55 }, COLLIDER_ENEMY, (Module*)App->enemies);
}

Enemy_Tank::~Enemy_Tank()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Tank::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}

void Enemy_Tank::ExtraAnim(SDL_Texture* texture)
{

}

void Enemy_Tank::DeadAnim()
{
	animation = &dead;
}