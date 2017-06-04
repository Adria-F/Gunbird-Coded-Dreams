#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_DECORATION][COLLIDER_DECORATION] = false;
	matrix[COLLIDER_DECORATION][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_DECORATION][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_DECORATION][COLLIDER_PLAYER1_SHOT] = true;
	matrix[COLLIDER_DECORATION][COLLIDER_PLAYER2_SHOT] = true;
	matrix[COLLIDER_DECORATION][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_DECORATION][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_DECORATION][COLLIDER_AIR_ENEMY] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_DECORATION] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER1_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWER_UP] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_AIR_ENEMY] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_DECORATION] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER1_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER2_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_AIR_ENEMY] = false;

	matrix[COLLIDER_AIR_ENEMY][COLLIDER_DECORATION] = false;
	matrix[COLLIDER_AIR_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_AIR_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_AIR_ENEMY][COLLIDER_PLAYER1_SHOT] = true;
	matrix[COLLIDER_AIR_ENEMY][COLLIDER_PLAYER1_SHOT] = true;
	matrix[COLLIDER_AIR_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_AIR_ENEMY][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_AIR_ENEMY][COLLIDER_AIR_ENEMY] = false;

	matrix[COLLIDER_PLAYER1_SHOT][COLLIDER_DECORATION] = true;
	matrix[COLLIDER_PLAYER1_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER1_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER1_SHOT][COLLIDER_PLAYER1_SHOT] = false;
	matrix[COLLIDER_PLAYER1_SHOT][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER1_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER1_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER1_SHOT][COLLIDER_AIR_ENEMY] = true;

	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_DECORATION] = true;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER1_SHOT] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_AIR_ENEMY] = true;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_DECORATION] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER1_SHOT] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER2_SHOT] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_AIR_ENEMY] = false;

	matrix[COLLIDER_POWER_UP][COLLIDER_NONE] = true;
	matrix[COLLIDER_POWER_UP][COLLIDER_DECORATION] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER1_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_AIR_ENEMY] = false;
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(c1->CheckCollision(c2->rect) == true)
			{
 				if(matrix[c1->type][c2->type] && c1->callback) 
					c1->callback->OnCollision(c1, c2);
				
				if(matrix[c2->type][c1->type] && c2->callback) 
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if(App->render->debugging == false)
		return;

	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case COLLIDER_DECORATION: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case COLLIDER_AIR_ENEMY: // orange
			App->render->DrawQuad(colliders[i]->rect, 255, 153, 0, alpha);
			break;
			case COLLIDER_PLAYER1_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case COLLIDER_PLAYER2_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case COLLIDER_ENEMY_SHOT: // cyan
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case COLLIDER_POWER_UP: // magenta
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback, Particle* part)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback, part);
			break;
		}
	}

	return ret;
}

bool ModuleCollision::EraseCollider(Collider* collider)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	bool result = false;

	if (((rect.y + rect.h) > r.y && (r.y + r.h) > rect.y) && ((rect.x + rect.w) > r.x && (r.x + r.w) > rect.x))
	{
		result = true;
	}

	return result;
}