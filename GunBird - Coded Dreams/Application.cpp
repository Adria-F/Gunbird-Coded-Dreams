#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneCastle.h"
#include "ModuleSceneMine.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleWelcomeTitle.h"
#include "ModuleHighscores.h"
#include "ModuleSelection.h"
#include "ModuleDebugMode.h"
#include "ModuleShooting.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"

Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = scene_mine = new ModuleSceneMine();
	modules[i++] = scene_castle = new ModuleSceneCastle();
	modules[i++] = welcometitle = new ModuleWelcomeTitle();
	modules[i++] = highscores = new ModuleHighscores();
	modules[i++] = selection = new ModuleSelection();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = audio = new ModuleAudio();
	modules[i++] = debug = new ModuleDebugMode();
	modules[i++] = shooting = new ModuleShooting();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = fade = new ModuleFadeToBlack();
}

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Player will be enabled on the first update of a new scene
	player->Disable();
	// Disable the map that you do not start with
	scene_castle->Disable();
	highscores->Disable();
	scene_mine->Disable();
	selection->Disable();
	debug->Disable();
	collision->Disable();

	/*
	//testing the shooting mechanic
	welcometitle->Disable();
	scene_mine->Enable();
	*/

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}