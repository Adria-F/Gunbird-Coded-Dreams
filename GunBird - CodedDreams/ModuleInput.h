#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_gamecontroller.h"

#define MAX_KEYS 300
#define MAX_BUTTONS 16

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum PAD_BUTON_STATE
{
	BUTTON_IDLE = 0,
	BUTTON_DOWN,
	BUTTON_REPEAT,
	BUTTON_UP
};

class ModuleInput : public Module
{
public:

	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:

	KEY_STATE keyboard[MAX_KEYS];
	PAD_BUTON_STATE controller[MAX_BUTTONS];
	SDL_GameController *game_controller = nullptr;
};

#endif // __ModuleInput_H__