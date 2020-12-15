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

	// テスト
	//SetKey(((SCREEN_WIDTH - PLAYER_SIZE_X) / 2) - 200, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + (128 - 64));
	//SetDore(((SCREEN_WIDTH - PLAYER_SIZE_X) / 2) + 500, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10));

	SetBlock(BLOCK_SIZE_X - 64, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y, 50, 2);
	SetBlock(BLOCK_SIZE_X - 64, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * 2, 1, 1);
	SetBlock(BLOCK_SIZE_X - 64, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * 4, 1, 2);
	SetBlock(BLOCK_SIZE_X - 64, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * 6, 1, 2);

	SetBlock(BLOCK_SIZE_X * 5, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * 2, 1, 2);
	SetBlock(BLOCK_SIZE_X * 7, ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * 6, 2, 1);
	// x座標,y座標,横幅のブロックのサイズ,縦幅のブロックのサイズ

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