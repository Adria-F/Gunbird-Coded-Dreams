#include "ModuleSelection.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMine.h"

ModuleSelection::ModuleSelection()
{

}

ModuleSelection::~ModuleSelection()
{

}

bool ModuleSelection::Start()
{


	return true;
}

bool ModuleSelection::CleanUp()
{


	return true;
}

update_status ModuleSelection::Update()
{

	if ((App->input->keyboard[SDL_SCANCODE_SPACE] || App->input->controller[SDL_CONTROLLER_BUTTON_Y] == PAD_BUTON_STATE::BUTTON_DOWN) && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->scene_mine, 0.5f);
		fading = true;
	}

	return UPDATE_CONTINUE;
}