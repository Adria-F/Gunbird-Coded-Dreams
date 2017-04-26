#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAsh.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModulePowerUp.h"
#include "ModuleSceneCastle.h"
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

	//onhit flying enemies (Torpedo)
	onhit.PushBack({ 52, 43, 31, 31 });
	onhit.PushBack({ 90, 44, 31, 31 });
	onhit.PushBack({ 131, 47, 31, 31 });
	onhit.PushBack({ 168, 46, 31, 31 });
	onhit.PushBack({ 206, 46, 31, 31 });
	onhit.PushBack({ 16, 84, 31, 31 });
	onhit.PushBack({ 54, 84, 31, 31 });
	onhit.PushBack({ 92, 84, 31, 31 });
	onhit.PushBack({ 130, 84, 31, 31 });

	onhit.PushBack({ 15, 2, 31, 31 });
	onhit.PushBack({ 50, 4, 31, 31 });
	onhit.PushBack({ 89, 4, 31, 31 });
	onhit.PushBack({ 125, 6, 31, 31 });
	onhit.PushBack({ 166, 7, 31, 31 });
	onhit.PushBack({ 203, 8, 31, 31 });
	onhit.PushBack({ 16, 41, 31, 31 });
	onhit.speed = 0.25f;
}

ModuleAsh::~ModuleAsh()
{}

// Load assets
bool ModuleAsh::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	texture_graphics = App->textures->Load("assets/characters/ash.png"); // arcade version
	texture_onhit = App->textures->Load("assets/characters/Collision sprites.png");

	points = 0;

	position.x = 150;
	position.y = 266;

	shot_lvl = 1;
	lives = 3;

	Pcollider = App->collision->AddCollider({ 0, 0, 18, 32 }, COLLIDER_PLAYER, this);

	App->powerup->Enable();

	return ret;
}

bool ModuleAsh::CleanUp()
{
	bool ret = true;
	
	if (texture_graphics != nullptr)
	{
		App->textures->Unload(texture_graphics);
		texture_graphics = nullptr;
	}

	if (texture_onhit != nullptr)
	{
		App->textures->Unload(texture_onhit);
		texture_onhit = nullptr;
	}

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
	Animation* onhit_animation4 = &onhit;

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

	if (App->input->keyboard[SDL_SCANCODE_KP_0] == KEY_STATE::KEY_DOWN && shot == false && App->scene_castle->lost == false) //The key state down is to control the spree you can shoot the bullets.
	{
		shot = true;
		bullet_counter = 0;
		start_time = SDL_GetTicks();
		App->audio->Load("assets/effects/gunbird_209 [EFFECT] ASH (Shoots Level 1 & 2).wav", App->audio->EFFECT);
		App->audio->Play(App->audio->EFFECT);
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	SDL_Rect oh = onhit_animation4->GetCurrentFrame();

	Pcollider->SetPos(position.x, position.y - r.h);

	App->render->Blit(texture_graphics, position.x, position.y - r.h, &r);

	if (going_onhit == true)
	{
		App->render->Blit(texture_onhit, position.x - 7, position.y - 30, &oh);
		going_onhit = false;
	}

	return UPDATE_CONTINUE;
}

void ModuleAsh::OnCollision(Collider* c1, Collider* c2)
{
	if (shot_lvl < 1) {
		shot_lvl = 1;
	}

	drop_timer_start = SDL_GetTicks();
	if (c2->type == COLLIDER_DROPPING_ENEMY)
	{
		onhit_now = SDL_GetTicks() - onhit_start_time;

		//activate onhit animation
		going_onhit = true;

		//sound when hit flying enemy (Torpedo)
		if (onhit_now > onhit_total_time)
		{
			going_onhit = false;
			onhit_start_time = SDL_GetTicks();
			App->audio->Load("assets/effects/gunbird_205 [EFFECT] Collide with Objects.wav", App->audio->EFFECT);
			for (int i = 0; i < 3; i++)
			{
				App->audio->Play(App->audio->EFFECT);
			}
		}

		if (drop && shot_lvl > 1)
		{
			App->powerup->AddPowerUp(UPGRADE, (c2->rect.x + c2->rect.w / 2), (c2->rect.y + c2->rect.h / 2));
			shot_lvl -= 1;
			drop = false;
		}
	}
}
