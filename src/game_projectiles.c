#include "game_projectiles.h"
#include "constants.h"
#include "game_asteroids.h"

#define PROJECTILE_MAX 12
static Projectile _projectiles[PROJECTILE_MAX];

void AddProjectile(Vector2 position, float rotation)
{
	bool created = false;

	for (int i = 0; i < PROJECTILE_MAX; i++)
	{
		if (_projectiles[i].active)
		{
			continue;
		}

		_projectiles[i] = CreateProjectile(position, rotation);
		created = true;
		break;
	}
	
	if (!created)
	{
		TraceLog(LOG_ERROR, "Failed to create a projectile because there was no inactive spots in the array!");
	}
}

static bool CheckCollisionProjectile(Projectile* projectile, Asteroid* asteroid)
{
	return (!asteroid->active)
		? false
		: CheckCollisionPointCircle(projectile->position, asteroid->position, AsteroidRadius(*asteroid));
}

int UpdateProjectiles(void)
{
	float frametime = GetFrameTime();
	float time = GetTime();
	
	Asteroid* asteroids = AsteroidsArray();

	int projectileCount = 0;
	for (int i = 0; i < PROJECTILE_MAX; i++)
	{
		Projectile* projectile = _projectiles + i;
		if (ProjectileUpdate(projectile, frametime, time))
		{
			projectileCount++;

			bool hit = false;
			for (int j = 0; j < ASTEROID_MAX; j++)
			{
				Asteroid* asteroid = asteroids + j;
				if (CheckCollisionProjectile(projectile, asteroid))
				{
					hit = true;
					DestroyAsteroid(j, projectile->rotation);
					projectile->active = false;
					// points earned?

					break;
				}
			}
		}
	}

	return projectileCount;
}

void DrawProjectiles(void)
{
	for (int i = 0; i < PROJECTILE_MAX; i++)
	{
		ProjectileDraw(_projectiles[i]);
	}
}

void ResetProjectiles(void)
{
	for (int i = 0; i < PROJECTILE_MAX; i++)
	{
		_projectiles[i] = (Projectile){0};
	}
}