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
	bool CleanUp();

private:

	int player1_score;
	int player2_score;
	int player1_top_score;
	int player2_top_score;
	char score_text[10];
	int font_score = -1;
	int highscores_score = -1;
	SDL_Texture* marion_texture;
	SDL_Texture* ash_texture;
	SDL_Texture* game_over = nullptr;
	SDL_Rect game_over_bckg;
	SDL_Texture* char_lives = nullptr;
	SDL_Rect char_pos;
	SDL_Texture* debugging_text = nullptr;
	SDL_Texture* godMode_text = nullptr;
	SDL_Rect notification;

};

#endif // !__MODULE_UI_H__
