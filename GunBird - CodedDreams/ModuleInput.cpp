#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleSceneMine.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}	

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if(keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;
	if (App->scene_mine->lost == false)
	{
		//Player 1
		if (keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN)
			App->player1->going_up = true;
		else if (keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP)
			App->player1->going_up = false;
		if (keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN)
			App->player1->going_left = true;
		else if (keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP)
			App->player1->going_left = false;
		if (keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN)
			App->player1->going_down = true;
		else if (keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP)
			App->player1->going_down = false;
		if (keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN)
			App->player1->going_right = true;
		else if (keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP)
			App->player1->going_right = false;
		//Shot if key pressed
		if (keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_DOWN && App->player1->shot == false)
		{
			App->player1->shot = true;
			App->player1->bullet_counter = 0;
			App->audio->Load(App->player1->character->shot_path, App->audio->EFFECT);
			App->audio->Play(App->audio->EFFECT);
		}

		//Player 2
		if (keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN)
			App->player2->going_up = true;
		else if (keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_UP)
			App->player2->going_up = false;
		if (keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN)
			App->player2->going_left = true;
		else if (keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_UP)
			App->player2->going_left = false;
		if (keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN)
			App->player2->going_down = true;
		else if (keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_UP)
			App->player2->going_down = false;
		if (keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN)
			App->player2->going_right = true;
		else if (keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_UP)
			App->player2->going_right = false;
		//Shot if key pressed
		if (keyboard[SDL_SCANCODE_KP_0] == KEY_STATE::KEY_DOWN && App->player2->shot == false)
		{
			App->player2->shot = true;
			App->player2->bullet_counter = 0;
			App->audio->Load(App->player1->character->shot_path, App->audio->EFFECT);
			App->audio->Play(App->audio->EFFECT);
		}

		if (keyboard[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN)
		{
			if (App->render->debugging)
				App->render->debugging = false;
			else
				App->render->debugging = true;
		}

		if (keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
		{
			if (App->render->god_mode)
				App->render->god_mode = false;
			else
				App->render->god_mode = true;
		}
	}

	if (keyboard[SDL_SCANCODE_BACKSPACE] == KEY_STATE::KEY_DOWN && App->render->debugging)
		App->scene_mine->lost = true;

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}