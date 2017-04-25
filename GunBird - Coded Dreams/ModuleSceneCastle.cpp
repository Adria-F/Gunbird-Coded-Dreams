#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneCastle.h"
#include "ModuleMarion.h"
#include "ModuleAsh.h"
#include "ModuleSceneMine.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleWelcomeTitle.h"
#include "ModuleHighscores.h"
#include "ModuleCollision.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleDebugMode.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneCastle::ModuleSceneCastle()
{
	// Background
	rect_background.w = SCREEN_WIDTH;
	rect_background.h = 2108;

	//Upper background
	rect_background_upper.w = SCREEN_WIDTH;
	rect_background_upper.h = 2108;
	
	//First river
	anim_1_river.PushBack({ 0, 0, 224, 120});
	anim_1_river.PushBack({ 224, 0, 224, 120 });
	anim_1_river.PushBack({ 0, 120, 224, 120 });
	anim_1_river.PushBack({ 224, 120, 224, 120 });
	anim_1_river.speed = 0.07f;

	//Second river
	anim_2_river.PushBack({ 0, 0, 224, 256 });
	anim_2_river.PushBack({ 224, 0, 224, 256 });
	anim_2_river.PushBack({ 448, 0, 224, 256 });
	anim_2_river.PushBack({ 672, 0, 224, 256 });
	anim_2_river.speed = 0.07f;
	
	//Bridge
	anim_bridge.PushBack({ 0, 0, 121, 35});
	anim_bridge.PushBack({ 125, 0, 116, 35 });
	anim_bridge.PushBack({ 250, 0, 119 , 35 });
	anim_bridge.PushBack({ 0, 65 , 121, 72 });
	anim_bridge.PushBack({ 125, 65 , 121, 72 });
	anim_bridge.PushBack({ 0, 205 , 110, 106 });
	anim_bridge.PushBack({ 0, 320, 117, 110 });
	anim_bridge.PushBack({ 125, 325, 117, 110 });
	anim_bridge.speed = 0.1f;

	last_bridge.PushBack({ 241,250,117,165 });
}

ModuleSceneCastle::~ModuleSceneCastle()
{}

// Load assets
bool ModuleSceneCastle::Start()
{
	LOG("Loading castle scene");
	LOG("Loading background assets");
	bool ret = true;
	texture_bg = App->textures->Load("assets/maps/castle_bg.png");
	texture_bg_upper = App->textures->Load("assets/maps/castle_bg_upper.png");
	texture_1_river = App->textures->Load("assets/maps/castle_first_river.png"); //First river
	texture_2_river = App->textures->Load("assets/maps/castle_second_river.png"); //Second river
	texture_bridge = App->textures->Load("assets/maps/castle_bridge.png"); //Bridge
	texture_the_trump = App->textures->Load("assets/maps/castle_the_trump.png");


	//pot
	App->enemies->AddEnemy(POT, 8, 840 );
	App->enemies->AddEnemy(POT, 185, 840);
	App->enemies->AddEnemy(POT, 8, 1058);
	App->enemies->AddEnemy(POT, 185, 1058);

	App->enemies->AddEnemy(ANTIAIRCRAFT, 162, 1597);
	App->enemies->AddEnemy(HUMANOIDE_ROBOT, 70, 1472);

	//knights
	//wave1
	App->enemies->AddEnemy(KNIGHTS, 80, 1910);
	App->enemies->AddEnemy(KNIGHTS, 65, 1890);

	//wave 2
	App->enemies->AddEnemy(KNIGHTS, 80, 1820, 2);
	App->enemies->AddEnemy(KNIGHTS, 95, 1800, 2);

	//wave 3
	App->enemies->AddEnemy(KNIGHTS, 160, 1590, 1, 1);
	App->enemies->AddEnemy(KNIGHTS, 140, 1590, 1, 1);
	App->enemies->AddEnemy(KNIGHTS, 120, 1590, 1, 1);

	//The_Trump pilot:
	App->enemies->AddEnemy(THE_TRUMP, 73, 850, 1, 1);

	//The_Trump 1st boy then girl:
	App->enemies->AddEnemy(THE_TRUMP, 5, 719, 2, 2);
	App->enemies->AddEnemy(THE_TRUMP, 12, 703, 3, 2);


	//first wave torpedos:
	App->enemies->AddEnemy(TORPEDO, -45, 1400);
	App->enemies->AddEnemy(TORPEDO, -45, 1390);
	App->enemies->AddEnemy(TORPEDO, -45, 1380);
	App->enemies->AddEnemy(TORPEDO, -45, 1370);

	//buildings
	App->enemies->AddEnemy(BUILDING1, 145, 1415);
	App->enemies->AddEnemy(BUILDING2, 75, 1165);

	//second wave torpedos:
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1015, 2, 1);
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1015, 2, 2); 
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1015, 2, 3);
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1015, 2, 4);
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1015, 2, 5);
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1015, 2, 6);
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1015, 2, 7);

	//third wave torpedos:
	App->enemies->AddEnemy(TORPEDO, 75, 550, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 123, 550, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 5, 540, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 53, 540, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 149, 540, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 197, 540, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 5, 530, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 53, 530, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 149, 530, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 197, 530, 3, 2);
	App->enemies->AddEnemy(TORPEDO, 75, 520, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 123, 520, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 99, 515, 3, 2);

    //third wave torpedos 2.0
	App->enemies->AddEnemy(TORPEDO, 75, 455, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 123, 455, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 5, 445, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 53, 445, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 149, 445, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 197, 445, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 5, 435, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 53, 435, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 149, 435, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 197, 435, 3, 3);
	App->enemies->AddEnemy(TORPEDO, 75, 425, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 123, 425, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 99, 420, 3, 3);

	App->render->moving_scene = true;
	App->render->camera.x = 0;
	App->render->camera.y = -1782;

	LOG("Loading Music");
	App->audio->Load("assets/music/castle-welcome_title.ogg", App->audio->MUSIC);
	App->audio->Play(App->audio->MUSIC);

	App->marion->Enable();
	App->ash->Enable();
	App->collision->Enable();
	App->particles->Enable();
	App->enemies->Enable();
	

	fading = false;

	return ret;
}

// UnLoad assets
bool ModuleSceneCastle::CleanUp()
{
	LOG("Unloading Castle scene");
	App->textures->Unload(texture_bg);
	App->textures->Unload(texture_bg_upper);
	App->textures->Unload(texture_1_river);
	App->textures->Unload(texture_2_river);
	App->textures->Unload(texture_bridge);
	App->textures->Unload(texture_the_trump);
	
	texture_bg = nullptr;
	texture_bg_upper = nullptr;
	texture_1_river = nullptr;
	texture_2_river = nullptr;
	texture_bridge = nullptr;
	texture_the_trump = nullptr;

	App->audio->Stop();
	App->marion->Disable();
	App->ash->Disable();
	App->particles->Disable();
	App->enemies->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneCastle::Update()
{
	if (lost)
	{
		App->render->moving_scene = false;
		if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
		{
			App->render->print_screen = true;
			App->fade->FadeToBlack(this, App->highscores, 0.5f);
			fading = true;
		}
	}
	
	// Draw everything --------------------------------------
	//background
	if (App->render->camera.y >= -357)
	{
		App->fade->FadeToBlack(this, App->highscores, 0.5f);
		fading = true;
	}

 	App->render->Blit(texture_bg, App->render->camera.x, App->render->camera.y, &rect_background, 0.75f);

	// First river
	Animation* current_1_river_animation = &anim_1_river;
	SDL_Rect rect_1_river = current_1_river_animation->GetCurrentFrame();
	App->render->Blit(texture_1_river, (App->render->camera.x + 1), (App->render->camera.y + 1714), &rect_1_river, 0.75f);

	// Second river
	Animation* current_2_river_animation = &anim_2_river;
	SDL_Rect rect_2_river = current_2_river_animation->GetCurrentFrame();
	App->render->Blit(texture_2_river, (App->render->camera.x + 1), (App->render->camera.y + 1341), &rect_2_river, 0.75f);

	App->render->Blit(texture_bg_upper, App->render->camera.x, App->render->camera.y, &rect_background_upper, 0.75f);
	
	//Bridge

	Animation* current_bridge_animation = &anim_bridge;
	Animation* last_bridge_frame = &last_bridge;
	SDL_Rect rect_bridge = current_bridge_animation->GetCurrentFrame();
	SDL_Rect last_bridge = last_bridge_frame->GetCurrentFrame();

	if (-1325 > App->render->camera.y && App->render->camera.y > -1340) {
		
		App->render->Blit(texture_bridge, (App->render->camera.x + 65), (App->render->camera.y + 1340), &rect_bridge);
	}
	if (App->render->camera.y > -1325) {
		App->render->Blit(texture_bridge, (App->render->camera.x + 54), (App->render->camera.y + 1263), &last_bridge);
	};

	//Fade To Black ---------------------------------------------
	if (App->marion->IsEnabled() == false && App->ash->IsEnabled() == false)
		lost = true;

	if (App->debug->debugging && App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->highscores, 0.5f);
		fading = true;
	}
	if (App->debug->debugging && App->input->keyboard[SDL_SCANCODE_BACKSPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		lost = true;
	}
	
	return UPDATE_CONTINUE;
}