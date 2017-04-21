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

	//First river
	anim_1_river.PushBack({ 0, 0, 224, 120});
	anim_1_river.PushBack({ 224, 0, 224, 120 });
	anim_1_river.PushBack({ 0, 120, 224, 120 });
	anim_1_river.PushBack({ 224, 120, 224, 120 });
	anim_1_river.speed = 0.07f;

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
}

ModuleSceneCastle::~ModuleSceneCastle()
{}

// Load assets
bool ModuleSceneCastle::Start()
{
	LOG("Loading castle scene");
	LOG("Loading background assets");
	bool ret = true;
	texture_bg = App->textures->Load("assets/maps/castle_background.png");
	//First river
	texture_1_river = App->textures->Load("assets/maps/castle_first_river.png");
	//Bridge
	texture_bridge = App->textures->Load("assets/maps/castle_bridge.png");

	App->enemies->AddEnemy(ANTIAIRCRAFT, 162, 1596);
	App->enemies->AddEnemy(HUMANOIDE_ROBOT, 70, 1505);
	//first round torpedos:
	App->enemies->AddEnemy(TORPEDO, -45, 1400);
	App->enemies->AddEnemy(TORPEDO, -45, 1390);
	App->enemies->AddEnemy(TORPEDO, -45, 1380);
	App->enemies->AddEnemy(TORPEDO, -45, 1370);

	App->enemies->AddEnemy(BUILDING1, 145, 1415);
	App->enemies->AddEnemy(BUILDING2, 75, 1165);

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
	App->textures->Unload(texture_1_river);
	App->textures->Unload(texture_bridge);

	texture_bg = nullptr;
	texture_1_river = nullptr;
	texture_bridge = nullptr;

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

	//bridge	
	Animation* current_bridge_animation = &anim_bridge;
	SDL_Rect rect_bridge = current_bridge_animation->GetCurrentFrame();
	App->render->Blit(texture_bridge, (App->render->camera.x + 65), (App->render->camera.y + 1346), &rect_bridge);

	// First river
	Animation* current_1_river_animation = &anim_1_river;
	SDL_Rect rect_1_river = current_1_river_animation->GetCurrentFrame();
	App->render->Blit(texture_1_river, (App->render->camera.x + 2), (App->render->camera.y + 1714), &rect_1_river, 0.75f);

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
			Animation* current_animation5 = &anim_build1down;
			rect_building1 = current_animation5->GetCurrentFrame();
			App->render->Blit(texture_buildings, (App->render->camera.x + 145), (App->render->camera.y + 1415), &rect_building1);//render
			coll_build1->SetPos((App->render->camera.x + 145), (App->render->camera.y + 1415));
		}
	}
}