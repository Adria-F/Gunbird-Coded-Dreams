#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleWelcomeTitle.h"
#include "ModuleMarion.h"
#include "ModuleSceneCastle.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleSelection.h"

ModuleSelection::ModuleSelection()
{
	// Background
	background.w = SCREEN_WIDTH;
	background.h = SCREEN_HEIGHT;
}

ModuleSelection::~ModuleSelection()
{}

// Load assets
bool ModuleSelection::Start()
{
	LOG("Loading Selection scene");
	bool ret = true;
	App->render->moving_scene = false;
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	graphics = App->textures->Load("assets/maps/selection.png");

	LOG("Loading music");
	App->audio->Load("assets/music/castle-welcome_title.ogg", App->audio->MUSIC);
	App->audio->Play(App->audio->MUSIC);

	fading = false;

	return ret;
}

// UnLoad assets
bool ModuleSelection::CleanUp()
{
	LOG("Unloading Selection scene");
	App->textures->Unload(graphics);
	graphics = nullptr;
	App->audio->Stop();

	return true;
}

// Update: draw background

update_status ModuleSelection::Update()
{
	// Draw everything --------------------------------------

	App->render->Blit(graphics, App->render->camera.x, App->render->camera.y, &background, 0.75f); // Selection Screen


	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->scene_castle, 0.5f);//0.5 serà millor per nosaltres per treballar bé
		fading = true;
	}
	return UPDATE_CONTINUE;
}