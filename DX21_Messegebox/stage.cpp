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

	for (int i = 0; i < 50; i++)
	{
		SetBlock(BLOCK_SIZE_X * i, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y);
	}
	for (int i = 0; i < 10; i++)
	{
		SetBlock(BLOCK_SIZE_X * 30, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * i);
	}

	SetBlock(BLOCK_SIZE_X * 10, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y);

	//SetBlock(BLOCK_SIZE_X * 9, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y - 160);

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