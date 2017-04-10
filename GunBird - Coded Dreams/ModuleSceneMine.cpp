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
#include "ModuleCollision.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneMine::ModuleSceneMine()
{
	// Background
	background_rect.w = SCREEN_WIDTH;
	background_rect.h = 3535;

	// Above background
	above_background_rect.w = SCREEN_WIDTH;
	above_background_rect.h = 3245;
}

ModuleSceneMine::~ModuleSceneMine()
{}

// Load assets
bool ModuleSceneMine::Start()
{
	// Background
	LOG("Loading Mine Scene");
	LOG("Loading background assets");
	bool ret = true;
	App->render->moving_scene = true;
	graphics_background_text = App->textures->Load("assets/maps/mine_background.png");
	graphics_above_background_text = App->textures->Load("assets/maps/above mine_background.png");

	App->render->camera.x  = 0;
	App->render->camera.y = -3210;
	above_background_rect.y = 0;

	LOG("Loading music");
	App->audio->Load("assets/music/mine.ogg", App->audio->MUSIC);
	App->audio->Play(App->audio->MUSIC);

	App->player->Enable();
	App->collision->Enable();
	fading = false;

	return ret;
}

// Load assets
bool ModuleSceneMine::CleanUp()
{
	LOG("Unloading Mine scene");
	App->textures->Unload(graphics_above_background_text);
	App->textures->Unload(graphics_background_text);

	graphics_above_background_text = nullptr;
	graphics_background_text = nullptr;
	
	App->audio->Stop();
	App->player->Disable();
	App->collision->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneMine::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics_background_text, App->render->camera.x, App->render->camera.y, &background_rect, 0.75f); // back of the room

	above_background_rect.y -= 1;
	App->render->Blit(graphics_above_background_text, App->render->camera.x, App->render->camera.y + 290, &above_background_rect, 0.75f);
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->scene_castle);
		fading = true;
	}

	return UPDATE_CONTINUE;
}