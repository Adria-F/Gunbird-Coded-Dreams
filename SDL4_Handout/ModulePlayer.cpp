#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({7, 14, 60, 90});
	idle.PushBack({95, 15, 60, 89});
	idle.PushBack({184, 14, 60, 90});
	idle.PushBack({276, 11, 60, 93});
	idle.PushBack({366, 12, 60, 92});
	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({78, 131, 60, 88});
	forward.PushBack({162, 128, 64, 92});
	forward.PushBack({259, 128, 63, 90});
	forward.PushBack({352, 128, 54, 91});
	forward.PushBack({432, 131, 50, 89});
	forward.speed = 0.1f;

	// TODO 4: Make ryu walk backwards with the correct animations
	backward.PushBack({ 627, 129, 60, 90 });
	backward.PushBack({ 710, 128, 60, 90 });
	backward.PushBack({ 795, 127, 60, 90 });
	backward.PushBack({ 881, 128, 60, 91 });
	backward.PushBack({ 971, 129, 60, 89 });
	backward.speed = 0.1f;

	// Ryu Jump
	jumping.PushBack({ 17, 798, 54, 134 });
	jumping.PushBack({ 100, 798, 55, 134 });
	jumping.PushBack({ 176, 798, 49, 134 });
	jumping.PushBack({ 251, 798, 53, 134 });
	jumping.PushBack({ 327, 798, 47, 134 });
	jumping.PushBack({ 397, 798, 47, 134 });
	jumping.PushBack({ 464, 798, 55, 134 });
	jumping.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	jump = false;
	jump_state = 0;
	graphics = App->textures->Load("ryu.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	if (jump == false)
	{
		if (App->input->keyboard[SDL_SCANCODE_D] == 1)
		{
			current_animation = &forward;
			position.x += speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == 1)
		{
			current_animation = &backward;
			position.x -= speed;
		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		{
			jump = true;
		}
	}
	if (jump)
	{
		current_animation = &jumping;
		if (jump_state <= 3)
		{
			position.y -= speed;
		}
		else if (jump_state > 3 && jump_state <= 5.9)
		{
			position.y += speed;
		}
		jump_state += jumping.speed;
		if ((int)jump_state >= 7)
		{
			jump = false;
			jump_state = 0;
		}
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}