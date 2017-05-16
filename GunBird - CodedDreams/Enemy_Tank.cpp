#include "Enemy_Tank.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Tank::Enemy_Tank(int x, int y, int wave) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/Tank.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_Tank.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_Tank.png");

	//Set animation steps, speed and loop
	idle_motor.PushBack({ 6, 10, 110, 65 });
	idle_motor.PushBack({ 128, 10, 110, 65 });
	idle_motor.PushBack({ 250, 10, 110, 65 });
	idle_motor.PushBack({ 372, 10, 110, 65 });
	idle_motor.PushBack({ 494, 10, 110, 65 });
	idle_motor.PushBack({ 616, 10, 110, 65 });
	idle_motor.speed = 0.1f;
	idle_motor.loop = false;

	open_tur.PushBack({ 6, 91, 110, 65 });
	open_tur.PushBack({ 128, 91, 110, 65 });
	open_tur.PushBack({ 250, 91, 110, 65 });
	open_tur.PushBack({ 372, 91, 110, 65 });
	open_tur.speed = 0.1f;
	open_tur.loop = false;

	open_cent.PushBack({ 6, 256, 110, 65 });
	open_cent.PushBack({ 128, 256, 110, 65 });
	open_cent.PushBack({ 250, 256, 110, 65 });
	open_cent.PushBack({ 372, 256, 110, 65 });
	open_cent.PushBack({ 494, 256, 110, 65 });
	open_cent.speed = 0.05f;
	open_cent.loop = false;

	idle.PushBack({ 6, 338, 110, 65 });
	idle.PushBack({ 128, 338, 110, 65 });
	idle.PushBack({ 250, 338, 110, 65 });
	idle.PushBack({ 372, 338, 110, 65 });
	idle.PushBack({ 494, 338, 110, 65 });
	idle.PushBack({ 616, 338, 110, 65 });
	idle.speed = 0.2f;
	idle.loop = true;
	

	close_tur.PushBack({ 6, 420, 110, 65 });
	close_tur.PushBack({ 128, 420, 110, 65 });
	close_tur.PushBack({ 250, 420, 110, 65 });
	close_tur.PushBack({ 372, 420, 110, 65 });
	close_tur.speed = 0.1f;
	close_tur.loop = false;

	close_cent.PushBack({ 6, 502, 110, 65 });
	close_cent.PushBack({ 128, 502, 110, 65 });
	close_cent.PushBack({ 250, 502, 110, 65 });
	close_cent.PushBack({ 372, 502, 110, 65 });
	close_cent.PushBack({ 494, 502, 110, 65 });
	close_cent.PushBack({ 616, 502, 110, 65 });
	close_cent.PushBack({ 738, 502, 110, 65 });
	close_cent.PushBack({ 859, 502, 110, 65 });
	close_cent.speed = 0.05f;
	close_cent.loop = false;

	dead.PushBack({ 6, 585, 110, 65 });
	dead.PushBack({ 128, 585, 110, 65 });
	dead.PushBack({ 250, 585, 110, 65 });
	dead.PushBack({ 372, 585, 110, 65 });
	dead.PushBack({ 494, 585, 110, 65 });
	dead.PushBack({ 616, 585, 110, 65 });
	dead.PushBack({ 738, 585, 110, 65 });
	dead.PushBack({ 859, 585, 110, 65 });
	dead.speed = 0.1f;
	dead.loop = true;
	
	//Set path
	path.PushBack({ -0.5f, 0.09f }, 50, &idle_motor);//Josep: He posat el 0.09f perque no es mogi cap a dalt. Suposo quen no era la teva intenció
	path.PushBack({ -0.5f, 0.09f }, 100, &open_tur);
	path.PushBack({ -0.5f, 0.09f }, 100, &open_cent);
	path.PushBack({ -0.5f, 0.09f }, 1000, &idle);//Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

											   //Set lives, initial_hp, points adn extra_anim
	lives = 52;
	initial_hp = lives;
	points = 5000;
	extra_anim = false;
	explosion_type = BIG1; //Explosion type

						   //Add and save collider
	collider = App->collision->AddCollider({ x, y, 105, 60 }, COLLIDER_ENEMY, (Module*)App->enemies);
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
	position.y += 0.09f;
}