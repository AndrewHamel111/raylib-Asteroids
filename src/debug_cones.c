#include "asteroid.h"
#include "raymath.h"

#define DEBUG_CONE_LIFESPAN 1.0f // duration of cone fadeout
#define DEBUG_CONE_DELAY 1.0f // time before the cone begins to fade
typedef struct Cone
{
	float time;
	Vector2 line0[2];
	Vector2 line1[2];

	bool active;
	bool spawn;
} Cone;

#define DEBUG_CONE_MAX 10
static Cone _cones[DEBUG_CONE_MAX] = {0};

// so hacky. Prevents split asteroids from taking two entries in the array.
static Vector2 _lastPosition;

static bool DrawCone(Cone cone, float time, Color color1, Color color2)
{
	float t = 1.0f - ((time - (cone.time + DEBUG_CONE_DELAY)) / DEBUG_CONE_LIFESPAN);
	if (t <= 0)
	{
		return false;
	}

	t = Clamp(t, 0, 1.0f);

	DrawLineV(cone.line0[0], cone.line0[1], Fade(color1, t));
	DrawLineV(cone.line1[0], cone.line1[1], Fade(color2, t));

	return true;
}

void DrawAsteroidCones(bool splitOnly)
{
	float time = GetTime();

	for (int i = 0; i < DEBUG_CONE_MAX; i++)
	{
		Cone cone = _cones[i];

		if (!cone.active)
		{
			continue;
		}

		if (splitOnly && cone.spawn)
		{
			continue;
		}

		Color color = ColorFromHSV(360.0f * i / DEBUG_CONE_MAX, 0.4, 0.7);
		if (!DrawCone(cone, time, color, color))
		{
			_cones[i].active = false;
		}
	}
}

void AddAsteroidCone(Vector2 position, Vector2 velocity, float angle, bool spawn)
{
// so hacky. Prevents split asteroids from taking two entries in the array.
	if (_lastPosition.x == position.x && _lastPosition.y == position.y)
	{
		return;
	}

	_lastPosition = position;

	Cone cone = (Cone)
	{
		.active = true,
		.spawn = spawn,
		.time = GetTime()
	};
	cone.line0[0] = position;
	cone.line0[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10), -angle));
	cone.line1[0] = position;
	cone.line1[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10), angle));

	for (int i = 0; i < DEBUG_CONE_MAX; i++)
	{
		if (!_cones[i].active)
		{
			_cones[i] = cone;
			return;
		}
	}
}