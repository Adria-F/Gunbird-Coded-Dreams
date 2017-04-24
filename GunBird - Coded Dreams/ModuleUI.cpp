#include "Application.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"

ModuleUI::ModuleUI()
{
	font_score = App->fonts->Load("assets/UI/ui_fonts.png", "udP:0123456789 ");
}

ModuleUI::~ModuleUI()
{
}

update_status ModuleUI::Update()
{


	return UPDATE_CONTINUE;
}