
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "block.h"
#include "player.h"
#include "camera.h"

//ブロックのテクスチャの読み込み
static int	g_BlockTexture;

//ブロックの位置座標
Block	Blocks[BLOCK_MAX];

int Block_Count = 0;

void InitBlock()
{
	// TEXの読み込み
	g_BlockTexture = Texture_SetTextureLoadFile("asset/steel_block.png");
	

	////ブロック配置
	//for (int i = 0; i < 50; i++)
	//{
	//	Blocks[Block_Count].xy.x = BLOCK_SIZE_X * i;
	//	Blocks[Block_Count].xy.y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) +PLAYER_SIZE_Y;
	//	Block_Count++;
	//}

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
		
		if (Blocks[i].use) {
			Sprite_Draw(g_BlockTexture,
				Blocks[i].xy.x, Blocks[i].xy.y,
				BLOCK_SIZE_X, BLOCK_SIZE_Y,
				0, 0, 64, 64);
		}
	}

}

void SetBlock(float x, float y)
{

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (Blocks[i].use == false)
		{
			Blocks[i].use = true;
			Blocks[i].xy.x = x;
			Blocks[i].xy.y = y;
			break;
		}
	}

}

Block* GetBlockPosition()
{
	return Blocks;
}

CollisionCircle GameBlock_GetCollision(int index)
{
	CollisionCircle c = {
		D3DXVECTOR2(
			Blocks[index].xy.x + BLOCK_SIZE_X * 0.5f,
			Blocks[index].xy.x + BLOCK_SIZE_Y * 0.5f
		),
		BLOCK_SIZE_X * 0.5f
	};

	return c;
}