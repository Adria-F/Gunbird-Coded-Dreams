#include "ModuleSelection.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMine.h"
#include "ModuleUI.h"
#include "ModuleMarion.h"
#include "ModuleAsh.h"

ModuleSelection::ModuleSelection()
{
	upper_rect = {16, 8, 224, 144};
	lower_rect = {251, 8, 224, 80};
	scroll = {15, 169, 417, 96};
}

ModuleSelection::~ModuleSelection()
{

}

bool ModuleSelection::Start()
{
	LOG("Loading Selection scene");
	background = App->textures->Load("assets/maps/selection_bckg.png");
	App->render->moving_scene = false;
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	scroll1_pos = 0.0f;
	scroll2_pos = -417.0f;
	selected_char = 1;

	LOG("Loading music");
	App->audio->Load("assets/music/selection.ogg", App->audio->MUSIC);
	App->audio->Play(App->audio->MUSIC);

	fading = false;

	App->ui->Enable();

	return true;
}

bool ModuleSelection::CleanUp()
{


	return true;
}

update_status ModuleSelection::Update()
{

	App->render->Blit(background, 0, 0, &upper_rect);
	App->render->Blit(background, 0, 240, &lower_rect);

	App->render->Blit(background, scroll1_pos, 144, &scroll);
	App->render->Blit(background, scroll2_pos, 144, &scroll);
	scroll1_pos += 0.3f;
	scroll2_pos += 0.3f;
	if (scroll1_pos >= 417)
	{
		scroll1_pos = -417;
	}
	if (scroll2_pos >= 417)
	{
		scroll2_pos = -417;
	}

	if ((App->input->keyboard[SDL_SCANCODE_A] || App->input->controller[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == PAD_BUTON_STATE::BUTTON_DOWN) && selected_char == 1)
		selected_char = 0;
	if ((App->input->keyboard[SDL_SCANCODE_D] || App->input->controller[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == PAD_BUTON_STATE::BUTTON_DOWN) && selected_char == 0)
		selected_char = 1;

	if ((App->input->keyboard[SDL_SCANCODE_SPACE] || App->input->controller[SDL_CONTROLLER_BUTTON_Y] == PAD_BUTON_STATE::BUTTON_DOWN) && fading == false && App->fade->GetFadeState() == false)
	{
		if (selected_char == 0)
		{
			App->player1->setCharacter(App->ash);
		}
		else
		{
			App->player1->setCharacter(App->marion);
		}
		App->fade->FadeToBlack(this, App->scene_mine, 0.5f);
		fading = true;
	}

	return UPDATE_CONTINUE;
}