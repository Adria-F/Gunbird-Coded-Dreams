#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 210

#include "Module.h"

struct Particle;

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_DECORATION,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_AIR_ENEMY,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_POWER_UP,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;
	Particle* part;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr, Particle* part = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback),
		part(part)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();
	//update_status PostUpdate();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr, Particle* part = nullptr);
	bool EraseCollider(Collider* collider);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
};

#endif // __ModuleCollision_H__