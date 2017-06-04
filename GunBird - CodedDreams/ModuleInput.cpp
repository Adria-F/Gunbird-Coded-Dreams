#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleSceneMine.h"
#include <iostream>

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;

	for (uint i = 0; i < MAX_BUTTONS; ++i)
		controller[i] = BUTTON_IDLE;

	SDL_Init(SDL_INIT_GAMECONTROLLER);
	if (SDL_NumJoysticks() < 1)
	{
		LOG("Warning: No joysticks connected!\n");
	}
	else
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			if (SDL_IsGameController(i))
			{
				game_controller = SDL_GameControllerOpen(i);
				std::cout << SDL_GameControllerMapping(game_controller) << std::endl;
				break;
			}
			else
			{
				LOG("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}
		}

	}
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
	SDL_Init(SDL_INIT_GAMECONTROLLER); //?
	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
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

	Uint8 button[MAX_BUTTONS];
	button[SDL_CONTROLLER_BUTTON_LEFTSHOULDER] = SDL_GameControllerGetButton(App->input->game_controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
	button[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] = SDL_GameControllerGetButton(App->input->game_controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
	button[SDL_CONTROLLER_BUTTON_A] = SDL_GameControllerGetButton(App->input->game_controller, SDL_CONTROLLER_BUTTON_A);
	button[SDL_CONTROLLER_BUTTON_B] = SDL_GameControllerGetButton(App->input->game_controller, SDL_CONTROLLER_BUTTON_B);
	button[SDL_CONTROLLER_BUTTON_Y] = SDL_GameControllerGetButton(App->input->game_controller, SDL_CONTROLLER_BUTTON_Y);
	button[SDL_CONTROLLER_BUTTON_DPAD_LEFT] = SDL_GameControllerGetButton(App->input->game_controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	button[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] = SDL_GameControllerGetButton(App->input->game_controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		if (button[i] == 1)
		{
			if (controller[i] == BUTTON_IDLE)
				controller[i] = BUTTON_DOWN;
			else
				controller[i] = BUTTON_REPEAT;
		}
		else
			if (controller[i] == BUTTON_REPEAT || controller[i] == BUTTON_DOWN)
				controller[i] = BUTTON_UP;
			else
				controller[i] = BUTTON_IDLE;
	}

	if(keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;
	if (App->scene_mine->lost == false)
	{
		//Player 1
		if (keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN || SDL_GameControllerGetAxis(App->input->game_controller, SDL_CONTROLLER_AXIS_LEFTY) < -13000)
			App->player1->going_up = true;
		else if (keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP || (keyboard[SDL_SCANCODE_W] != KEY_STATE::KEY_REPEAT && SDL_GameControllerGetAxis(App->input->game_controller, SDL_CONTROLLER_AXIS_LEFTY) > -15000))
			App->player1->going_up = false;
		if (keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN || SDL_GameControllerGetAxis(App->input->game_controller, SDL_CONTROLLER_AXIS_LEFTX) < -13000)
			App->player1->going_left = true;
		else if (keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP || (keyboard[SDL_SCANCODE_A] != KEY_STATE::KEY_REPEAT && SDL_GameControllerGetAxis(App->input->game_controller, SDL_CONTROLLER_AXIS_LEFTX) > -15000))
			App->player1->going_left = false;
		if (keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN || SDL_GameControllerGetAxis(App->input->game_controller, SDL_CONTROLLER_AXIS_LEFTY) > 10000)
			App->player1->going_down = true;
		else if (keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP || (keyboard[SDL_SCANCODE_S] != KEY_STATE::KEY_REPEAT && SDL_GameControllerGetAxis(App->input->game_controller, SDL_CONTROLLER_AXIS_LEFTY) < 10000))
			App->player1->going_down = false;
		if (keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN || SDL_GameControllerGetAxis(App->input->game_controller, SDL_CONTROLLER_AXIS_LEFTX) > 10000)
			App->player1->going_right = true;
		else if (keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP || (keyboard[SDL_SCANCODE_D] != KEY_STATE::KEY_REPEAT && SDL_GameControllerGetAxis(App->input->game_controller, SDL_CONTROLLER_AXIS_LEFTX) < 10000))
			App->player1->going_right = false;
		//Shot if key pressed
		if ((keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_DOWN || controller[SDL_CONTROLLER_BUTTON_A] == PAD_BUTON_STATE::BUTTON_DOWN) && App->player1->shot == false && App->player1->IsEnabled())
		{
			App->player1->shot = true;
			App->player1->bullet_counter = 0;
			if (App->player1->shot_lvl < 3)
			{
				App->audio->Load(App->player1->character->shot_path, App->audio->EFFECT);
			}
			else 
				App->audio->Load(App->player1->character->shot_path2, App->audio->EFFECT);

			App->audio->Play(App->audio->EFFECT);
		}
		if ((keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN || controller[SDL_CONTROLLER_BUTTON_B] == PAD_BUTON_STATE::BUTTON_DOWN) && App->player1->IsEnabled() && App->player1->bombs > 0 && App->player1->bomb_attacking == false)
		{
			App->player1->bombs--;
			App->player1->bomb_attacking = true;
			App->player1->bomb_timer_start = SDL_GetTicks();
			App->audio->Load(App->player1->character->bomb_path, App->audio->EFFECT);
			App->audio->Play(App->audio->EFFECT);
			App->player1->bomb_pos.x = App->player1->position.x - 10;
			App->player1->bomb_pos.y = App->player1->position.y - 16;
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
		if (keyboard[SDL_SCANCODE_KP_0] == KEY_STATE::KEY_DOWN && App->player2->shot == false && App->player2->IsEnabled())
		{
			App->player2->shot = true;
			App->player2->bullet_counter = 0;
			if (App->player2->shot_lvl < 3)
			{
				App->audio->Load(App->player2->character->shot_path, App->audio->EFFECT);
			}
			else 
				App->audio->Load(App->player2->character->shot_path2, App->audio->EFFECT);

			App->audio->Play(App->audio->EFFECT);
		}
		if (keyboard[SDL_SCANCODE_KP_PERIOD] == KEY_STATE::KEY_DOWN && App->player2->IsEnabled() && App->player2->bombs > 0 && App->player2->bomb_attacking == false)
		{
			App->player2->bombs--;
			App->player2->bomb_attacking = true;
			App->player2->bomb_timer_start = SDL_GetTicks();
			App->audio->Load(App->player2->character->bomb_path, App->audio->EFFECT);
			App->audio->Play(App->audio->EFFECT);
			App->player2->bomb_pos.x = App->player2->position.x - 10;
			App->player2->bomb_pos.y = App->player2->position.y - 16;
		}

		if (keyboard[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN || controller[SDL_CONTROLLER_BUTTON_LEFTSHOULDER] == PAD_BUTON_STATE::BUTTON_DOWN)
		{
			if (App->render->debugging)
				App->render->debugging = false;
			else
				App->render->debugging = true;
		}

		if (keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN || controller[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == PAD_BUTON_STATE::BUTTON_DOWN)
		{
			if (App->render->god_mode)
				App->render->god_mode = false;
			else
				App->render->god_mode = true;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}