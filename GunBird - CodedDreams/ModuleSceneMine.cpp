#include "Globals.h"
#include "Application.h"
#include "ModuleSceneMine.h"
#include "ModuleWelcomeTitle.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleHighscores.h"
#include "ModuleUI.h"

// Reference at updated to a youtube video from gunbird
// https://youtu.be/HDC6PZxGwL4?t=3m17s

ModuleSceneMine::ModuleSceneMine()
{
	// Background
	background_rect.w = SCREEN_WIDTH;
	background_rect.h = 3535;

	// Above background
	above_background_rect.w = SCREEN_WIDTH;
	above_background_rect.h = 3535;
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
	overlay_position = 0;

	//Set enemies
	App->enemies->AddEnemy(BALLON, 150, 3000);
	App->enemies->AddEnemy(FLYING_MACHINE, 224, 3200);
	//Drones wave1->Done
	App->enemies->AddEnemy(DRONE, -50, 3020+70, 1, 1);
	App->enemies->AddEnemy(DRONE,   0, 3020+70, 1, 1);
	App->enemies->AddEnemy(DRONE, -25, 3040+70, 1, 2);
	//Drones wave2->Done
	App->enemies->AddEnemy(DRONE, 175, 2980 + 70, 2, 1);
	App->enemies->AddEnemy(DRONE, 125, 2980 + 70, 2, 1);
	App->enemies->AddEnemy(DRONE, 150, 3010 + 70, 2, 2);
	//Drones wave3
	App->enemies->AddEnemy(DRONE, 280, 2950, 3, 1);
	App->enemies->AddEnemy(DRONE, 230, 2950, 3, 1);
	App->enemies->AddEnemy(DRONE, 255, 2980, 3, 2);
	//Drones wave4
	App->enemies->AddEnemy(DRONE, 75, 2890, 2, 1);
	App->enemies->AddEnemy(DRONE, 25, 2890, 2, 1);
	App->enemies->AddEnemy(DRONE, 50, 2920, 2, 2);
	//Drones wave5
	App->enemies->AddEnemy(DRONE, -50, 2800, 1, 1);
	App->enemies->AddEnemy(DRONE,   0, 2800, 1, 1);
	App->enemies->AddEnemy(DRONE, -25, 2820, 1, 2);
	//Drones wave6
	App->enemies->AddEnemy(DRONE, 175, 2760, 2, 1);
	App->enemies->AddEnemy(DRONE, 125, 2760, 2, 1);
	App->enemies->AddEnemy(DRONE, 150, 2790, 2, 2);
	//Drones wave7
	App->enemies->AddEnemy(DRONE, 280, 2750, 3, 1);
	App->enemies->AddEnemy(DRONE, 230, 2750, 3, 1);
	App->enemies->AddEnemy(DRONE, 255, 2780, 3, 2);
	//Drones wave8
	App->enemies->AddEnemy(DRONE, 75, 2690, 2, 1);
	App->enemies->AddEnemy(DRONE, 25, 2690, 2, 1);
	App->enemies->AddEnemy(DRONE, 50, 2720, 2, 2);

	//Falling Drones wave1

	App->enemies->AddEnemy(FALLING_DRONE, -60, 3200, 1, 1);
	App->enemies->AddEnemy(FALLING_DRONE, -30, 3230, 1, 1);
	App->enemies->AddEnemy(FALLING_DRONE, -60, 3260, 1, 1);


	//Torpedos wave1
	App->enemies->AddEnemy(TORPEDO, 0, 2149, 1);

	//My name is Jeff
	App->enemies->AddEnemy(MINER, 50, 3300, 1);
	App->enemies->AddEnemy(MINER, 80, 3280, 2);
	App->enemies->AddEnemy(MINER, 125, 3300, 3);
	App->enemies->AddEnemy(MINER, 140, 3380, 4);
	App->enemies->AddEnemy(MINER, 170, 3380, 4);

	//The Trump
	App->enemies->AddEnemy(TRUMP, 15, 2845, 1, 1);

	
	LOG("Loading music");
	App->audio->Load("assets/music/mine.ogg", App->audio->MUSIC);
	App->audio->Play(App->audio->MUSIC);

	fading = false;
	lost = false;

	App->ui->Enable();
	App->player2->Enable();
	App->player1->Enable();
	App->collision->Enable();

	return ret;
}

// Load assets
bool ModuleSceneMine::CleanUp()
{
	LOG("Unloading Mine scene");
	if (graphics_above_background_text != nullptr)
	{
		App->textures->Unload(graphics_above_background_text);
		graphics_above_background_text = nullptr;
	}
	if (graphics_background_text != nullptr)
	{
		App->textures->Unload(graphics_background_text);
		graphics_background_text = nullptr;
	}
	
	App->audio->Stop();
	App->ui->Disable();
	App->player1->Disable();
	App->player2->Disable();
	App->collision->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneMine::Update()
{
	if (lost)
	{
		App->render->moving_scene = false;
		if ((App->input->keyboard[SDL_SCANCODE_SPACE] || App->input->controller[SDL_CONTROLLER_BUTTON_Y] == PAD_BUTON_STATE::BUTTON_DOWN) && fading == false && App->fade->GetFadeState() == false)
		{
			App->fade->FadeToBlack(this, App->highscores, 0.5f);
			fading = true;
		}
	}
	
	// Draw everything --------------------------------------	
	App->render->Blit(graphics_background_text, App->render->camera.x, App->render->camera.y, &background_rect, 0.75f); // back of the room
	if (App->render->moving_scene)
		overlay_position += overlay_speed;
	App->render->Blit(graphics_above_background_text, App->render->camera.x, App->render->camera.y - 15 + overlay_position, &above_background_rect, 0.75f);
	
	//Fade to black
	if (App->player1->IsEnabled() == false && App->player2->IsEnabled() == false)
		lost = true;

	if ((App->input->keyboard[SDL_SCANCODE_SPACE] || App->input->controller[SDL_CONTROLLER_BUTTON_Y] == PAD_BUTON_STATE::BUTTON_DOWN) && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->highscores, 0.5f);
		fading = true;
	}

	return UPDATE_CONTINUE;
}