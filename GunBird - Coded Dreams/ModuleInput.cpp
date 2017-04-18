#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleDebugMode.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"

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

	if(keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	if (keyboard[SDL_SCANCODE_TAB] == KEY_STATE::KEY_DOWN)
	{
		if (App->debug->IsEnabled())
		{
			App->debug->Disable();
		}
		else
		{
			App->debug->Enable();
		}
	}

	if (keyboard[SDL_SCANCODE_SPACE])
	{
		if (App->fade->GetFadeState() == false)
		{
			App->audio->Load("assets/effects/gunbird_101 [VOICE] Coin (Credit Inserted).wav", App->audio->EFFECT);
			App->audio->Play(App->audio->EFFECT);
		}
	}

	if (keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN)
	{
		App->player->going_MARION_up = true;
		App->player->going_MARION_down = false;
	}
	if (keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP)
	{
		App->player->going_MARION_up = false;
	}
	if (keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN)
	{
		App->player->going_MARION_left = true;
		App->player->going_MARION_right = false;
	}
	if (keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP)
	{
		App->player->going_MARION_left = false;
	}
	if (keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN)
	{
		App->player->going_MARION_down = true;
		App->player->going_MARION_up = false;
	}
	if (keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP)
	{
		App->player->going_MARION_down = false;
	}
	if (keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN)
	{
		App->player->going_MARION_right = true;
		App->player->going_MARION_left = false;
	}
	if (keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP)
	{
		App->player->going_MARION_right = false;
	}

	//------------------------------------------------------------------------------------------ Jeff


	if (keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN)
	{
		App->player2->going_ASH_up= true;
		App->player2->going_ASH_down = false;
	}
	if (keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_UP)
	{
		App->player2->going_ASH_up = false;
	}
	if (keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN)
	{
		App->player2->going_ASH_left = true;
		App->player2->going_ASH_right = false;
	}
	if (keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_UP)
	{
		App->player2->going_ASH_left = false;
	}
	if (keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN)
	{
		App->player2->going_ASH_down = true;
		App->player2->going_ASH_up = false;
	}
	if (keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_UP)
	{
		App->player2->going_ASH_down = false;
	}
	if (keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN)
	{
		App->player2->going_ASH_right = true;
		App->player2->going_ASH_left = false;
	}
	if (keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_UP)
	{
		App->player2->going_ASH_right = false;
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