#include "ModulePowerUp.h"
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

ModulePowerUp::ModulePowerUp()
{
}

ModulePowerUp::~ModulePowerUp()
{
}

bool ModulePowerUp::Start()
{
	LOG("Loading Power Up textures");
	//-----------------Upgrade Texture------------------

	return true;
}

bool ModulePowerUp::CleanUp()
{
	
	return true;
}

update_status ModulePowerUp::Update()
{
	return UPDATE_CONTINUE;
}

void ModulePowerUp::AddPowerUp(powerup_type type, int x, int y)
{
	App->particles->upgrade.speed.x = 0;
	App->particles->upgrade.speed.y = 0;
	App->particles->AddParticle(App->particles->upgrade, particle_type::P_UPGRADE, x, y, COLLIDER_POWER_UP);
}

void ModulePowerUp::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->callback == App->player)
	{
		App->audio->Load("assets/music/upgrade_marion.wav", App->audio->EFFECT);
		App->audio->Play(App->audio->EFFECT);
		App->particles->OnCollision(c1, c2);
	}
}