#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneCastle.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
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
	anim_bridge.PushBack({ 125, 320, 117, 110 });
	anim_bridge.PushBack({ 250, 322, 117, 110 });
	anim_bridge.speed = 0.03f;

	//knight
	anim_knight.PushBack({ 0, 0, 15, 24 }); //up
	anim_knight.PushBack({ 20, 0, 14, 24 }); //up
	anim_knight.PushBack({ 39, 0, 14, 24 }); //up
	anim_knight.PushBack({ 59, 0, 14, 24 }); //up

	anim_knight.speed = 0.03f;
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
	texture_knight = App->textures->Load("assets/maps/Castle Knights.png"); //knights

	App->enemies->AddEnemy(ANTIAIRCRAFT, 162, 1596);
	App->enemies->AddEnemy(HUMANOIDE_ROBOT, 70, 1472);

	//first wave torpedos:
	App->enemies->AddEnemy(TORPEDO, -45, 1400);
	App->enemies->AddEnemy(TORPEDO, -45, 1390);
	App->enemies->AddEnemy(TORPEDO, -45, 1380);
	App->enemies->AddEnemy(TORPEDO, -45, 1370);

	//buildings
	App->enemies->AddEnemy(BUILDING1, 145, 1415);
	App->enemies->AddEnemy(BUILDING2, 75, 1165);

	//second wave torpedos:
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 990, 2, 1);
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 990, 2, 2); 
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 990, 2, 3);
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 990, 2, 4);
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 990, 2, 5);
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 990, 2, 6);
	App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 990, 2, 7);

	//third wave torpedos
/*
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
*/
    //third wave torpedos 2.0
/*
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
App->enemies->AddEnemy(TORPEDO, SCREEN_WIDTH + 45, 1200, 2);
*/
	//PUT OTHER ENEMIES UNDER THE LAST ENEMY!!


	App->render->moving_scene = true;
	App->render->camera.x = 0;
	App->render->camera.y = -1782;

	LOG("Loading Music");
	App->audio->Load("assets/music/castle-welcome_title.ogg", App->audio->MUSIC);
	App->audio->Play(App->audio->MUSIC);

	App->player->Enable();
	App->player2->Enable();
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
	App->textures->Unload(texture_knight);

	texture_bg = nullptr;
	texture_bg_upper = nullptr;
	texture_1_river = nullptr;
	texture_2_river = nullptr;
	texture_bridge = nullptr;
	texture_knight = nullptr;

	App->audio->Stop();
	App->player->Disable();
	App->player2->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->enemies->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneCastle::Update()
{
	// Draw everything --------------------------------------
	//background
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

	//bridge	
	Animation* current_bridge_animation = &anim_bridge;
	SDL_Rect rect_bridge = current_bridge_animation->GetCurrentFrame();
	App->render->Blit(texture_bridge, (App->render->camera.x + 65), (App->render->camera.y + 1346), &rect_bridge);

	//knights
	Animation* current_knight_animation = &anim_knight;
	SDL_Rect rect_knight = current_knight_animation->GetCurrentFrame();
	App->render->Blit(texture_knight, (App->render->camera.x + 50), (App->render->camera.y + 1750), &rect_knight);

	//Fade To Black ---------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->highscores, 0.5f);
		fading = true;
	}

	return UPDATE_CONTINUE;
}


void ModuleSceneCastle::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_BUILDING)
	{
		if (c2 == coll_build1)
		{
		/*
		Animation* current_animation5 = &anim_build1down;
		rect_building1 = current_animation5->GetCurrentFrame();
		App->render->Blit(texture_buildings, (App->render->camera.x + 145), (App->render->camera.y + 1415), &rect_building1);//render
		coll_build1->SetPos((App->render->camera.x + 145), (App->render->camera.y + 1415));
		*/
		
		}
	}
}

