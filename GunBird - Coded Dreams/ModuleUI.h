#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleUI : public Module
{
public:

	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();

private:

	int marion_score;
	int ash_score;
	char score_text[10];
	int font_score = -1;
	int highscores_score = -1;
	Animation marion_anim;
	SDL_Texture* marion_texture;
	Animation ash_anim;
	SDL_Texture* ash_texture;

};

#endif // !__MODULE_UI_H__
