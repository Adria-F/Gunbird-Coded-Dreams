#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleWelcomeTitle.h"
#include "ModulePlayer.h"
#include "ModuleSceneMine.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleSelection.h"

ModuleSelection::ModuleSelection()
{
	// Background
	background.w = SCREEN_WIDTH;
	background.h = SCREEN_HEIGHT;
	background_x = 0;
	background_y = 0;
}

ModuleSelection::~ModuleSelection()
{}

// Load assets
bool ModuleSelection::Start()
{
	LOG("Loading WelcomeTitle scene");
	bool ret = true;
	graphics = App->textures->Load("assets/maps/selection.png");

	LOG("Loading music");
	App->audio->Load("assets/music/castle-welcome_title.ogg");
	App->audio->Play(-1);
	// TODO 1: Enable (and properly disable) the player module
	fading = false;

	return ret;
}

// UnLoad assets
bool ModuleSelection::CleanUp()
{
	LOG("Unloading selection scene");
	App->textures->Unload(graphics);
	App->audio->Stop();
	App->player->Disable();

	return true;
}

// Update: draw background

update_status ModuleSelection::Update()
{
	// Draw everything --------------------------------------

	App->render->Blit(graphics, background_x, background_y, &background, 0.75f); // Selection Screen


	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->scene_mine);
		fading = true;
	}
	return UPDATE_CONTINUE;
}