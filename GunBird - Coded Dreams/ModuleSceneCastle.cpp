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

	/*//General Turret
	anim_gturret.PushBack({ 0, 0, 32, 32 });
	anim_gturret.PushBack({ 34, 0, 32,32 });
	anim_gturret.PushBack({ 68, 0, 32, 32 });
	anim_gturret.PushBack({ 102, 0, 32, 32 });
	anim_gturret.speed = 0.1f;*/

	//Build1
	/*
	anim_build1.PushBack({ 0, 0, 64, 86 });
	anim_build1.speed = 0.1f;
	anim_flag1.PushBack({ 13, 95, 69, 23 });
	anim_flag1.PushBack({ 13, 121, 69, 23 });
	anim_flag1.PushBack({ 13, 146, 69, 23 });
	anim_flag1.PushBack({ 13, 171, 69, 23 });
	anim_flag1.PushBack({ 13, 196, 69, 23 });
	anim_flag1.PushBack({ 88, 98, 69, 23 });
	anim_flag1.PushBack({ 89, 127, 65, 21 });
	anim_flag1.PushBack({ 89, 154, 65, 21 });
	anim_flag1.speed = 0.07f;
	*/
	



	//Build2
	/*
	anim_build2.PushBack({ 69, 0, 72, 83 });
	anim_build2.speed = 0.1f;
	anim_flag2.PushBack({ 13, 95, 69, 23 });
	anim_flag2.PushBack({ 13, 121, 69, 23 });
	anim_flag2.PushBack({ 13, 146, 69, 23 });
	anim_flag2.PushBack({ 13, 171, 69, 23 });
	anim_flag2.PushBack({ 13, 196, 69, 23 });
	anim_flag2.PushBack({ 88, 98, 69, 23 });
	anim_flag2.PushBack({ 89, 127, 65, 21 });
	anim_flag2.PushBack({ 89, 154, 65, 21 });
	anim_flag2.speed = 0.07f;
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
	texture_bg = App->textures->Load("assets/maps/castle_background.png");

	//Bridge
	texture_bridge = App->textures->Load("assets/maps/castle_bridge.png");

	App->enemies->AddEnemy(ANTIAIRCRAFT, 162, 1596);
	App->enemies->AddEnemy(HUMANOIDE_ROBOT, 70, 1505);
	App->enemies->AddEnemy(TORPEDO, -45, 1435);
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
	App->textures->Unload(texture_bridge);

	texture_bg = nullptr;
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
	Animation* current_animation = &anim_bridge;
	SDL_Rect rect_bridge = current_animation->GetCurrentFrame();
	App->render->Blit(texture_bridge, (App->render->camera.x + 65), (App->render->camera.y + 1346), &rect_bridge);

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