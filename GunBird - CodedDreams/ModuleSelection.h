#ifndef __MODULE_SELECTION_H__
#define __MODULE_SELECTION_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleSelection : public Module
{
public:

	ModuleSelection();
	~ModuleSelection();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	SDL_Rect lower_rect;
	SDL_Rect upper_rect;
	SDL_Rect scroll;
	bool fading;
	float scroll1_pos;
	float scroll2_pos;
	int selected_char;
};

#endif // !__MODULE_SELECTION_H__
