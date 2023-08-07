#ifndef DEBUG_H_
#define DEBUG_H_

#include "raylib.h"

/// @brief Call from within a BeginDrawing2D!
void ShowDebugMenu(void);

/// @brief Call from within a BeginDrawing2D!
void ShowDebugVisualizations(int asteroidCount, int projectileCount);

void SetLastCone(Vector2 position, Vector2 velocity, float angle, bool spawn);
void SetPlayerInfo(Vector2 position, Vector2 velocity, float rotation);

#endif