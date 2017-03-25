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

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleWelcomeTitle::ModuleWelcomeTitle()
{
	// Background
	background.w = SCREEN_WIDTH;
	background.h = SCREEN_HEIGHT;
	background_x = 0;
	background_y = 0;
}

ModuleWelcomeTitle::~ModuleWelcomeTitle()
{}

// Load assets
bool ModuleWelcomeTitle::Start()
{
	LOG("Loading WelcomeTitle scene");
	bool ret = true;
	graphics = App->textures->Load("assets/maps/credit-insert_welcome-page.png");

	LOG("Loading music")
	App->audio->Load("assets/music/welcome_title.ogg");
	App->audio->Play();
	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();
	fading = false;

	return ret;
}

// UnLoad assets
bool ModuleWelcomeTitle::CleanUp()
{
	LOG("Unloading welcome scene");
	App->audio->Stop();
	App->player->Disable();

	return true;
}

// Update: draw background

update_status ModuleWelcomeTitle::Update()
{
	// Draw everything --------------------------------------
	
	App->render->Blit(graphics, background_x, background_y, &background, 0.75f); // Welcome title Screen

	// TODO 3: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->scene_mine);
		fading = true;
	}
	return UPDATE_CONTINUE;
}