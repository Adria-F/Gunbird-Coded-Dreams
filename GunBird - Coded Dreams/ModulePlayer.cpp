#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL_timer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 5, 64, 21, 32 });//x - y - w - h
	idle.PushBack({ 37, 64, 21, 32 });
	idle.PushBack({ 68, 64, 21, 32 });
	idle.PushBack({ 101, 64, 21, 32 });
	idle.speed = 0.1f;

	//right animation
	//1st fase
	right.PushBack({ 5, 129, 23, 32 });//x - y - w - h
	right.PushBack({ 37, 129, 23, 32 });
	right.PushBack({ 68, 129, 23, 32 });
	right.PushBack({ 101, 129, 23, 32 });
	//2nd fase
	right.PushBack({ 5, 97, 23, 32 });
	right.PushBack({ 37, 97, 23, 32 });
	right.PushBack({ 68, 97, 23, 32 });
	right.PushBack({ 101, 97, 23, 32 });
	right.speed = 0.1f;

	//left animation
	left.PushBack({ 3, 33, 23, 32 });//x - y - w - h
	left.PushBack({ 35, 33, 23, 32 });
	left.PushBack({ 66, 33, 23, 32 });
	left.PushBack({ 99, 33, 23, 32 });
	left.PushBack({ 3, 0, 23, 32 });
	left.PushBack({ 35, 0, 23, 32 });
	left.PushBack({ 66, 0, 23, 32 });
	left.PushBack({ 99, 0, 23, 32 });
	left.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("assets/characters/marion.png"); // arcade version
	
	position.x = 101;
	position.y = 266;

	Pcollider = App->collision->AddCollider({ 0, 0, 18, 32 }, COLLIDER_PLAYER, this);

	return ret;
}

bool ModulePlayer::CleanUp()
{
	bool ret = true;
	App->textures->Unload(graphics);

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	now = SDL_GetTicks() - start_time;

	if ((bullet_counter == 0 || now >= total_time) && bullet_counter <= MAX_BULLETS && shot)
	{
		App->particles->AddParticle(App->particles->bullet, position.x + 5, position.y - 45, COLLIDER_PLAYER_SHOT);
		start_time = SDL_GetTicks();
		bullet_counter++;
		if (bullet_counter == MAX_BULLETS)
		{
			shot = false;
		}
	}
	
	Animation* current_animation = &idle;

	int speed = 3;

	if(goingW && position.y > 32)
	{
		position.y -= speed;
	}
	if (goingA)
	{
		current_animation = &left;
		if (position.x > 0)
		{
			position.x -= speed;
		}
	}
	if (goingS && position.y < SCREEN_HEIGHT)
	{
		position.y += speed;
	}
	if (goingD)
	{
		current_animation = &right;
		if (position.x < SCREEN_WIDTH - 18)
		{
			position.x += speed;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_DOWN && shot == false) //The key state down is to control the spree you can shoot the bullets.
	{
		shot = true;
		bullet_counter = 0;
		start_time = SDL_GetTicks();
		App->audio->Load("assets/effects/gunbird_211 [EFFECT] MARION (Shoots Level 1 & 2).wav", App->audio->EFFECT);
		App->audio->Play(App->audio->EFFECT);
	}
	
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	Pcollider->SetPos(position.x, position.y - r.h);

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}