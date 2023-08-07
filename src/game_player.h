#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include "player.h"

#define PLAYER_PROJECTILE_OFFSET PLAYER_RADIUS
#define PLAYER_FIRE_DELAY 0.33f
#define PLAYER_HEALTH_MAX 5

void InitPlayer(void);
void DrawPlayer(void);
void UpdatePlayer(void);
int PlayerHealth(void);
void ResetPlayer(void);

#endif