#include "Application.h"
#include "ModuleDebugMode.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include <iostream>
using namespace std;

ModuleDebugMode::ModuleDebugMode()
{
	notifier.w = 147;
	notifier.h = 31;
}

ModuleDebugMode::~ModuleDebugMode()
{

}

bool ModuleDebugMode::Start()
{
	LOG("Opened Debug Mode");
	debugging_on = App->textures->Load("assets/UI/debugging_on.png");

	debugging = true;
	
	return debugging;
}

bool ModuleDebugMode::CleanUp()
{
	LOG("Closed Debug Mode");
	App->textures->Unload(debugging_on);
	App->render->camera.x = 0;
	if (App->render->moving_scene == false)
	{
		App->render->camera.y = 0;
	}
	else
	{
		if (App->render->camera.y > 0)
		{
			App->render->camera.y = 0;
		}
		else if (App->render->camera.y < -2895)
		{
			App->render->camera.y = -2895;
		}
	}

	debugging = false;
	
	return true;
}

update_status ModuleDebugMode::Update()
{
	App->render->Blit(debugging_on, 0, 0, &notifier);
	
	return UPDATE_CONTINUE;
}