#include "player.h"
#include "raymath.h"
#include "debug.h"
#include "constants.h"

#define PLAYER_ROT_SPEED 360
#define PLAYER_SPEED 250
#define PLAYER_ACCELERATION 750
#define PLAYER_DECELERATION 175
#define PLAYER_NUDGE_VELOCITY 150

#define FIELD_MIN_X (-PLAYER_RADIUS / 2)
#define FIELD_MAX_X (SCREEN_WIDTH + PLAYER_RADIUS / 2)
#define FIELD_MIN_Y (-PLAYER_RADIUS / 2)
#define FIELD_MAX_Y (SCREEN_HEIGHT + PLAYER_RADIUS / 2)

static void UpdateAngle(Player* player, float frametime)
{
	int xIn = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
	player->rotation += (xIn * PLAYER_ROT_SPEED * frametime);
}

static void UpdateVelocity(Player* player, float frametime)
{
	int yIn = (int)IsKeyDown(KEY_UP) - (int)IsKeyDown(KEY_DOWN);
	float magSqr = Vector2LengthSqr(player->velocity);
	float mag = sqrt(magSqr);
	Vector2 facingDirection = PlayerFacingDirection(*player);
	if (yIn > 0)
	{
		player->velocity = Vector2Add(player->velocity,
			Vector2Scale(facingDirection, PLAYER_ACCELERATION * frametime));
		if (mag > PLAYER_SPEED)
		{
			player->velocity = Vector2Scale(player->velocity, PLAYER_SPEED / mag);
		}
	}
	else
	{
		if (mag > 0)
		{
			float xSign = (player->velocity.x < 0) ? -1.0f: 1.0f;
			float ySign = (player->velocity.y < 0) ? -1.0f: 1.0f;

			float xAbs = player->velocity.x * xSign;
			float yAbs = player->velocity.y * ySign;

			float xWeight = xAbs * xAbs / magSqr;
			float yWeight = yAbs * yAbs / magSqr;

			float xDecel = xWeight * PLAYER_DECELERATION * xSign * frametime;
			float yDecel = yWeight * PLAYER_DECELERATION * ySign * frametime;

			player->velocity.x = (xAbs > xDecel) ? player->velocity.x - xDecel : 0;
			player->velocity.y = (yAbs > yDecel) ? player->velocity.y - yDecel : 0;
		}
	}

	return;
}

static void UpdateWrap(Player* player, float frametime)
{
	if (player->position.x > FIELD_MAX_X)
	{
		player->position.x = FIELD_MIN_X;

		if (player->velocity.x < PLAYER_NUDGE_VELOCITY)
		{
			player->velocity.x = PLAYER_NUDGE_VELOCITY;
		}
	}
	else if (player->position.x < FIELD_MIN_X)
	{
		player->position.x = FIELD_MAX_X;

		if (player->velocity.x > -PLAYER_NUDGE_VELOCITY)
		{
			player->velocity.x = -PLAYER_NUDGE_VELOCITY;
		}
	}
	
	if (player->position.y > FIELD_MAX_Y)
	{
		player->position.y = FIELD_MIN_Y;

		if (player->velocity.y < PLAYER_NUDGE_VELOCITY)
		{
			player->velocity.y = PLAYER_NUDGE_VELOCITY;
		}
	}
	else if (player->position.y < FIELD_MIN_Y)
	{
		player->position.y = FIELD_MAX_Y;

		if (player->velocity.y > -PLAYER_NUDGE_VELOCITY)
		{
			player->velocity.y = -PLAYER_NUDGE_VELOCITY;
		}
	}
}

void PlayerMove(Player* player)
{
	float frametime = GetFrameTime();

	if (player->state != PLAYER_STUNNED && player->state != PLAYER_DEAD)
	{
		UpdateAngle(player, frametime);
		UpdateVelocity(player, frametime);
	}

	player->position = Vector2Add(player->position, Vector2Scale(player->velocity, frametime));
	UpdateWrap(player, frametime);

	SetPlayerInfo(player->position, player->velocity, player->rotation);
}

void PlayerDraw(Player player, Texture2D texture)
{
	if (player.state == PLAYER_DEAD)
	{
		return;
	}

	const Rectangle source = {0, 0, 32, 32};
	Rectangle dest = {player.position.x, player.position.y, PLAYER_RADIUS * 2, PLAYER_RADIUS * 2};
	Vector2 origin = {dest.width / 2, dest.height / 2};

	Color color = WHITE;
	if (player.state == PLAYER_IFRAME)
	{
		float seconds = GetTime() - player.timeStateEntered;
		int value = (int)(seconds * 6.0f);
		if (value % 2)
		{
			color = Fade(RED, 0.6f);
		}
	}

	DrawTexturePro(texture, source, dest, origin, player.rotation, color);
}

Vector2 PlayerFacingDirection(Player player)
{
	return Vector2Rotate((Vector2){0, -1}, player.rotation * DEG2RAD);
}

void PlayerSetState(Player* player, PlayerState state)
{
	player->state = state;
	player->timeStateEntered = GetTime();
}