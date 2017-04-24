#include "Application.h"
#include "ModuleRender.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"
#include "Brown_Pot.h"

Brown_Pot::Brown_Pot(int x, int y) : Enemy(x, y)
{
	sprites = App->textures->Load("assets/maps/pot.png");
	
	pot_anim.PushBack({ 342, 202, 36, 53 });


	lives = 10;
	Animation* pot_animation = &pot_anim;

	SDL_Rect rect_pot = pot_animation->GetCurrentFrame();

	App->render->Blit(texture_pot, (App->render->camera.x + 8), (App->render->camera.y + 840), &rect_pot);

	collider = App->collision->AddCollider(rect_pot, COLLIDER_BUILDING, (Module*)App->enemies);
}

void Brown_Pot::Render()
{
	
}

void Brown_Pot::CleanUp()
{
	animation = &dead_pot;

	collider->to_delete = true;

	if (collider->to_delete == true) {

	};

	App->textures->Unload(texture_pot);
}
