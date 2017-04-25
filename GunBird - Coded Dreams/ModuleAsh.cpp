#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAsh.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModulePowerUp.h"
#include "SDL/include/SDL_timer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleAsh::ModuleAsh()
{

	// idle animation
	idle.PushBack({ 14, 13, 19, 32 });//x - y - w - h
	idle.PushBack({ 43, 13, 19, 32 });
	idle.speed = 0.3f;

	//right animation
	right.PushBack({ 70, 55, 14, 32 });
	right.PushBack({ 94, 55, 14, 32 });
	right.speed = 0.3f;

	//left animation
	left.PushBack({ 15, 97, 14, 32 });//x - y - w - h
	left.PushBack({ 39, 97, 14, 32 });
	left.speed = 0.3f;

	//right.PushBack({ 16, 55, 17, 32 });//x - y - w - h
	//right.PushBack({ 43, 55, 17, 32 });

	//left.PushBack({ 63, 97, 17, 32 });
	//left.PushBack({ 90, 97, 17, 32 });
}

ModuleAsh::~ModuleAsh()
{}

// Load assets
bool ModuleAsh::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("assets/characters/ash.png"); // arcade version

	points = 0;

	position.x = 150;
	position.y = 266;

	Pcollider = App->collision->AddCollider({ 0, 0, 18, 32 }, COLLIDER_PLAYER, this);

	App->powerup->Enable();

	return ret;
}

bool ModuleAsh::CleanUp()
{
	bool ret = true;
	App->textures->Unload(graphics);
	graphics = nullptr;
	if (Pcollider != nullptr)
	{
		Pcollider->to_delete = true;
	}

	App->powerup->Disable();

	return ret;
}

// Update: draw background
update_status ModuleAsh::Update()
{
	now = SDL_GetTicks() - start_time;

	drop_timer_now = SDL_GetTicks() - drop_timer_start;
	if (drop_timer_now >= drop_timer_total)
	{
		drop = true;
	}

	if (shot_lvl < 2)
	{
		if ((bullet_counter == 0 || now >= total_time) && bullet_counter <= MAX_BULLETS && shot)
		{
			App->particles->AddParticle(App->particles->ASH_bullet_p1_particle, particle_type::P_ASH_BULLET_P1, position.x + 5, position.y - 45, COLLIDER_PLAYER_SHOT);
			start_time = SDL_GetTicks();
			bullet_counter++;
			if (bullet_counter == MAX_BULLETS)
			{
				shot = false;
			}
		}
	}
	//test
	else if (shot_lvl >= 2)
	{
		if ((bullet_counter == 0 || now >= total_time) && bullet_counter <= MAX_BULLETS && shot)
		{
			App->particles->AddParticle(App->particles->ASH_bullet_p2_particle, particle_type::P_ASH_BULLET_P2, position.x, position.y - 55, COLLIDER_PLAYER_SHOT);
			start_time = SDL_GetTicks();
			bullet_counter++;
			if (bullet_counter == MAX_BULLETS)
			{
				shot = false;
			}
		}
	}

	Animation* current_animation = &idle;

	int speed = 3;

	if (going_up && position.y > 32)
	{
		position.y -= speed;
	}
	if (going_left)
	{
		current_animation = &right;
		if (position.x > 0)
		{
			position.x -= speed;
		}
	}
	if (going_down && position.y < SCREEN_HEIGHT)
	{
		position.y += speed;
	}
	if (going_right)
	{
		current_animation = &left;
		if (position.x < SCREEN_WIDTH - 18)
		{
			position.x += speed;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_KP_0] == KEY_STATE::KEY_DOWN && shot == false) //The key state down is to control the spree you can shoot the bullets.
	{
		shot = true;
		bullet_counter = 0;
		start_time = SDL_GetTicks();
		App->audio->Load("assets/effects/gunbird_209 [EFFECT] ASH (Shoots Level 1 & 2).wav", App->audio->EFFECT);
		App->audio->Play(App->audio->EFFECT);
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	Pcollider->SetPos(position.x, position.y - r.h);

	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}

void ModuleAsh::OnCollision(Collider* c1, Collider* c2)
{
	drop_timer_start = SDL_GetTicks();
	if (c2->type == COLLIDER_DROPPING_ENEMY)
	{
		if (drop && shot_lvl > 1)
		{
			App->powerup->AddPowerUp(UPGRADE, (c2->rect.x + c2->rect.w / 2), (c2->rect.y + c2->rect.h / 2));
			shot_lvl -= 1;
			drop = false;
		}
	}
}
