#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "raylib.h"

typedef struct Projectile
{
	bool active;

	Vector2 position;
	float rotation;
	float creationTime;
} Projectile;

Projectile CreateProjectile(Vector2 position, float rotation);
bool ProjectileUpdate(Projectile* projectile, float frametime, float time);
void ProjectileDraw(Projectile projectile);

#endif