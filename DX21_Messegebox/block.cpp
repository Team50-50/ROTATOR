
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "block.h"


unsigned int	g_BlockTexture;

BLOCK			g_Block[BLOCK_MAX];


void InitBlock()
{
	// TEXの読み込み
	g_BlockTexture = LoadTexture("rom/block.tga");

	// ブロック構造体の初期化
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		g_Block[i].Use = false;
	}

	// ブロックを配置している
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 8; x++)
		{	//			X座標,					Y座標,			Type（色）
			SetBlock(-350.0f + x * 100.0f, -375.0f + y * 50.0f, y / 2);
		}
	}
}



void UninitBlock()
{

	UnloadTexture(g_BlockTexture);

}


void UpdateBlock()
{
	int blockCount = 0;

	// 生きてるブロックの数を数えています
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Block[i].Use == true)
			blockCount++;
	}

	// 数えた数が０だったら全部消したって事になる
	if (blockCount <= 0)
	{
		// 全部消した時の処理をここに書く

	}

}



void DrawBlock()
{
	// TEXをセット
	SetTexture(g_BlockTexture);

	// ブロックを描画
	for (int i = 0; i < BLOCK_MAX; i++)
	{	// 生きてるブロックを描画
		if (g_Block[i].Use == true)
		{
			DrawSprite(g_Block[i].Position.x, g_Block[i].Position.y, 128.0f, 64.0f,
				0.0f, g_Block[i].Type * 0.25f, 1.0f, 0.25f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

// ブロックを配置する関数
void SetBlock(float x, float y, int type)
{
	// 未使用のブロックを探す
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		// 未使用のブロックを見つけたら初期化して使用中に変える
		if (g_Block[i].Use == false)
		{
			g_Block[i].Position.x = x;
			g_Block[i].Position.y = y;
			g_Block[i].Type = type;
			g_Block[i].Use = true;
			break;
		}
	}

}


// ブロック構造体の先頭アドレスを返す関数
BLOCK *GetBlock()
{
	return g_Block;

	//return &g_Block[0];
}



