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
	//anim_bridge.PushBack({ 241, 250, 117, 165 });
	anim_bridge.speed = 0.02f;

	last_bridge.PushBack({ 241,250,117,165 });

	

	pot_anim.PushBack({ 342, 202, 36, 53 });

	
	/*
	//knight
	//up
	anim_knight_up.PushBack({ 0, 0, 15, 24 });
	anim_knight_up.PushBack({ 20, 0, 14, 24 });
	anim_knight_up.PushBack({ 39, 0, 14, 24 });
	anim_knight_up.PushBack({ 59, 0, 14, 24 });
	anim_knight_up.speed = 0.1f;

	//left
	anim_knight_left.PushBack({ 0, 28, 11, 25 }); //1
	anim_knight_left.PushBack({ 16, 29, 12, 24 }); //2
	anim_knight_left.PushBack({ 33, 28, 11, 25 }); //3
	anim_knight_left.PushBack({ 49, 29, 11, 24 }); //4
	anim_knight_left.speed = 0.1f;
	*/


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
	texture_pot = App->textures->Load("assets/maps/pot.png");

	//pot
	App->enemies->AddEnemy(POT, 8, 840 );

	App->enemies->AddEnemy(ANTIAIRCRAFT, 162, 1596);
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
	App->enemies->AddEnemy(TORPEDO, 5, 535, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 53, 535, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 149, 535, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 197, 535, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 5, 520, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 53, 520, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 149, 520, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 197, 520, 3, 2);
	App->enemies->AddEnemy(TORPEDO, 75, 505, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 123, 505, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 99, 500, 3, 2);

    //third wave torpedos 2.0
	App->enemies->AddEnemy(TORPEDO, 75, 455, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 123, 455, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 5, 440, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 53, 440, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 149, 440, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 197, 440, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 5, 425, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 53, 425, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 149, 425, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 197, 425, 3, 3);
	App->enemies->AddEnemy(TORPEDO, 75, 410, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 123, 410, 3, 1);
	App->enemies->AddEnemy(TORPEDO, 99, 405, 3, 3);




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
	
	texture_bg = nullptr;
	texture_bg_upper = nullptr;
	texture_1_river = nullptr;
	texture_2_river = nullptr;
	texture_bridge = nullptr;

	App->audio->Stop();
	App->marion->Disable();
	App->ash->Disable();
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
	
	//Bridge

	Animation* current_bridge_animation = &anim_bridge;
	Animation* last_bridge_frame = &last_bridge;
	SDL_Rect rect_bridge = current_bridge_animation->GetCurrentFrame();
	SDL_Rect last_bridge = last_bridge_frame->GetCurrentFrame();

	if (-1266 > App->render->camera.y && App->render->camera.y > -1347) {
		App->render->Blit(texture_bridge, (App->render->camera.x + 65), (App->render->camera.y + 1347), &rect_bridge);
	}

	if (App->render->camera.y > -1266) {
		App->render->Blit(texture_bridge, (App->render->camera.x + 52), (App->render->camera.y + 1266), &last_bridge);
	};

	//Fade To Black ---------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->highscores, 0.5f);
		fading = true;
	}

	//pot

	Animation* pot_animation = &pot_anim;

	SDL_Rect rect_pot = pot_animation->GetCurrentFrame();

	App->render->Blit(texture_pot, (App->render->camera.x + 8), (App->render->camera.y + 840), &rect_pot);

	
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

