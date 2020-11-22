
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

void InitBlock()
{
	// TEXの読み込み
	g_BlockTexture = Texture_SetTextureLoadFile("asset/testblock.jpg");
	
	//ブロック配置
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		g_Block[i].x = BLOCK_SIZE_X * i;
		g_Block[i].y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) +PLAYER_SIZE_Y;
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

D3DXVECTOR2  GetBlockPosition(int n)
{
	//指定されたブロックの位置座標を返す
	return g_Block[n];
}



