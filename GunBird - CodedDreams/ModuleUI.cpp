#include "Application.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneMine.h"
#include "ModuleHighscores.h"
#include "ModuleMarion.h"
#include "ModuleAsh.h"
#include <stdio.h>

ModuleUI::ModuleUI()
{

	game_over_bckg.w = SCREEN_WIDTH;
	game_over_bckg.h = SCREEN_HEIGHT;

	char_pos.w = 15;
	char_pos.h = 13;
	char_pos.y = 12;

	notification = { 0, 0, 73, 15 };
	marion_rect = { 8, 12, 14, 13 };
	ash_rect = { 28, 12, 11, 13 };

}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	font_score = App->fonts->Load("assets/UI/ui_fonts.png", "udP:0123456789 ", 3);
	highscores_points_score = App->fonts->Load("assets/UI/highscores_points_fonts.png", "01234.56789 ", 2);
	highscores_points_score_grey = App->fonts->Load("assets/UI/highscores_points_grey_fonts.png", "01234.56789 ", 2);
	highscores_score = App->fonts->Load("assets/UI/highscores_fonts.png", "1234567890:-player", 3);
	highscores_score_grey = App->fonts->Load("assets/UI/highscores_grey_fonts.png", "1234567890:-player", 3);
	
	marion_texture = App->textures->Load("assets/characters/marion.png");
	ash_texture = App->textures->Load("assets/characters/ash.png");
	game_over = App->textures->Load("assets/UI/game over.png");
	char_lives = App->textures->Load("assets/UI/ash_marion_ui.png");
	debugging_text = App->textures->Load("assets/UI/debugging_on.png");
	godMode_text = App->textures->Load("assets/UI/godmode_on.png");

	App->fonts->Enable();

	return true;
}

bool ModuleUI::CleanUp()
{
	Deactivate();
	
	App->textures->Unload(game_over);
	App->textures->Unload(char_lives);
	App->textures->Unload(marion_texture);
	App->textures->Unload(ash_texture);
	App->textures->Unload(debugging_text);
	App->textures->Unload(godMode_text);
	
	App->fonts->Unload(font_score);
	App->fonts->Unload(highscores_points_score);
	App->fonts->Unload(highscores_points_score_grey);
	App->fonts->Unload(highscores_score);
	App->fonts->Unload(highscores_score_grey);
	App->fonts->Disable();

	return true;
}

update_status ModuleUI::Update()
{
	if (App->render->debugging)
	{
		App->render->Blit(debugging_text, 0, 305, &notification);
	}
	if (App->render->god_mode)
	{
		App->render->Blit(godMode_text, 151, 305, &notification);
	}
	
	if (App->scene_mine->lost == false)
	{
		if (App->player1->IsEnabled())
		{
			player1_score = App->player1->points;
			if (player1_score > player1_top_score)
			{
				player1_top_score = player1_score;
			}
			sprintf_s(score_text1, 10, "%7d", App->player1->points);

			if (App->player1->character == App->marion)
				char_pos.x = 8;
			else if (App->player1->character == App->ash)
				char_pos.x = 26;

			for (int i = 0; i < App->player1->lives - 1; i++)
			{
				App->render->Blit(char_lives, 5 + ((char_pos.w + 2) * i), 20, &char_pos);
			}
		}

		if (App->scene_mine->IsEnabled())
		{
			App->fonts->BlitText(0, 5, font_score, "uP:");
			App->fonts->BlitText(25, 5, font_score, score_text1);
		}

		if (App->player2->IsEnabled())
		{
			player2_score = App->player2->points;
			if (player2_score > player2_top_score)
			{
				player2_top_score = player2_score;
			}
			sprintf_s(score_text2, 10, "%7d", App->player2->points);

			if (App->player2->character == App->marion)
				char_pos.x = 8;
			else if (App->player2->character == App->ash)
				char_pos.x = 26;

			for (int i = 0; i < App->player2->lives - 1; i++)
			{
				App->render->Blit(char_lives, 204 - ((char_pos.w + 2) * i), 20, &char_pos);
			}
		}

		if (App->scene_mine->IsEnabled())
		{
			App->fonts->BlitText(130, 5, font_score, "dP:");
			App->fonts->BlitText(155, 5, font_score, score_text2);
		}
	}
	else
		App->render->Blit(game_over, 0, 0, &game_over_bckg);

	if (App->highscores->IsEnabled())
	{
		highscore* curr = first;
		char pos = '1';
		for (int i = 0; i < 10; i++)
		{
			int points_font_id = highscores_points_score_grey;
			int text_font_id = highscores_score_grey;		
			if (curr && curr->active)
			{
				points_font_id = highscores_points_score;
				text_font_id = highscores_score;
			}

			App->fonts->BlitText(39, 52 + (24 * i), text_font_id, &pos);
			if (pos == '0')
			{
				App->fonts->BlitText(30, 52 + (24 * i), text_font_id, "1");
			}
			App->fonts->BlitText(50, 55 + (24 * i), text_font_id, ":");
			
			if (curr)
			{
				App->fonts->BlitText(64, 52 + (24 * i), text_font_id, ((curr->player == App->player1) ? "p1" : "p2"));
				char score[10];
				sprintf_s(score, 10, "%7d", curr->points);
				App->fonts->BlitText(109, 58 + (24 * i), points_font_id, score);
				if (curr->active)
				{
					App->render->Blit(((curr->character == App->marion) ? marion_texture : ash_texture), ((curr->player == App->player1)? 12 : 181), 46 + (24 * i), &(curr->character->highscore_anim.GetCurrentFrame()));
				}
				else
				{
					App->render->Blit(char_lives, 181, 56 + (24 * i), &((curr->character == App->marion) ?  marion_rect : ash_rect ));
				}
				curr = curr->below;
			}
			else
			{
				App->fonts->BlitText(64, 52 + (24 * i), text_font_id, "---");
			}

			// x = 39 | y = 52 + (24 * i) [NUMBER]
			// x = 50 | y = 55 + (24 * i) [:]

			// x = 64 | y = 52 + (24 * i) [PLAYERnum/---]
			// x = 109 | y = 58 + (24 * i) [POINTS]
			// x = 12/181 | y = 46 + (24 * i) [CHARACTER IMAGE ACTIVE]
			// x = 181 | y = 56 + (24 * i) [CHARACTER IMAGE NOT ACTIVE]
			if (i < 8)
				pos++;
			else
				pos = '0';
		}

		/*if (player1_score >= player2_score)
		{
			App->render->Blit(marion_texture, 12, 46, &(App->player1->character->highscore_anim.GetCurrentFrame()));
			sprintf_s(score_text1, 10, "%7d", player1_top_score);
			App->fonts->BlitText(109, 58, highscores_points_score, score_text1);
			App->render->Blit(ash_texture, 194, 70, &(App->player2->character->highscore_anim.GetCurrentFrame()));
			sprintf_s(score_text2, 10, "%7d", player2_top_score);
			App->fonts->BlitText(109, 83, highscores_points_score, score_text2);
		}
		else
		{
			App->render->Blit(marion_texture, 194, 70, &(App->player1->character->highscore_anim.GetCurrentFrame()));
			sprintf_s(score_text1, 10, "%7d", player1_score);
			App->fonts->BlitText(109, 83, highscores_points_score, score_text1);
			App->render->Blit(ash_texture, 12, 46, &(App->player2->character->highscore_anim.GetCurrentFrame()));
			sprintf_s(score_text2, 10, "%7d", player2_score);
			App->fonts->BlitText(109, 58, highscores_points_score, score_text2);
		}*/
	}

	return UPDATE_CONTINUE;
}