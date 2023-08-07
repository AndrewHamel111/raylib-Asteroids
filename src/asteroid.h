#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "raylib.h"

typedef enum AsteroidSize
{
	ASTEROID_SMALL = 1,
	ASTEROID_MEDIUM = 2,
	ASTEROID_LARGE = 4,
} AsteroidSize;

#define ASTEROID_ROT_SPEED_MIN 5
#define ASTEROID_ROT_SPEED_MAX 240

#define ASTEROID_SPEED_MIN 100
#define ASTEROID_SPEED_MAX 225

#define ASTEROID_LIFE 10.0f

typedef struct Asteroid
{
	bool active;

	Vector2 position;
	Vector2 velocity;
	AsteroidSize size;

	float rotation;
	float rotationSpeed;
	float creationTime;
} Asteroid;

Asteroid CreateAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size);
bool AsteroidUpdate(Asteroid* asteroid, float frametime, float time);
void AsteroidDraw(Asteroid asteroid);
float AsteroidRadius(Asteroid asteroid);

#endif