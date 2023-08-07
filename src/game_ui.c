#include "game_ui.h"
#include "game_player.h"
#include "constants.h"

void DrawHealth(void)
{
	const Color healthHigh = GREEN;
	const Color healthMed = YELLOW;
	const Color healthLow = RED;

	const float barWidth = 300.0f;
	const int lineThick = 8;
	const int cellGap = 3;
	const float cellWidth = (barWidth + cellGap - (lineThick * 2)) / PLAYER_HEALTH_MAX;
	const float cellHeight = 48;

	int health = PlayerHealth();

	Rectangle r = (Rectangle){ (SCREEN_WIDTH * 0.5f) - (barWidth * 0.5f), SCREEN_HEIGHT - cellWidth * 1.5f, barWidth, cellHeight };
	DrawRectangleRounded(r, 0.25f, 8, BLACK);

	r.x += lineThick;
	r.y += lineThick;
	r.width = cellWidth - cellGap;
	r.height = cellHeight - (lineThick * 2); 

	Color color = (health >= PLAYER_HEALTH_MAX * 0.6f) ? healthHigh : (health >= PLAYER_HEALTH_MAX * 0.25f) ? healthMed : healthLow;

	for (int i = 0; i < health; i++)
	{
		DrawRectangleRec(r, color);
		r.x += cellWidth;
	}
}