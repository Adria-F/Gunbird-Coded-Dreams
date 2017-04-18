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
	


	//Build 1 destroyed
	anim_build1down.PushBack({ 92, 186, 61, 52 });
	anim_build1down.speed = 0.1f;

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

	/*//gturret
	texture_gturret = App->textures->Load("assets/enemies/General_Torpedo _ Castle mortar.png");
	coll_gturret = App->collision->AddCollider({ 0, 0, 32, 32 }, COLLIDER_DROPPING_ENEMY, this);*/

	/*//building1
	texture_buildings = App->textures->Load("assets/maps/Castle_Sprites.png");
	coll_build1 = App->collision->AddCollider({ 0, 0, 64, 86 }, COLLIDER_BUILDING, this);*/
	App->enemies->AddEnemy(ANTIAIRCRAFT, 162, 1596);
	App->enemies->AddEnemy(HUMANOIDE_ROBOT, 70, 1505);
	App->enemies->AddEnemy(BUILDING1, 145, 1415);
	App->enemies->AddEnemy(FLAG1, 175, 1403);
	App->enemies->AddEnemy(BUILDING2, 75, 1165);
	App->enemies->AddEnemy(FLAG2, 109, 1155);
	
	//building2
	//coll_build2 = App->collision->AddCollider({ 69, 0, 72, 83 }, COLLIDER_BUILDING, this);

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
	App->textures->Unload(texture_gturret);
	App->textures->Unload(texture_buildings);

	texture_bg = nullptr;
	texture_gturret = nullptr;
	texture_buildings = nullptr;

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
	App->render->Blit(texture_bg, App->render->camera.x, App->render->camera.y, &rect_background, 0.75f); // sea and sky

	/*//general turret
	Animation* current_animation = &anim_gturret;
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(texture_gturret, (App->render->camera.x + 162), (App->render->camera.y + 1596), &r);
	coll_gturret->SetPos((App->render->camera.x + 162), (App->render->camera.y + 1596));*/

	//building 1
	/*
	Animation* current_animation1 = &anim_build1;
	rect_building1 = current_animation1->GetCurrentFrame();
	App->render->Blit(texture_buildings, (App->render->camera.x + 145), (App->render->camera.y + 1415), &rect_building1);//render
	coll_build1->SetPos((App->render->camera.x + 145), (App->render->camera.y + 1415));//collider
	Animation* current_animation2 = &anim_flag1;
	rect_flag1 = current_animation2->GetCurrentFrame();
	App->render->Blit(texture_buildings, (App->render->camera.x + 175), (App->render->camera.y + 1403), &rect_flag1);//render
	*/
	/*
		//building 2
	Animation* current_animation3 = &anim_build2;
	rect_building2 = current_animation3->GetCurrentFrame();
	App->render->Blit(texture_buildings, (App->render->camera.x + 75), (App->render->camera.y + 1165), &rect_building2);//render
	coll_build2->SetPos((App->render->camera.x + 75), (App->render->camera.y + 1165));//collider

	Animation* current_animation4 = &anim_flag2;
	rect_flag2 = current_animation4->GetCurrentFrame();
	App->render->Blit(texture_buildings, (App->render->camera.x + 109), (App->render->camera.y + 1155), &rect_flag2);//render
	*/
	




	//Fade To Black ---------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->highscores);
		fading = true;
	}
	/*OnCollision(player shot, building)
	{	Animation* current_animation5 = &build1down;
			rec_building1 = current_animation5->GetCurrentFrame();
			App->render->Blit(graphics_buildings, (App->render->camera.x + 145), (App->render->camera.y + 1415), &rec_building1);//render
			rect_build1->SetPos((App->render->camera.x + 145), (App->render->camera.y + 1415))
	}
	*/

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