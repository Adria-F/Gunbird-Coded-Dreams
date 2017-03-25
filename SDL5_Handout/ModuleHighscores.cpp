#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneCastle.h"
#include "ModulePlayer.h"
#include "ModuleSceneMine.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleHighscores.h"
#include "ModuleWelcomeTitle.h"

ModuleHighscores::ModuleHighscores()
{
	// Background
	background.w = SCREEN_WIDTH;
	background.h = SCREEN_HEIGHT;
	background_x = 0;
	background_y = 0;
}

ModuleHighscores::~ModuleHighscores()
{}

// Load assets
bool ModuleHighscores::Start()
{
	LOG("Loading highscores scene");
	bool ret = true;
	graphics = App->textures->Load("assets/maps/highscore_nameregist.png");

	LOG("Loading music")
	App->audio->Load("assets/music/highscore.ogg");
	App->audio->Play();
	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable(); //Player in highscores?
	fading = false;

	return true;
}

// UnLoad assets
bool ModuleHighscores::CleanUp()
{
	LOG("Unloading highscore scene");
	App->audio->Stop();
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleHighscores::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, background_x, background_y, &background, 0.75f); // sea and sky

																				 // TODO 3: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->welcometitle);
		fading = true;
	}

	return UPDATE_CONTINUE;
}