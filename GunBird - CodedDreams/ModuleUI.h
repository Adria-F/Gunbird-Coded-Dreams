#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleCharacter.h"
#include "ModulePlayer.h"

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
	char score_text1[10];
	char score_text2[10];
	int font_score = -1;
	int highscores_score = -1;
	int highscores_score_grey = -1;
	int highscores_points_score = -1;
	int highscores_points_score_grey = -1;
	SDL_Texture* marion_texture;
	SDL_Texture* ash_texture;
	SDL_Texture* game_over = nullptr;
	SDL_Rect game_over_bckg;
	SDL_Texture* char_lives = nullptr;
	SDL_Rect char_pos;
	SDL_Texture* debugging_text = nullptr;
	SDL_Texture* godMode_text = nullptr;
	SDL_Rect notification;
	SDL_Rect marion_rect;
	SDL_Rect ash_rect;
	
	struct highscore
	{
		int points;
		ModuleCharacter* character;
		Player* player;
		highscore* above;
		highscore* below;
		bool active;

		highscore(int points, ModuleCharacter* character, Player* player)
		{
			above = nullptr;
			below = nullptr;
			this->points = points;
			this->character = character;
			this->player = player;
			active = false;
		}
	};

	highscore* first = nullptr;
	highscore* last = nullptr;
	int numHighscores = 0;

public:

	void Addhighscore(int points, ModuleCharacter* character, Player* player)
	{
		if (numHighscores < 10 || points > last->points)
		{
			highscore* temp = new highscore(points, character, player);
			temp->below = first;
			if (first)
				first->above = temp;
			first = temp;
			if (last == nullptr)
				last = first;

			while (temp->below && temp->points < temp->below->points)
			{
				highscore* toSwap = temp->below;
				highscore* above = temp->above;
				highscore* below = toSwap->below;

				toSwap->below = temp;
				temp->above = toSwap;
				toSwap->above = above;
				temp->below = below;
				if (above)
					above->below = toSwap;
				else
					first = toSwap;
				if (below)
					below->above = temp;
				if (toSwap == last)
					last = temp;
			}
			temp->active = true;
			numHighscores++;

			if (numHighscores > 10)
			{
				last = last->above;
				delete last->below;
				last->below = nullptr;
				numHighscores--;
			}
		}
	}

	void Deactivate()
	{
		highscore* curr = first;
		while (curr != nullptr)
		{
			curr->active = false;
			curr = curr->below;
		}
	}

};

#endif // !__MODULE_UI_H__
