#include "Application.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"
#include "ModuleMarion.h"
#include "ModuleAsh.h"
#include <stdio.h>

ModuleUI::ModuleUI()
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	font_score = App->fonts->Load("assets/UI/ui_fonts.png", "udP:0123456789 ");

	return true;
}

update_status ModuleUI::Update()
{
	if (App->marion->IsEnabled())
	{
		sprintf_s(score_text, 10, "%7d", App->marion->score);
		App->fonts->BlitText(0, 0, font_score, "uP:");
		App->fonts->BlitText(30, 0, font_score, score_text);
	}
	if (App->ash->IsEnabled())
	{

	}

	return UPDATE_CONTINUE;
}