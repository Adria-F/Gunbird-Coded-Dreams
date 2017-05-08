#include "Application.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneMine.h"
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

}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	font_score = App->fonts->Load("assets/UI/ui_fonts.png", "udP:0123456789 ", 3);
	highscores_score = App->fonts->Load("assets/UI/highscores_fonts.png", "01234.56789 ", 2);
	
	game_over = App->textures->Load("assets/UI/game over.png");
	char_lives = App->textures->Load("assets/UI/ash_marion_ui.png");

	App->fonts->Enable();

	return true;
}

bool ModuleUI::CleanUp()
{
	App->fonts->Unload(font_score);
	App->fonts->Unload(highscores_score);
	App->fonts->Disable();

	return true;
}

update_status ModuleUI::Update()
{
	if (App->player1->IsEnabled())
	{
		player1_score = App->player1->points;
		if (player1_score > player1_top_score)
		{
			player1_top_score = player1_score;
		}
		sprintf_s(score_text, 10, "%7d", App->player1->points);
		
		if (App->player1->character == App->marion)
			char_pos.x = 8;
		else if(App->player1->character == App->ash)
			char_pos.x = 26;

		for (int i = 0; i < App->player1->lives; i++)
		{
			App->render->Blit(char_lives, 5 + ((char_pos.w + 2) * i), 20, &char_pos);
		}
	}
	
	if (App->scene_mine->IsEnabled()) // && scene_mine->lost = false
	{
		App->fonts->BlitText(0, 5, font_score, "uP:");
		App->fonts->BlitText(25, 5, font_score, score_text);
	}

	if (App->player2->IsEnabled())
	{
		player2_score = App->player2->points;
		if (player2_score > player2_top_score)
		{
			player2_top_score = player2_score;
		}
		sprintf_s(score_text, 10, "%7d", App->player2->points);
		
		if (App->player2->character == App->marion)
			char_pos.x = 8;
		else if (App->player2->character == App->ash)
			char_pos.x = 26;

		for (int i = 0; i < App->player2->lives; i++)
		{
			App->render->Blit(char_lives, 204 - ((char_pos.w + 2) * i), 20, &char_pos);
		}
	}

	/*if (App->scene_mine->lost)
	{
		App->render->Blit(game_over, 0, 0, &game_over_bckg);
	}*/
	if (App->scene_mine->IsEnabled()) //else if
	{
		App->fonts->BlitText(130, 5, font_score, "dP:");
		App->fonts->BlitText(155, 5, font_score, score_text);
	}

	/*if (App->highscores->IsEnabled())
	{
		if (marion_score >= ash_score)
		{
			App->render->Blit(marion_texture, 12, 46, &(highscore_anim.GetCurrentFrame()));
			sprintf_s(score_text, 10, "%7d", marion_top_score);
			App->fonts->BlitText(109, 58, highscores_score, score_text);
			App->render->Blit(ash_texture, 194, 70, &(highscores_anim.GetCurrentFrame()));
			sprintf_s(score_text, 10, "%7d", ash_top_score);
			App->fonts->BlitText(109, 83, highscores_score, score_text);
		}
		else
		{
			App->render->Blit(marion_texture, 194, 70, &(highscore_anim.GetCurrentFrame()));
			sprintf_s(score_text, 10, "%7d", marion_score);
			App->fonts->BlitText(109, 83, highscores_score, score_text);
			App->render->Blit(ash_texture, 12, 46, &(highscores_anim.GetCurrentFrame()));
			sprintf_s(score_text, 10, "%7d", ash_score);
			App->fonts->BlitText(109, 58, highscores_score, score_text);

		}
	}*/

	return UPDATE_CONTINUE;
}