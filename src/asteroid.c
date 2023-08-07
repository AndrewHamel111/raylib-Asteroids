#include "asteroid.h"
#include "raymath.h"

Asteroid CreateAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size)
{
	return (Asteroid)
	{
		.active = true,
		.position = position,
		.velocity = velocity,
		.size = size,
		.rotation = GetRandomValue(0, 360),
		.rotationSpeed = GetRandomValue(ASTEROID_ROT_SPEED_MIN, ASTEROID_ROT_SPEED_MAX),
		.creationTime = GetTime()
	};
}

bool AsteroidUpdate(Asteroid* asteroid, float frametime, float time)
{
	if (!asteroid->active)
	{
		return false;
	}

	if (time > asteroid->creationTime + ASTEROID_LIFE)
	{
		asteroid->active = false;
		return false;
	}
	
	asteroid->position = Vector2Add(asteroid->position,
		Vector2Scale(asteroid->velocity, frametime));
	asteroid->rotation += asteroid->rotationSpeed * frametime;

	return true;
}

void AsteroidDraw(Asteroid asteroid)
{
	if (!asteroid.active)
	{
		return;
	}

	DrawPolyLines(asteroid.position, 3, AsteroidRadius(asteroid), asteroid.rotation, WHITE);
}

float AsteroidRadius(Asteroid asteroid)
{
	return 16.0f * (int)asteroid.size;
}