#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

Enemy::Enemy(int x, int y, int wave) : position(x, y), wave(wave)
{}

Enemy::~Enemy()
{
	App->textures->Unload(sprites);
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{
	if(collider != nullptr)
		collider->SetPos(App->render->camera.x + position.x, App->render->camera.y + position.y);

	if (animation != nullptr)
		App->render->Blit(sprites, App->render->camera.x + position.x, App->render->camera.y + position.y, &(animation->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_PLAYER_SHOT)
	{
		lives -= 1;
	}
}