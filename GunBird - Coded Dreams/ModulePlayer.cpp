#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModulePowerUp.h"
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

	//Stars stele
	//1
	stele1.PushBack({ 169, 0, 11, 11 }); 
	stele1.PushBack({ 169, 16, 11, 11 });
	stele1.PushBack({ 169, 30, 11, 11 });
	stele1.PushBack({ 169, 45, 11, 11 });
	//2
	stele2.PushBack({ 184, 0, 11, 11 });
	stele2.PushBack({ 184, 16, 11, 11 });
	//3
	stele3.PushBack({ 199, 0, 11, 11 });
	stele3.PushBack({ 213, 0, 11, 11 });
	stele3.PushBack({ 230, 0, 11, 11 });
	stele3.PushBack({ 247, 0, 11, 11 });
	stele3.PushBack({ 261, 0, 11, 11 });
	stele3.PushBack({ 279, 0, 11, 11 });
	stele3.PushBack({ 199, 16, 11, 11 });
	stele3.PushBack({ 213, 16, 11, 11 });
	stele3.PushBack({ 230, 16, 11, 11 });
	stele3.PushBack({ 247, 16, 11, 11 });
	stele3.PushBack({ 261, 16, 11, 11 });
	stele3.PushBack({ 279, 16, 11, 11 });
	stele1.speed = 0.1f;
	stele2.speed = 0.1f;
	stele3.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}
// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("assets/characters/marion.png"); // arcade version
	
	position.x = 50;
	position.y = 266;

	Pcollider = App->collision->AddCollider({ 0, 0, 18, 32 }, COLLIDER_PLAYER, this);

	App->powerup->Enable();

	return ret;
}

bool ModulePlayer::CleanUp()
{
	bool ret = true;
	App->textures->Unload(graphics);
	graphics = nullptr;

	App->powerup->Disable();

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	now = SDL_GetTicks() - start_time;

	drop_timer_now = SDL_GetTicks() - drop_timer_start;
	if (drop_timer_now >= drop_timer_total)
	{
		drop = true;
	}
	
	if ((bullet_counter == 0 || now >= total_time) && bullet_counter <= MAX_BULLETS && shot)
	{
		App->particles->AddParticle(App->particles->MARION_bullet_particle, particle_type::P_MARION_BULLET, position.x + 5, position.y - 45, COLLIDER_PLAYER_SHOT);
		start_time = SDL_GetTicks();
		bullet_counter++;
		if (bullet_counter == MAX_BULLETS)
		{
			shot = false;
		}
	}
	
	Animation* current_animation = &idle;
	
	Animation* stele_animation1 = &stele1;
	Animation* stele_animation2 = &stele2;
	Animation* stele_animation3 = &stele3;

	int speed = 3;

	if(going_MARION_up && position.y > 32)
	{
		position.y -= speed;
	}
	if (going_MARION_left)
	{
		current_animation = &left;

		if (position.x > 0)
		{
			position.x -= speed;
		}
	}
	if (going_MARION_down && position.y < SCREEN_HEIGHT)
	{
		position.y += speed;
	}
	if (going_MARION_right)
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

	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN)
	{
		App->powerup->AddPowerUp(powerup_type::UPGRADE, 100, 150);
	}
	
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	SDL_Rect s1 = stele_animation1->GetCurrentFrame();
	SDL_Rect s2 = stele_animation2->GetCurrentFrame();
	SDL_Rect s3 = stele_animation3->GetCurrentFrame();

	Pcollider->SetPos(position.x, position.y - r.h);
	//Move graphics render
	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	//Stele render
	App->render->Blit(graphics, position.x+4, position.y - s1.h + 10, &s1);
	App->render->Blit(graphics, position.x + 4, position.y - s2.h + 15, &s2);
	App->render->Blit(graphics, position.x + 4, position.y - s3.h + 20, &s3);

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
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
	