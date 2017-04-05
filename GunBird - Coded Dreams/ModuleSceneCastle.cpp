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
}

ModuleSceneCastle::~ModuleSceneCastle()
{}

// Load assets
bool ModuleSceneCastle::Start()
{
	LOG("Loading castle scene");
	bool ret = true;
	graphics = App->textures->Load("assets/maps/castle_background.png");
	graphics_gturret = App->textures->Load("assets/enemies/General_Torpedo _ Castle mortar.png");
	rect_gturret = App->collision->AddCollider({ 0, 0, 32, 32 }, COLLIDER_ENEMY, this);
	App->render->moving_scene = true;

	App->render->camera.x = 0;
	App->render->camera.y = -1782;

	LOG("Loading Music");
	App->audio->Load("assets/music/castle-welcome_title.ogg", App->audio->MUSIC);
	App->audio->Play(App->audio->MUSIC);

	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();
	App->collision->Enable();
	fading = false;

	return ret;
}

// UnLoad assets
bool ModuleSceneCastle::CleanUp()
{
	LOG("Unloading castle scene");
	App->textures->Unload(graphics);

	graphics = nullptr;
	graphics_gturret = nullptr;

	App->audio->Stop();
	App->player->Disable();
	App->collision->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneCastle::Update()
{
	// Draw everything --------------------------------------
	Animation* current_animation = &gturret;
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, App->render->camera.x, App->render->camera.y, &background, 0.75f); // sea and sky

	App->render->Blit(graphics_gturret, (App->render->camera.x + 162), (App->render->camera.y + 1596), &r); // general_turret
	rect_gturret->SetPos((App->render->camera.x + 162), (App->render->camera.y + 1596));

	// TODO 3: make so pressing SPACE the HONDA stage is loaded
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