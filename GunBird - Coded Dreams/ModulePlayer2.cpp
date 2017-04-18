#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModulePowerUp.h"
#include "SDL/include/SDL_timer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2()
{

	// idle animation
	idle.PushBack({ 14, 13, 19, 32 });//x - y - w - h
	idle.PushBack({ 43, 13, 19, 32 });
	idle.speed = 0.1f;

	//right animation
	right.PushBack({ 16, 55, 17, 32 });//x - y - w - h
	right.PushBack({ 43, 55, 17, 32 });
	right.PushBack({ 70, 55, 14, 32 });
	right.PushBack({ 94, 55, 14, 32 });
	right.speed = 0.1f;

	//left animation
	left.PushBack({ 15, 97, 14, 32 });//x - y - w - h
	left.PushBack({ 39, 97, 14, 32 });
	left.PushBack({ 63, 97, 17, 32 });
	left.PushBack({ 90, 97, 17, 32 });
	left.speed = 0.1f;
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("assets/characters/Ash.png"); // arcade version

	position2.x = 101;
	position2.y = 266;

	Pcollider = App->collision->AddCollider({ 0, 0, 18, 32 }, COLLIDER_PLAYER, this);

	App->powerup->Enable();

	return ret;
}

bool ModulePlayer2::CleanUp()
{
	bool ret = true;
	App->textures->Unload(graphics);
	graphics = nullptr;

	App->powerup->Disable();

	return ret;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	now = SDL_GetTicks() - start_time;

	drop_timer_now = SDL_GetTicks() - drop_timer_start;
	if (drop_timer_now >= drop_timer_total)
	{
		drop = true;
	}

	if ((bullet_counter == 0 || now >= total_time) && bullet_counter <= MAX_BULLETS && shot)
	{
		App->particles->AddParticle(App->particles->bullet, particle_type::P_BULLET, position2.x + 5, position2.y - 45, COLLIDER_PLAYER_SHOT);
		start_time = SDL_GetTicks();
		bullet_counter++;
		if (bullet_counter == MAX_BULLETS)
		{
			shot = false;
		}
	}

	Animation* current_animation = &idle;

	int speed = 3;

	if (going8_U && position2.y > 32)
	{
		position2.y -= speed;
	}
	if (going4_L)
	{
		current_animation = &right;
		if (position2.x > 0)
		{
			position2.x -= speed;
		}
	}
	if (going5_D && position2.y < SCREEN_HEIGHT)
	{
		position2.y += speed;
	}
	if (going6_R)
	{
		current_animation = &left;
		if (position2.x < SCREEN_WIDTH - 18)
		{
			position2.x += speed;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_KP_0] == KEY_STATE::KEY_DOWN && shot == false) //The key state down is to control the spree you can shoot the bullets.
	{
		shot = true;
		bullet_counter = 0;
		start_time = SDL_GetTicks();
		App->audio->Load("assets/effects/gunbird_211 [EFFECT] MARION (Shoots Level 1 & 2).wav", App->audio->EFFECT);
		App->audio->Play(App->audio->EFFECT);
	}

	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN)
	{
		App->powerup->AddPowerUp(powerup_type::UPGRADE, 100, 150);
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	Pcollider->SetPos(position2.x, position2.y - r.h);

	App->render->Blit(graphics, position2.x, position2.y - r.h, &r);

	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{

	drop_timer_start = SDL_GetTicks();
	if (c2->type == COLLIDER_DROPPING_ENEMY)
	{
		if (drop)
		{
			App->powerup->AddPowerUp(UPGRADE, (c2->rect.x + c2->rect.w / 2), (c2->rect.y + c2->rect.h / 2));
			drop = false;
		}
	}
}
