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

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneCastle::ModuleSceneCastle()
{
	// Background
	background.w = SCREEN_WIDTH;
	background.h = 3535;
	background_x = 0;
	background_y = -2895;
}

ModuleSceneCastle::~ModuleSceneCastle()
{}

// Load assets
bool ModuleSceneCastle::Start()
{
	LOG("Loading castle scene");
	
	graphics = App->textures->Load("assets/maps/castle_background.png");
	App->audio->Load("assets/music/title_castle.ogg");
	App->audio->Play();
	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();
	fading = false;

	return true;
}

// UnLoad assets
bool ModuleSceneCastle::CleanUp()
{
	LOG("Unloading castle scene");
	App->audio->Stop();
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneCastle::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, background_x, background_y, &background, 0.75f); // sea and sky

	// TODO 3: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->scene_mine);
		fading = true;
	}

	return UPDATE_CONTINUE;
}