#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{

	// idle animation (arcade sprite sheet)
	idle.PushBack({68, 64, 18, 32}); //w - h - w - h
	idle.speed = 0.2f;

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
	Animation* current_animation = &idle;

	int speed = 3;

	if(App->input->keyboard[SDL_SCANCODE_W] && position.y > 32)
	{
		position.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] && position.x > 0)
	{
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] && position.y < SCREEN_HEIGHT)
	{
		position.y += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_D] && position.x < SCREEN_WIDTH - 18)
	{
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_DOWN) //The key state down is to control the spree you can shoot the bullets.
	{
		App->particles->AddParticle(App->particles->bullet, position.x+5, position.y-45);
	}
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();


	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}