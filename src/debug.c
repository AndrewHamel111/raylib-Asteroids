#include "debug.h"
#include "constants.h"

#include "raymath.h"
#include "raygui.h"

static bool _showDebugMenu = false;
static bool _showAsteroidCount = false;
static bool _showProjectileCount = false;
static bool _showAngleCone = false;
static bool _showAngleConeSplitOnly = false;
static int _comboBoxActiveShowAngle = 0;

// debug_cones.c
void DrawAsteroidCones(void);
// debug_cones.c
void AddAsteroidCone(Vector2 position, Vector2 velocity, float angle, bool spawn);

static Vector2 _playerPosition = {0};
static Vector2 _playerVelocity = {0};
static float _playerRotation = 0;

void ShowDebugMenu(void)
{
	if (IsKeyPressed(KEY_GRAVE))
	{
		_showDebugMenu = !_showDebugMenu;
	}

	if (_showDebugMenu)
	{
		Rectangle r = {10, SCREEN_HEIGHT - 40, 20, 20};
		Rectangle rWide = {10, SCREEN_HEIGHT - 40, 180, 20};
		_showAsteroidCount = GuiCheckBox(r, "Show Asteroid Count", _showAsteroidCount);
		
		r.y -= 30;
		_showProjectileCount = GuiCheckBox(r, "Show Projectile Count", _showProjectileCount);

		r.y -= 30;
		rWide.y = r.y;
		_comboBoxActiveShowAngle = GuiComboBox(rWide, "Don't Show Angles\nShow New Asteroid Angle\nShow Split Asteroid Angle\nShow All Angles", _comboBoxActiveShowAngle);
	}

	_showAngleCone = _comboBoxActiveShowAngle > 0;
	_showAngleConeSplitOnly = _comboBoxActiveShowAngle == 2;
}

void ShowDebugVisualizations(int asteroidCount, int projectileCount)
{
	if (_showAngleCone)
	{
		// DrawLineV(line0[0], line0[1], RED);
		// DrawLineV(line1[0], line1[1], BLUE);
		DrawAsteroidCones();
	}

	if (_showAsteroidCount)
	{
		DrawRectangle(10, 10, 275, 52, Fade(BLACK, 0.6f));
		DrawText(TextFormat("ASTEROIDS: %d", asteroidCount), 20, 20, 32, WHITE);
	}

	if (_showProjectileCount)
	{
		DrawRectangle(10, 52, 275, 52, Fade(BLACK, 0.6f));
		DrawText(TextFormat("PROJECTILES: %d", projectileCount), 20, 20 + 52, 32, WHITE);
	}
}

void SetLastCone(Vector2 position, Vector2 velocity, float angle, bool spawn)
{
	if (spawn && _showAngleConeSplitOnly)
	{
		return;
	}

	AddAsteroidCone(position, velocity, angle, spawn);
}

void SetPlayerInfo(Vector2 position, Vector2 velocity, float rotation)
{
	_playerPosition = position;
	_playerVelocity = velocity;
	_playerRotation = rotation;
}