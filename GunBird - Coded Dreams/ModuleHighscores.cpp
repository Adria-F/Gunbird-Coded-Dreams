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
}

ModuleHighscores::~ModuleHighscores()
{}

// Load assets
bool ModuleHighscores::Start()
{
	LOG("Loading highscores scene");
	bool ret = true;
	App->render->moving_scene = false;
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	graphics = App->textures->Load("assets/maps/highscore_nameregist.png");

	LOG("Loading music");
	App->audio->Load("assets/music/highscore.ogg", App->audio->MUSIC);
	App->audio->Play(App->audio->MUSIC);

	fading = false;

	return true;
}

// UnLoad assets
bool ModuleHighscores::CleanUp()
{
	LOG("Unloading highscore scene");
	App->textures->Unload(graphics);
	graphics = nullptr;
	App->audio->Stop();

	return true;
}

// Update: draw background
update_status ModuleHighscores::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, App->render->camera.x, App->render->camera.y, &background, 0.75f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->welcometitle);
		fading = true;
	}

	return UPDATE_CONTINUE;
}