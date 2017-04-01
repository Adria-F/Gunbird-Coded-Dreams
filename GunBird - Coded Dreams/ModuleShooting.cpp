#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleShooting.h"

ModuleShooting::ModuleShooting()
{
	//Marion Bullets
	bullet.x = 166;
	bullet.y = 127;
	bullet.h = 40;
	bullet.w = 20;
	
}
ModuleShooting::~ModuleShooting()
{}

bool ModuleShooting::Start()
{
	LOG("Loading ModuleShooting");
	bool ret = true;
	graphics = App->textures->Load("assets/characters/marion.png");
	LOG("Loading FX");

	return ret;
}

bool ModuleShooting::CleanUp()
{
	LOG("Unloading ModuleShooting");
	App->textures->Unload(graphics);
	graphics = nullptr;
	App->audio->Stop();
	return true;
}

update_status ModuleShooting::Update()
{
	return UPDATE_CONTINUE;
}
