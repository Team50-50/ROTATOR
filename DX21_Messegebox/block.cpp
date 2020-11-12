
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

//ブロック描画座標
D3DXVECTOR2	g_Block_DrawPosition[BLOCK_MAX];

//プレイヤーが現在いる座標
D3DXVECTOR2	Current_PlayerPosition;

//プレイヤーがスタートした時にいた座標
D3DXVECTOR2	Start_PlayerPosition;

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

	//プレイヤーの現在位置を取得
	Current_PlayerPosition = GetPlayerPosition();
 
	//プレイヤーのスタート位置を保存
	Start_PlayerPosition.x = Current_PlayerPosition.x;
	Start_PlayerPosition.y = Current_PlayerPosition.y;
}


void UninitBlock()
{
	//テクスチャの開放
	Texture_Release(&g_BlockTexture, 1);

}

void UpdateBlock()
{
	//プレイヤー位置座標を保存
	Current_PlayerPosition = GetPlayerPosition();
	
	//主人公に合わせてブロック描画配置を更新
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		g_Block_DrawPosition[i].x = g_Block[i].x - (Current_PlayerPosition.x - Start_PlayerPosition.x);
		g_Block_DrawPosition[i].y = g_Block[i].y - (Current_PlayerPosition.y - Start_PlayerPosition.y);
	}
	
}



void DrawBlock()
{

	// ブロックを描画
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		Sprite_Draw(g_BlockTexture, g_Block_DrawPosition[i].x, g_Block_DrawPosition[i].y, BLOCK_SIZE_X, BLOCK_SIZE_Y,
			0, 0, 64, 64);
	}
}

D3DXVECTOR2  GetBlockPosition(int n)
{
	//指定されたブロックの位置座標を返す
	return g_Block[n];
}



