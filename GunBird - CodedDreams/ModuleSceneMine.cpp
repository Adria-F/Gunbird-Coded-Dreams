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
#include "ModuleParticles.h"

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
	graphics_above_background_anims_text = App->textures->Load("assets/maps/above_mine_bg_anims.png");

	App->render->camera.x  = 0;
	App->render->camera.y = -3210;
	overlay_position = 0;
	turret_appeared = false;
	turret_appearing = false;

	//Set enemies
	//Flying Machine
	App->enemies->AddEnemy(FLYING_MACHINE, 224, 3230);

	//Barrel
	App->enemies->AddEnemy(BARREL, 0, 2803);

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
	App->enemies->AddEnemy(DRONE, 75, 2890, 4, 1);
	App->enemies->AddEnemy(DRONE, 25, 2890, 4, 1);
	App->enemies->AddEnemy(DRONE, 50, 2920, 4, 2);
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
	App->enemies->AddEnemy(DRONE, 75, 2690, 4, 1);
	App->enemies->AddEnemy(DRONE, 25, 2690, 4, 1);
	App->enemies->AddEnemy(DRONE, 50, 2720, 4, 2);

	//Falling Drones wave1
	App->enemies->AddEnemy(FALLING_DRONE, -60, 2450, 1, 1);
	App->enemies->AddEnemy(FALLING_DRONE, -20, 2450, 1, 1);
	App->enemies->AddEnemy(FALLING_DRONE, -40, 2490, 1, 2);
	//Falling Drones wave2
	App->enemies->AddEnemy(FALLING_DRONE, 240, 2450, 2, 1);
	App->enemies->AddEnemy(FALLING_DRONE, 200, 2450, 2, 1);
	App->enemies->AddEnemy(FALLING_DRONE, 220, 2490, 2, 2);

	//Torpedos wave1 left
	App->enemies->AddEnemy(TORPEDO, 0, 2350, 1);
	App->enemies->AddEnemy(TORPEDO, 0, 2345, 1);
	App->enemies->AddEnemy(TORPEDO, 0, 2340, 1);
	App->enemies->AddEnemy(TORPEDO, 0, 2335, 1);
	//Torpedos wave2 right
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH, 2350, 2);
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH, 2345, 2);
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH, 2340, 2);
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH, 2335, 2);

	//Tanks
	App->enemies->AddEnemy(TANK, SCREEN_WIDTH, 2930, 1);
	App->enemies->AddEnemy(TANK, SCREEN_WIDTH, 2881, 2);

	//Miners
	App->enemies->AddEnemy(MINER, 50, 3300, 1);
	App->enemies->AddEnemy(MINER, 80, 3280, 2);
	App->enemies->AddEnemy(MINER, 125, 3300, 3);
	App->enemies->AddEnemy(MINER, 140, 3380, 4);
	App->enemies->AddEnemy(MINER, 170, 3380, 4);

	//The Trump
	App->enemies->AddEnemy(TRUMP, 15, 2845, 1, 1);
	App->enemies->AddEnemy(TRUMP, 145, 2830, 1, 2);
	App->enemies->AddEnemy(TRUMP, 110, 2357, 1, 3);
	App->enemies->AddEnemy(TRUMP, 250, 2345, 2, 2);
	App->enemies->AddEnemy(TRUMP, -30, 2345, 2, 1);

	//<3
	App->enemies->AddEnemy(MEGAMAN, 180, 3395, 1);

	//Balloon
	App->enemies->AddEnemy(BALLON, 50, 3200, 1, 1);

	//General Turret Wave 1
	App->enemies->AddEnemy(GENERAL_TURRET, 49, 3050, 1, 1);
	App->enemies->AddEnemy(GENERAL_TURRET, 99, 3050, 1, 1);
	App->enemies->AddEnemy(GENERAL_TURRET, 132, 3050, 1, 2);
	App->enemies->AddEnemy(GENERAL_TURRET, 49, 3012, 1, 1);
	App->enemies->AddEnemy(GENERAL_TURRET, 99, 3012, 1, 1);
	App->enemies->AddEnemy(GENERAL_TURRET, 132, 3012, 1, 2);

	//General Turret Wave 2
	App->enemies->AddEnemy(GENERAL_TURRET, 225, 2803, 2);
	App->enemies->AddEnemy(GENERAL_TURRET, 276, 2803, 2);

	//General Turret Wave 3
	App->enemies->AddEnemy(GENERAL_TURRET, 127, 2618, 3, 2);

	//Boss Stage 1
	{
	//final result
	App->enemies->AddEnemy(CENTRALSIDE, 93, 2295);
	App->enemies->AddEnemy(RIGHTSIDE, 133, 2309);

	//Testing
	//App->enemies->AddEnemy(CENTRALSIDE, 93, 3150);
	//App->enemies->AddEnemy(RIGHTSIDE, 133, 3164);


	}

	//LEDS AND BLOWS
	{
		//LED 1
		upper_led1.PushBack({ 1, 1, 16, 5 });
		upper_led1.PushBack({ 18, 1, 16, 5 });
		upper_led1.PushBack({ 35, 1, 16, 5 });
		upper_led1.PushBack({ 52, 1, 16, 5 });
		upper_led1.PushBack({ 1, 7, 16, 5 });
		upper_led1.PushBack({ 18, 7, 16, 5 });
		upper_led1.PushBack({ 35, 7, 16, 5 });
		upper_led1.PushBack({ 52, 7, 16, 5 });
		upper_led1.speed = 0.1f;
		upper_led1.loop = true;

		//LED 2
		upper_led2.PushBack({ 3, 13, 12, 15 });
		upper_led2.PushBack({ 20, 13, 12, 15 });
		upper_led2.PushBack({ 37, 13, 12, 15 });
		upper_led2.PushBack({ 54, 13, 12, 15 });
		upper_led2.PushBack({ 3, 29, 12, 15 });
		upper_led2.PushBack({ 20, 29, 12, 15 });
		upper_led2.PushBack({ 37, 29, 12, 15 });
		upper_led2.PushBack({ 54, 29, 12, 15 });
		upper_led2.speed = 0.1f;
		upper_led2.loop = true;

		//LED 3
		upper_led3.PushBack({ 3, 45, 9, 6 });
		upper_led3.PushBack({ 13, 45, 9, 6 });
		upper_led3.PushBack({ 23, 45, 9, 6 });
		upper_led3.PushBack({ 37, 45, 9, 6 });
		upper_led3.PushBack({ 47, 45, 9, 6 });
		upper_led3.PushBack({ 57, 45, 9, 6 });
		upper_led3.PushBack({ 47, 52, 9, 6 });
		upper_led3.PushBack({ 57, 52, 9, 6 });
		upper_led3.speed = 0.1f;
		upper_led3.loop = true;

		//LED 4
		upper_led4.PushBack({ 3, 59, 13, 11 });
		upper_led4.PushBack({ 17, 59, 13, 11 });
		upper_led4.PushBack({ 31, 59, 13, 11 });
		upper_led4.PushBack({ 45, 59, 13, 11 });
		upper_led4.PushBack({ 3, 71, 13, 11 });
		upper_led4.PushBack({ 17, 71, 13, 11 });
		upper_led4.PushBack({ 31, 71, 13, 11 });
		upper_led4.PushBack({ 45, 71, 13, 11 });
		upper_led4.speed = 0.1f;
		upper_led4.loop = true;

		//BLOW1
		upper_blow1.PushBack({ 69, 1, 31, 63 });
		upper_blow1.PushBack({ 101, 1, 31, 63 });
		upper_blow1.PushBack({ 133, 1, 31, 63 });
		upper_blow1.PushBack({ 165, 1, 31, 63 });
		upper_blow1.speed = 0.2f;
		upper_blow1.loop = true;

		//BLOW 2
		upper_blow2.PushBack({ 69, 65, 25, 34 });
		upper_blow2.PushBack({ 101, 65, 25, 34 });
		upper_blow2.PushBack({ 133, 65, 25, 34 });
		upper_blow2.PushBack({ 165, 65, 25, 34 });
		upper_blow2.speed = 0.2f;
		upper_blow2.loop = true;
	}
	
	LOG("Loading music");
	App->audio->Load("assets/music/mine.ogg", App->audio->MUSIC);
	App->audio->Play(App->audio->MUSIC);

	fading = false;
	lost = false;

	App->ui->Enable();
	App->player2->Enable();
	App->player1->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->particles->Enable();

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
	if (graphics_above_background_anims_text != nullptr)
	{
		App->textures->Unload(graphics_above_background_anims_text);
		graphics_above_background_anims_text = nullptr;
	}
	
	App->audio->Stop();
	App->ui->Disable();
	App->player1->Disable();
	App->player2->Disable();
	App->collision->Disable();
	App->enemies->Disable();
	App->particles->Disable();

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
	
	App->enemies->draw_underlayed = true;
	App->enemies->Update();
	App->enemies->draw_underlayed = false;

	//Overlay map
	if (App->render->moving_scene)
		overlay_position += overlay_speed;
	App->render->Blit(graphics_above_background_text, App->render->camera.x, App->render->camera.y - 15 + overlay_position, &above_background_rect, 0.75f);
	
	//LEDS AND BLOWS
	{
		//LED 1
		App->render->Blit(graphics_above_background_anims_text, App->render->camera.x + 100, App->render->camera.y + 3436 + overlay_position, &upper_led1.GetCurrentFrame(), 0.75f);
		//LED 2
		App->render->Blit(graphics_above_background_anims_text, App->render->camera.x + 90, App->render->camera.y + 2168 + overlay_position, &upper_led2.GetCurrentFrame(), 0.75f);
		//LED 3
		App->render->Blit(graphics_above_background_anims_text, App->render->camera.x + 64, App->render->camera.y + 2077 + overlay_position, &upper_led3.GetCurrentFrame(), 0.75f);
		//LED 4
		App->render->Blit(graphics_above_background_anims_text, App->render->camera.x + 172, App->render->camera.y + 2805 + overlay_position, &upper_led4.GetCurrentFrame(), 0.75f);
		//BLOW 1
		App->render->Blit(graphics_above_background_anims_text, App->render->camera.x, App->render->camera.y + 3339 + overlay_position, &upper_blow1.GetCurrentFrame(), 0.75f);
		//BLOW 2
		App->render->Blit(graphics_above_background_anims_text, App->render->camera.x, App->render->camera.y + 2165 + overlay_position, &upper_blow2.GetCurrentFrame(), 0.75f);
	}

	//Fade to black
	if (App->player1->IsEnabled() == false && App->player2->IsEnabled() == false)
		lost = true;

	if (App->render->camera.y >= -2000 && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->highscores, 0.5f);
		fading = true;
	}
	
	if (((App->input->keyboard[SDL_SCANCODE_SPACE] || App->input->controller[SDL_CONTROLLER_BUTTON_Y] == PAD_BUTON_STATE::BUTTON_DOWN) && fading == false && App->fade->GetFadeState() == false) && App->render->debugging)
	{
		App->fade->FadeToBlack(this, App->highscores, 0.5f);
		fading = true;
	}

	return UPDATE_CONTINUE;
}