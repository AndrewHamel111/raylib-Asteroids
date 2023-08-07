#include "game.h"

#include "game_asteroids.h"
#include "game_projectiles.h"
#include "game_score.h"
#include "game_player.h"
#include "game_ui.h"

#include "constants.h"
#include "debug.h"
#include "raygui.h"

static int _activeAsteroids = 0;
static int _activeProjectiles = 0;

extern bool _quitGame;

typedef enum GameState
{
	GAME_MAIN_MENU = 0,
	GAME_PLAYING,
	GAME_OVER
} GameState;

static GameState _state;

static void SetState(GameState state)
{
	switch (state)
	{
	case GAME_MAIN_MENU:
		break;
		
	case GAME_PLAYING:
		ResetAsteroids();
		ResetPlayer();
		ResetProjectiles();
		ResetScore();
		break;
		
	case GAME_OVER:
		break;
	
	default:
		break;
	}

	_state = state;
}

void InitGame(void)
{
	InitPlayer();
}

void UpdateGame(void)
{
	_activeAsteroids = UpdateAsteroids();
	_activeProjectiles = UpdateProjectiles();
	UpdatePlayer();
}

void DrawGame(void)
{
	const int buttonWidth = 200;
	const int buttonHeight = 80;
	const Rectangle topButton = {SCREEN_CENTER.x - buttonWidth / 2, SCREEN_CENTER.y - buttonHeight / 2 - 5, buttonWidth, buttonHeight};
	const Rectangle bottomButton = {SCREEN_CENTER.x - buttonWidth / 2, SCREEN_CENTER.y + buttonHeight / 2 + 5, buttonWidth, buttonHeight};

	switch (_state)
	{
	case GAME_MAIN_MENU:
		if (GuiButton(topButton, "ASTEROIDS!"))
		{
			SetState(GAME_PLAYING);
			return;
		}

		if (GuiButton(bottomButton, "QUIT"))
		{
			_quitGame = true;
			return;
		}
		break;
		
	case GAME_PLAYING:
		DrawAsteroids();
		DrawProjectiles();
		DrawPlayer();
		DrawScore();
		DrawHealth();
		ShowDebugVisualizations(_activeAsteroids, _activeProjectiles);
		break;
		
	case GAME_OVER:
		DrawAsteroids();

		DrawRectangleRec(SCREEN_AREA, Fade(BLACK, 0.5f));

		const int fontSize = 64;
		const char* gameover = "GAME OVER!";
		float measure = MeasureText(gameover, fontSize);
		DrawText(gameover, SCREEN_CENTER.x - measure/2, fontSize * 1.5f, fontSize, WHITE);
		
		DrawScore();

		if (GuiButton(topButton, "PLAY AGAIN?"))
		{
			SetState(GAME_PLAYING);
			return;
		}

		if (GuiButton(bottomButton, "QUIT"))
		{
			_quitGame = true;
			return;
		}
		break;
	
	default:
		TraceLog(LOG_ERROR, "Unhandled GameState!");
		break;
	}

	ShowDebugMenu();
}

void GameOver(void)
{
	SetState(GAME_OVER);
}