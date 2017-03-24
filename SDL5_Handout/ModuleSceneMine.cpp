#include "Globals.h"
#include "Application.h"
#include "ModuleSceneMine.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneCastle.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneMine::ModuleSceneMine()
{
	// Background
	background.w = SCREEN_WIDTH;
	background.h = 3535;
	background_x = 0;
	background_y = -2895;
}

ModuleSceneMine::~ModuleSceneMine()
{}

// Load assets
bool ModuleSceneMine::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("assets/maps/mine_background.png");

	LOG("Loading music");
	App->audio->Load("assets/music/mine.ogg");
	App->audio->Play();
	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();
	fading = false;

	return ret;
}

// Load assets
bool ModuleSceneMine::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading mine stage");
	App->audio->Stop();
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneMine::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, background_x, background_y, &background, 0.75f); // back of the room

	// TODO 3: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->scene_castle);
		fading = true;
	}

	return UPDATE_CONTINUE;
}