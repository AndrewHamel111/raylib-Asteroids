#ifndef ASTEROIDS_H_
#define ASTEROIDS_H_

#include "asteroid.h"

void AddAsteroid(Vector2 position, AsteroidSize size, float speedMod, bool spawn);
void DestroyAsteroid(int index, float angle);
Vector2 GetNextAsteroidPosition(void);
int UpdateAsteroids(void);
void DrawAsteroids(void);
Asteroid* AsteroidsArray(void);
void ResetAsteroids(void);

#endif