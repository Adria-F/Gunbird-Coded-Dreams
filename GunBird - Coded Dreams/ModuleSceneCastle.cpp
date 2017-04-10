#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneCastle.h"
#include "ModulePlayer.h"
#include "ModuleSceneMine.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleWelcomeTitle.h"
#include "ModuleHighscores.h"
#include "ModuleCollision.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneCastle::ModuleSceneCastle()
{
	// Background
	background.w = SCREEN_WIDTH;
	background.h = 2108;

	// General Turret
	gturret.PushBack({ 0, 0, 32, 32 });
	gturret.PushBack({ 34, 0, 32,32 });
	gturret.PushBack({ 68, 0, 32, 32 });
	gturret.PushBack({ 102, 0, 32, 32 });
	gturret.speed = 0.1f;

	// Build1
	build1.PushBack({ 0, 0, 64, 86 });
	build1.PushBack({ 0, 0, 64, 86 });
	build1.speed = 0.1f;
	flag1.PushBack({ 13, 95, 69, 23 });
	flag1.PushBack({ 13, 121, 69, 23 });
	flag1.PushBack({ 13, 146, 69, 23 });
	flag1.PushBack({ 13, 171, 69, 23 });
	flag1.PushBack({ 13, 196, 69, 23 });
	flag1.PushBack({ 88, 98, 69, 23 });
	flag1.PushBack({ 89, 127, 65, 21 });
	flag1.PushBack({ 89, 154, 65, 21 });

	flag1.speed = 0.4f;
	
}

ModuleSceneCastle::~ModuleSceneCastle()
{}

// Load assets
bool ModuleSceneCastle::Start()
{
	LOG("Loading castle scene");
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("assets/maps/castle_background.png");

	//gturret
	graphics_gturret = App->textures->Load("assets/enemies/General_Torpedo _ Castle mortar.png");
	rect_gturret = App->collision->AddCollider({ 0, 0, 32, 32 }, COLLIDER_ENEMY, this);

	//building1
	graphics_build1 = App->textures->Load("assets/maps/Castle_Sprites.png");
	rect_build1 = App->collision->AddCollider({ 0, 0, 64, 86 }, COLLIDER_ENEMY, this);

	App->render->moving_scene = true;
	App->render->camera.x = 0;
	App->render->camera.y = -1782;

	LOG("Loading Music");
	App->audio->Load("assets/music/castle-welcome_title.ogg", App->audio->MUSIC);
	App->audio->Play(App->audio->MUSIC);

	App->player->Enable();
	App->collision->Enable();
	App->particles->Enable();
	fading = false;

	return ret;
}

// UnLoad assets
bool ModuleSceneCastle::CleanUp()
{
	LOG("Unloading Castle scene");
	App->textures->Unload(graphics);
	App->textures->Unload(graphics_gturret);
	App->textures->Unload(graphics_build1);

	graphics = nullptr;
	graphics_gturret = nullptr;
	graphics_build1 = nullptr;

	App->audio->Stop();
	App->player->Disable();
	App->collision->Disable();
	App->particles->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneCastle::Update()
{
	// Draw everything --------------------------------------
	//background
	App->render->Blit(graphics, App->render->camera.x, App->render->camera.y, &background, 0.75f); // sea and sky

	//general turret
	Animation* current_animation = &gturret;
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics_gturret, (App->render->camera.x + 162), (App->render->camera.y + 1596), &r);
	rect_gturret->SetPos((App->render->camera.x + 162), (App->render->camera.y + 1596));

	//building 1
	Animation* current_animation1 = &build1;
	rec_building1 = current_animation1->GetCurrentFrame();
	App->render->Blit(graphics_build1, (App->render->camera.x + 145), (App->render->camera.y + 1415), &rec_building1);
	rect_build1->SetPos((App->render->camera.x + 145), (App->render->camera.y + 1415));

	Animation* current_animation2 = &flag1;
	rec_flag1 = current_animation2->GetCurrentFrame();
	App->render->Blit(graphics_build1, (App->render->camera.x + 175), (App->render->camera.y + 1403), &rec_flag1);


	//Fade To Black ---------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->highscores);
		fading = true;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneCastle::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->callback == App->player)
	{
		App->render->moving_scene = false;
		App->fade->FadeToBlack(App->scene_castle, App->highscores);
	}
}