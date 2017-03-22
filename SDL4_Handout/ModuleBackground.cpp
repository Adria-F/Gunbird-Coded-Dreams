#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;
	
	// Ship animation
	ship.x = 8;
	ship.y = 24;
	ship.w = 521;
	ship.h = 176;
	/*ship.PushBack({ 8, 30, 521, 176 });
	ship.PushBack({ 8, 21, 521, 176 });
	ship.speed = 0.03f;*/

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// pink_girl animation
	pink_girl.PushBack({ 624, 16, 32, 56 });
	pink_girl.PushBack({ 624, 80, 32, 56 });
	pink_girl.PushBack({ 624, 144, 32, 56 });
	pink_girl.speed = 0.05f;

	// two_men animation
	two_men.PushBack({});
	two_men.PushBack({});
	two_men.PushBack({});
	two_men.speed = 0.05f;

	// gree_man animation
	green_man.PushBack({});
	green_man.PushBack({});
	green_man.speed = 0.05f;

	// blue_man animation
	blue_man.PushBack({});
	blue_man.PushBack({});
	blue_man.PushBack({});
	blue_man.speed = 0.05f;

	// brown_man animation
	brown_man.PushBack({});
	brown_man.PushBack({});
	brown_man.PushBack({});
	brown_man.speed = 0.05f;

	// purple_man animation
	purple_man.PushBack({});
	purple_man.PushBack({});
	purple_man.PushBack({});
	purple_man.speed = 0.05f;
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	boat_up = false;
	boat_delay = 0;
	float_variation = 1;
	graphics = App->textures->Load("ken_stage.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	// TODO 2: Draw the ship from the sprite sheet with some parallax effect
	App->render->Blit(graphics, 0, float_variation - 4, &ship, 0.9f);

	// TODO 3: Animate the girl on the ship (see the sprite sheet)
	App->render->Blit(graphics, 192, float_variation + 100, &(pink_girl.GetCurrentFrame()), 0.9f);
	App->render->Blit(graphics, 128, 96, &(two_men.GetCurrentFrame()), 0.9f);
	App->render->Blit(graphics, 224, 104, &(green_man.GetCurrentFrame()), 0.9f);
	App->render->Blit(graphics, 228, 96, &(blue_man.GetCurrentFrame()), 0.9f);
	App->render->Blit(graphics, 88, 24, &(brown_man.GetCurrentFrame()), 0.9f);
	App->render->Blit(graphics, 127, 24, &(purple_man.GetCurrentFrame()), 0.9f);
	
	App->render->Blit(graphics, 0, 170, &ground);

	if (boat_delay == 0)
	{
		if (boat_up == false)
		{
			if (float_variation < 3)
			{
				float_variation++;
			}
			else
			{
				boat_up = true;
			}
		}
		else
		{
			if (float_variation >= 0)
			{
				float_variation--;
			}
			else
			{
				boat_up = false;
			}
		}
		boat_delay = 20;
	}
	else
	{
		boat_delay--;
	}

	return UPDATE_CONTINUE;
}