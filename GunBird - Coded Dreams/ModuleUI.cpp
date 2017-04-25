#include "Application.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"
#include "ModuleMarion.h"
#include "ModuleAsh.h"
#include "ModuleSceneCastle.h"
#include "ModuleHighscores.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include <stdio.h>

ModuleUI::ModuleUI()
{

	marion_anim.PushBack({ 5, 64, 21, 32 });//x - y - w - h
	marion_anim.PushBack({ 37, 64, 21, 32 });
	marion_anim.PushBack({ 68, 64, 21, 32 });
	marion_anim.PushBack({ 101, 64, 21, 32 });
	marion_anim.PushBack({ 5, 129, 23, 32 });//x - y - w - h
	marion_anim.PushBack({ 37, 129, 23, 32 });
	marion_anim.PushBack({ 68, 129, 23, 32 });
	marion_anim.PushBack({ 101, 129, 23, 32 });
	marion_anim.PushBack({ 5, 97, 23, 32 });
	marion_anim.PushBack({ 37, 97, 23, 32 });
	marion_anim.PushBack({ 68, 97, 23, 32 });
	marion_anim.PushBack({ 101, 97, 23, 32 });
	marion_anim.PushBack({ 5, 129, 23, 32 });//x - y - w - h
	marion_anim.PushBack({ 37, 129, 23, 32 });
	marion_anim.PushBack({ 68, 129, 23, 32 });
	marion_anim.PushBack({ 101, 129, 23, 32 });
	marion_anim.PushBack({ 5, 64, 21, 32 });//x - y - w - h
	marion_anim.PushBack({ 37, 64, 21, 32 });
	marion_anim.PushBack({ 68, 64, 21, 32 });
	marion_anim.PushBack({ 101, 64, 21, 32 });
	marion_anim.PushBack({ 3, 33, 23, 32 });//x - y - w - h
	marion_anim.PushBack({ 35, 33, 23, 32 });
	marion_anim.PushBack({ 66, 33, 23, 32 });
	marion_anim.PushBack({ 99, 33, 23, 32 });
	marion_anim.PushBack({ 3, 0, 23, 32 });
	marion_anim.PushBack({ 35, 0, 23, 32 });
	marion_anim.PushBack({ 66, 0, 23, 32 });
	marion_anim.PushBack({ 99, 0, 23, 32 });
	marion_anim.PushBack({ 3, 33, 23, 32 });//x - y - w - h
	marion_anim.PushBack({ 35, 33, 23, 32 });
	marion_anim.PushBack({ 66, 33, 23, 32 });
	marion_anim.PushBack({ 99, 33, 23, 32 });
	marion_anim.speed = 0.1f;

	ash_anim.PushBack({ 14, 13, 19, 32 });//x - y - w - h
	ash_anim.PushBack({ 43, 13, 19, 32 });
	ash_anim.PushBack({ 70, 55, 14, 32 });
	ash_anim.PushBack({ 94, 55, 14, 32 });
	ash_anim.PushBack({ 14, 13, 19, 32 });//x - y - w - h
	ash_anim.PushBack({ 43, 13, 19, 32 });
	ash_anim.PushBack({ 15, 97, 14, 32 });//x - y - w - h
	ash_anim.PushBack({ 39, 97, 14, 32 });
	ash_anim.speed = 0.1f;

	game_over_bckg.w = SCREEN_WIDTH;
	game_over_bckg.h = SCREEN_HEIGHT;

	char_pos.w = 15;
	char_pos.h = 13;

}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	font_score = App->fonts->Load("assets/UI/ui_fonts.png", "udP:0123456789 ", 3);
	highscores_score = App->fonts->Load("assets/UI/highscores_fonts.png", "01234.56789 ", 2);
	marion_texture = App->textures->Load("assets/characters/marion.png");
	ash_texture = App->textures->Load("assets/characters/ash.png");
	game_over = App->textures->Load("assets/UI/game over.png");
	char_lives = App->textures->Load("assets/UI/ash_marion_ui.png");

	App->fonts->Enable();

	return true;
}

bool ModuleUI::CleanUp()
{
	App->fonts->UnLoad(font_score);
	App->fonts->UnLoad(highscores_score);
	App->textures->Unload(marion_texture);
	App->textures->Unload(ash_texture);
	App->textures->Unload(game_over);
	App->textures->Unload(char_lives);

	marion_texture = nullptr;
	ash_texture = nullptr;
	game_over = nullptr;
	char_lives = nullptr;

	App->fonts->Disable();

	return true;
}

update_status ModuleUI::Update()
{
	if (App->marion->IsEnabled())
	{
		marion_score = App->marion->points;
		if (marion_score > marion_top_score)
		{
			marion_top_score = marion_score;
		}
		sprintf_s(score_text, 10, "%7d", App->marion->points);
		char_pos.x = 8;
		char_pos.y = 12;
		for (int i = 0; i < App->marion->lives; i++)
		{
			App->render->Blit(char_lives, 5 + ((char_pos.w + 2) * i), 20, &char_pos);
		}
	}
	
	if (App->scene_castle->IsEnabled() && App->scene_castle->lost == false)
	{
		App->fonts->BlitText(0, 5, font_score, "uP:");
		App->fonts->BlitText(25, 5, font_score, score_text);
	}

	if (App->ash->IsEnabled())
	{
		ash_score = App->ash->points;
		if (ash_score > ash_top_score)
		{
			ash_top_score = ash_score;
		}
		sprintf_s(score_text, 10, "%7d", App->ash->points);
		char_pos.x = 26;
		char_pos.y = 12;
		for (int i = 0; i < App->ash->lives; i++)
		{
			App->render->Blit(char_lives, 204 - ((char_pos.w + 2) * i), 20, &char_pos);
		}
	}
	if (App->scene_castle->lost)
	{
		App->render->Blit(game_over, 0, 0, &game_over_bckg);
	}
	else if (App->scene_castle->IsEnabled())
	{
		App->fonts->BlitText(130, 5, font_score, "dP:");
		App->fonts->BlitText(155, 5, font_score, score_text);
	}

	if (App->highscores->IsEnabled())
	{
		if (marion_score >= ash_score)
		{
			App->render->Blit(marion_texture, 12, 46, &(marion_anim.GetCurrentFrame()));
			sprintf_s(score_text, 10, "%7d", marion_top_score);
			App->fonts->BlitText(109, 58, highscores_score, score_text);
			App->render->Blit(ash_texture, 194, 70, &(ash_anim.GetCurrentFrame()));
			sprintf_s(score_text, 10, "%7d", ash_top_score);
			App->fonts->BlitText(109, 83, highscores_score, score_text);
		}
		else
		{
			App->render->Blit(marion_texture, 194, 70, &(marion_anim.GetCurrentFrame()));
			sprintf_s(score_text, 10, "%7d", marion_score);
			App->fonts->BlitText(109, 83, highscores_score, score_text);
			App->render->Blit(ash_texture, 12, 46, &(ash_anim.GetCurrentFrame()));
			sprintf_s(score_text, 10, "%7d", ash_score);
			App->fonts->BlitText(109, 58, highscores_score, score_text);

		}
	}

	return UPDATE_CONTINUE;
}