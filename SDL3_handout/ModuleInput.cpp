#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

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
update_status ModuleInput::Update()
{
	SDL_PumpEvents();
	update_status status = UPDATE_CONTINUE;

	keyboard = SDL_GetKeyboardState(NULL);

	if (keyboard[SDL_SCANCODE_ESCAPE])
	{
		status = UPDATE_STOP;
	}
	if (keyboard[SDL_SCANCODE_UP])
	{
		if (App->render->background_y < 0)
		{
			App->render->background_y += 1;
		}
	}
	if (keyboard[SDL_SCANCODE_DOWN])
	{
		if (App->render->background_y > -2895)
		{
			App->render->background_y -= 1;
		}
	}

	// TODO 1: find out how to detect if the ESC key was pressed
	// and quit the game

	return status;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}