/*
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
rect_bullet.x = 166;
rect_bullet.y = 127;
rect_bullet.h = 40;
rect_bullet.w = 20;

//Enemy Medium Bullets

rect_enemy_medium_bullet.x = 7;
rect_enemy_medium_bullet.y = 7;
rect_enemy_medium_bullet.h = 10;
rect_enemy_medium_bullet.w = 10;

}
ModuleShooting::~ModuleShooting()
{}

bool ModuleShooting::Start()
{
LOG("Loading ModuleShooting");
bool ret = true;
texture_bullet = App->textures->Load("assets/characters/marion.png");
texture_enemy_medium_bullet = App->textures->Load("assets/enemies/enemy_medium_bullet.png");
LOG("Loading FX");

return ret;
}

bool ModuleShooting::CleanUp()
{
LOG("Unloading ModuleShooting");
App->textures->Unload(texture_bullet);
App->textures->Unload(texture_enemy_medium_bullet);
texture_enemy_medium_bullet = nullptr;
texture_bullet = nullptr;
App->audio->Stop();
return true;
}

update_status ModuleShooting::Update()
{
return UPDATE_CONTINUE;
}

*/