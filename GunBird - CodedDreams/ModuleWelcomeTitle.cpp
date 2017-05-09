#include "Globals.h"
#include "ModuleWelcomeTitle.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMine.h"
#include "ModulePlayer.h" //temp
#include "ModuleMarion.h" //temp
#include "ModuleAsh.h" //temp

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleWelcomeTitle::ModuleWelcomeTitle()
{
	// Background
	background.w = SCREEN_WIDTH;
	background.h = SCREEN_HEIGHT;
}

ModuleWelcomeTitle::~ModuleWelcomeTitle()
{}

// Load assets
bool ModuleWelcomeTitle::Start()
{
	LOG("Loading WelcomeTitle scene");
	bool ret = true;
	App->render->moving_scene = false;
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	graphics = App->textures->Load("assets/maps/credit-insert_welcome-page.png");

	LOG("Loading music");
	App->audio->Load("assets/music/welcome_title.ogg", App->audio->MUSIC);
	App->audio->Play(App->audio->MUSIC);

	fading = false;

	return ret;
}

// UnLoad assets
bool ModuleWelcomeTitle::CleanUp()
{
	LOG("Unloading WelcomeTitle scene");
	if (graphics != nullptr)
	{
		App->textures->Unload(graphics);
		graphics = nullptr;
	}

	App->audio->Stop();

	return true;
}

// Update: draw background

update_status ModuleWelcomeTitle::Update()
{
	// Draw everything --------------------------------------
	
	App->render->Blit(graphics, App->render->camera.x, App->render->camera.y, &background, 0.75f); // Welcome title Screen

	if ((App->input->keyboard[SDL_SCANCODE_SPACE] || App->input->controller[SDL_CONTROLLER_BUTTON_Y] == PAD_BUTON_STATE::BUTTON_DOWN) && fading == false && App->fade->GetFadeState() == false)
	{
		App->fade->FadeToBlack(this, App->scene_mine, 0.5f);
		fading = true;
	}

	App->player1->setCharacter(App->marion); //Character selection
	App->player2->setCharacter(App->ash); //Character selection

	return UPDATE_CONTINUE;
}