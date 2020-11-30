
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "block.h"
#include "player.h"
#include "camera.h"

//ブロックのテクスチャの読み込み
static int	g_BlockTexture;

//ブロックの位置座標
D3DXVECTOR2	g_Block[BLOCK_MAX];

int Block_Count = 0;

void InitBlock()
{
	// TEXの読み込み
	g_BlockTexture = Texture_SetTextureLoadFile("asset/steel_block.png");
	

	//ブロック配置
	for (int i = 0; i < 50; i++)
	{
		g_Block[Block_Count].x = BLOCK_SIZE_X * i;
		g_Block[Block_Count].y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) +PLAYER_SIZE_Y;
		Block_Count++;
	}

	for (int i = 0; i < 10; i++)
	{
		g_Block[Block_Count].x = BLOCK_SIZE_X * 50;
		g_Block[Block_Count].y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * i;
		Block_Count++;
	}

	for (int i = 0; i < 5; i++)
	{
		g_Block[Block_Count].x = BLOCK_SIZE_X * 3 *i;
		g_Block[Block_Count].y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * 5;
		Block_Count++;
	}

	for (int i = 0; i < 15; i++)
	{
		g_Block[Block_Count].x = BLOCK_SIZE_X * 3 * 5 + BLOCK_SIZE_X * 2 * i;
		g_Block[Block_Count].y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * 5;
		Block_Count++;
	}

	for (int i = 0; i < 10; i++)
	{
		g_Block[Block_Count].x = BLOCK_SIZE_X * 0;
		g_Block[Block_Count].y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * i;
		Block_Count++;
	}

	for (int i = 1; i <= 1; i++)
	{
		g_Block[Block_Count].x = BLOCK_SIZE_X * 45;
		g_Block[Block_Count].y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * i;
		Block_Count++;
	}

	for (int i = 1; i <= 2; i++)
	{
		g_Block[Block_Count].x = BLOCK_SIZE_X * 46;
		g_Block[Block_Count].y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * i;
		Block_Count++;
	}
	for (int i = 1; i <= 3; i++)
	{
		g_Block[Block_Count].x = BLOCK_SIZE_X * 47;
		g_Block[Block_Count].y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * i;
		Block_Count++;
	}
	for (int i = 1; i <= 4; i++)
	{
		g_Block[Block_Count].x = BLOCK_SIZE_X * 48;
		g_Block[Block_Count].y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * i;
		Block_Count++;
	}
	for (int i = 1; i <= 5; i++)
	{
		g_Block[Block_Count].x = BLOCK_SIZE_X * 49;
		g_Block[Block_Count].y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y * i;
		Block_Count++;
	}
	
	//ブロック配置
	for (int i = 0; i < 50; i++)
	{
		g_Block[Block_Count].x = BLOCK_SIZE_X * i;
		g_Block[Block_Count].y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y*10;
		Block_Count++;
	}
}


void UninitBlock()
{
	//テクスチャの開放
	Texture_Release(&g_BlockTexture, 1);

}

void UpdateBlock()
{
	
}

void DrawBlock()
{

	// ブロックを描画
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		Sprite_Draw(g_BlockTexture, 
			WorldToScreen(g_Block[i]).x, WorldToScreen(g_Block[i]).y,
			BLOCK_SIZE_X, BLOCK_SIZE_Y,
			0, 0, 64, 64);
	}
}

//D3DXVECTOR2  GetBlockPosition(int n)
//{
//	//指定されたブロックの位置座標を返す
//	return g_Block[n];
//}

D3DXVECTOR2* GetBlockPosition()
{
	return g_Block;
}