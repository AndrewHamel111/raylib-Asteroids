#include "game_score.h"

#include "raylib.h"
#include "constants.h"

static int _score = 0;

void ResetScore(void)
{
	_score = 0;
}

void AddScore(int points)
{
	_score += points;
}

void DrawScore(void)
{
	const int fontSize = 48;
	const int fontSizeSmall = 24;
	const Color black = Fade(BLACK, 0.8f);
	const Color white = Fade(WHITE, 0.8f);

	const int xPad = 16;
	const int yPad = 8;
	const int shadow = 8;

	const char* textNumber = TextFormat("%d", _score);
	const char* textPts = "PTS";
	float measureNumber = MeasureText(textNumber, fontSize);
	float measurePts = MeasureText(textPts, fontSizeSmall);

	int x = SCREEN_WIDTH - measureNumber - measurePts - (xPad * 1.5);
	int y = yPad;
	int xPts = x + measureNumber + (xPad * 0.5f);
	int yPts = y + (fontSize - fontSizeSmall);

	DrawText(textNumber, x + shadow, y + shadow, fontSize, black);
	DrawText(textPts, xPts + shadow, yPts + shadow, fontSizeSmall, black);
	DrawText(textNumber, x, y, fontSize, white);
	DrawText(textPts, xPts, yPts, fontSizeSmall, white);
}