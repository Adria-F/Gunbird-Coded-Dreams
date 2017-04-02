#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleWelcomeTitle.h"
#include "ModulePlayer.h"
#include "ModuleSelection.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleWelcomeTitle::ModuleWelcomeTitle()
{
	// Background
	background.w = SCREEN_WIDTH;
	background.h = SCREEN_HEIGHT;
}

ModuleWelcomeTitle::~ModuleWelcomeTitle()
{}

// Load assets
bool ModuleWelcomeTitle::Start()
{
	LOG("Loading WelcomeTitle scene");
	bool ret = true;
	App->render->moving_scene = false;
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	graphics = App->textures->Load("assets/maps/credit-insert_welcome-page.png");

	LOG("Loading music");
	App->audio->Load("assets/music/castle-welcome_title.ogg", App->audio->MUSIC);
	App->audio->Play(App->audio->MUSIC);
	// TODO 1: Enable (and properly disable) the player module
	fading = false;

	return ret;
}

// UnLoad assets
bool ModuleWelcomeTitle::CleanUp()
{
	LOG("Unloading welcome scene");
	App->textures->Unload(graphics);
	graphics = nullptr;
	App->audio->Stop();
	App->player->Disable();

	return true;
}

// Update: draw background

update_status ModuleWelcomeTitle::Update()
{
	// Draw everything --------------------------------------
	
	App->render->Blit(graphics, App->render->camera.x, App->render->camera.y, &background, 0.75f); // Welcome title Screen

	// TODO 3: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->selection);
		fading = true;
	}
	return UPDATE_CONTINUE;
}