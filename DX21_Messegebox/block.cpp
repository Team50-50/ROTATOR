
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
				BLOCK_SIZE_X * Blocks[i].Width_Quantity, BLOCK_SIZE_Y * Blocks[i].High_Quantity,
				0, 0, 64 * Blocks[i].Width_Quantity, 64 * Blocks[i].High_Quantity);
		}
	}

}

void SetBlock(float x, float y, int w, int h)
{

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (Blocks[i].use == false)
		{
			Blocks[i].use = true;
			Blocks[i].xy.x = x;
			Blocks[i].xy.y = y;
			Blocks[i].Width_Quantity = w;
			Blocks[i].High_Quantity = h;
			break;
		}
	}

}

Block* GetBlockPosition()
{
	return Blocks;
}
