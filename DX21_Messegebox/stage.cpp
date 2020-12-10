#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "block.h"
#include "key.h"
#include "dore.h"
#include "player.h"
#include "stage.h"



void InitStage()
{

	// ƒeƒXƒg
	SetKey(((SCREEN_WIDTH - PLAYER_SIZE_X) / 2) - 200, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + (128 - 64));
	SetDore(((SCREEN_WIDTH - PLAYER_SIZE_X) / 2) + 500, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10));

	SetBlock(BLOCK_SIZE_X, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y, 50, 2);

}

void UninitStage()
{



}

void UpdateStage()
{



}

void DrawStage()
{



}