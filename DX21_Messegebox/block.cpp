
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "block.h"
#include "player.h"
#include "camera.h"

//�u���b�N�̃e�N�X�`���̓ǂݍ���
static int	g_BlockTexture;

//�u���b�N�̈ʒu���W
Block	Blocks[BLOCK_MAX];

int Block_Count = 0;

void InitBlock()
{
	// TEX�̓ǂݍ���
	g_BlockTexture = Texture_SetTextureLoadFile("asset/steel_block.png");
	

	////�u���b�N�z�u
	//for (int i = 0; i < 50; i++)
	//{
	//	Blocks[Block_Count].xy.x = BLOCK_SIZE_X * i;
	//	Blocks[Block_Count].xy.y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) +PLAYER_SIZE_Y;
	//	Block_Count++;
	//}

}

void UninitBlock()
{
	//�e�N�X�`���̊J��
	Texture_Release(&g_BlockTexture, 1);

}

void UpdateBlock()
{
	
}

void DrawBlock()
{
	// �u���b�N��`��
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
			Blocks[index].xy.y + BLOCK_SIZE_Y * 0.5f
		),
		BLOCK_SIZE_X * 0.5f
	};

	return c;
}