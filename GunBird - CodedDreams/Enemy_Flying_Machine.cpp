#include "Enemy_Flying_Machine.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

Enemy_Flying_Machine::Enemy_Flying_Machine(int x, int y) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/Flying Machine.png");
	RedSprite = App->textures->Load("assets/enemies//hitten/hitten_red_Flying Machine.png");
	WhiteSprite = App->textures->Load("assets/enemies//hitten/hitten_white_Flying Machine.png");

	//Set animation steps, speed and loop

	//Low level
	idle_low.PushBack({ 36, 58, 90, 69 });
	idle_low.PushBack({ 147, 59, 90, 69 });
	idle_low.PushBack({ 252, 58, 90, 69 });
	idle_low.PushBack({ 362, 60, 90, 69 });
	idle_low.speed = 0.3f;
	idle_low.loop = true;

	//Grow level
	idle_grow.PushBack({ 36, 156, 90, 69 });
	idle_grow.PushBack({ 147, 155, 90, 69 });
	idle_grow.PushBack({ 254, 144, 90, 69 });
	idle_grow.PushBack({ 363, 143, 90, 69 });
	idle_grow.PushBack({ 480, 143, 90, 69 });
	idle_grow.PushBack({ 602, 143, 90, 69 });
	idle_grow.PushBack({ 710, 141, 90, 69 });
	idle_grow.PushBack({ 826, 141, 90, 69 });
	idle_grow.speed = 0.3f;
	idle_grow.loop = false;

	//Grow gun level
	idle_grow_gun.PushBack({ 36, 241, 90, 69 });
	idle_grow_gun.PushBack({ 149, 241, 90, 69 });
	idle_grow_gun.PushBack({ 258, 241, 90, 69 });
	idle_grow_gun.PushBack({ 362, 241, 90, 69 });
	idle_grow_gun.PushBack({ 484, 243, 90, 69 });
	idle_grow_gun.PushBack({ 598, 243, 90, 69 });
	idle_grow_gun.PushBack({ 709, 243, 90, 69 });
	idle_grow_gun.PushBack({ 825, 243, 90, 69 });
	idle_grow_gun.speed = 0.3f;
	idle_grow_gun.loop = false;

	//Up level
	idle_up.PushBack({ 40, 349, 90, 69 });
	idle_up.PushBack({ 149, 347, 90, 69 });
	idle_up.PushBack({ 259, 349, 90, 69 });
	idle_up.PushBack({ 363, 349, 90, 69 });
	idle_up.speed = 0.3f;
	idle_up.loop = true;

	//Death
	dead.PushBack({ 16, 132, 32, 58 });
	dead.PushBack({ 80, 132, 32, 58 });
	dead.speed = 0.1f;
	dead.loop = false;

	//Set path
	path.PushBack({ 0.0f, 0.0f }, 225, &idle_low);
	path.PushBack({ -0.75f, -0.6f }, 250, &idle_low);
	path.PushBack({ 0.01f, 0.15f }, 75, &idle_low); // fix previous position
	path.PushBack({ 0.012f, -0.23f }, 1100, &idle_low);
	path.PushBack({ -0.2f, -0.75f }, 85, &idle_low);
	path.PushBack({ -0.15f, -0.75f }, 30, &idle_grow);
	path.PushBack({ -0.1f, -0.45f }, 30, &idle_grow_gun);
	// UP 1
	path.PushBack({ 0.0f, -0.85f }, 85, &idle_up);
	path.PushBack({ 0.0f, -0.45f }, 15, &idle_up);
	path.PushBack({ 0.0f, 0.0f }, 15, &idle_up);
	// DOWN 1
	path.PushBack({ 0.0f, 0.45f - 0.09f}, 15, &idle_up);
	path.PushBack({ 0.0f, 0.85f - 0.09f }, 40, &idle_up);
	path.PushBack({ 0.0f, 0.45f - 0.09f }, 15, &idle_up);
	path.PushBack({ 0.0f, 0.0f - 0.09f }, 15, &idle_up);
	// UP 2
	path.PushBack({ 0.0f, -0.45f }, 15, &idle_up);
	path.PushBack({ 0.0f, -0.85f }, 125, &idle_up);
	path.PushBack({ 0.0f, -0.45f }, 15, &idle_up);
	path.PushBack({ 0.0f, 0.0f }, 15, &idle_up);
	// DOWN 2
	path.PushBack({ 0.0f, 0.45f - 0.09f }, 15, &idle_up);
	path.PushBack({ 0.0f, 0.85f - 0.09f }, 50, &idle_up);
	path.PushBack({ 0.0f, 0.45f - 0.09f }, 15, &idle_up);
	path.PushBack({ 0.0f, 0.0f - 0.09f }, 15, &idle_up);
	// UP 3
	path.PushBack({ 0.0f, -0.45f }, 15, &idle_up);
	path.PushBack({ 0.0f, -0.85f }, 130, &idle_up);
	path.PushBack({ 0.0f, -0.45f }, 15, &idle_up);
	path.PushBack({ 0.0f, 0.0f }, 15, &idle_up);
	// DOWN 3
	path.PushBack({ 0.0f, 0.45f - 0.09f }, 15, &idle_up);
	path.PushBack({ 0.0f, 0.85f - 0.09f }, 50, &idle_up);
	path.PushBack({ 0.0f, 0.45f - 0.09f }, 15, &idle_up);
	path.PushBack({ 0.0f, 0.0f - 0.09f }, 15, &idle_up);
	// UP 4
	path.PushBack({ 0.0f, -0.45f }, 15, &idle_up);
	path.PushBack({ 0.0f, -0.85f }, 135, &idle_up);
	path.PushBack({ 0.0f, -0.45f }, 15, &idle_up);
	path.PushBack({ 0.0f, 0.0f }, 15, &idle_up);

	// DOWN LAST
	path.PushBack({ 0.0f, 0.45f - 0.09f }, 15, &idle_up);
	path.PushBack({ 0.0f, 1.0f - 0.09f }, 300, &idle_up);
	path.PushBack({ 0.0f, 0.0f}, 200, &idle_up);

	//Set lives, initial_hp, points adn extra_anim
	lives = 90;
	initial_hp = lives;
	points = 5000;
	extra_anim = false;
	explosion_type = BIG1;
	Shot_Total_time = (Uint32)(2500.0f);

	//Add and save collider
	collider = App->collision->AddCollider({ x, y, 90, 69 }, COLLIDER_AIR_ENEMY, (Module*)App->enemies);
}

Enemy_Flying_Machine::~Enemy_Flying_Machine()
{

}

void Enemy_Flying_Machine::Move()
{

	position = original_pos + path.GetCurrentPosition(&animation);
	Shot_now = SDL_GetTicks() - Shot_Start_time;
	if (lower_level == false)
	{
		if (Shot_now > Shot_Total_time)
		{
			Shot_Start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 5, position.y + App->render->camera.y + 40, COLLIDER_ENEMY_SHOT, 0, 270, ANGLE);
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 5, position.y + App->render->camera.y + 40, COLLIDER_ENEMY_SHOT, 0, 248, ANGLE);
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 5, position.y + App->render->camera.y + 40, COLLIDER_ENEMY_SHOT, 0, 226, ANGLE);
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 5, position.y + App->render->camera.y + 40, COLLIDER_ENEMY_SHOT, 0, 204, ANGLE);
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 5, position.y + App->render->camera.y + 40, COLLIDER_ENEMY_SHOT, 0, 180, ANGLE);

			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 60, position.y + App->render->camera.y + 40, COLLIDER_ENEMY_SHOT, 0, 270, ANGLE);
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 60, position.y + App->render->camera.y + 40, COLLIDER_ENEMY_SHOT, 0, 292, ANGLE);
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 60, position.y + App->render->camera.y + 40, COLLIDER_ENEMY_SHOT, 0, 314, ANGLE);
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 60, position.y + App->render->camera.y + 40, COLLIDER_ENEMY_SHOT, 0, 336, ANGLE);
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 60, position.y + App->render->camera.y + 40, COLLIDER_ENEMY_SHOT, 0, 360, ANGLE);
		}
	}

	if (collider != nullptr)
	{
		if (path.GetCurrentAnimation() == &idle_grow_gun || path.GetCurrentAnimation() == &idle_up)
		{
			collider->rect = { (int)position.x, (int)position.y, 90, 69 };
			lower_level = false;
		}
		else
		{
			collider->rect = { 0, 0, 0, 0 };
			lower_level = true;
		}
	}
}