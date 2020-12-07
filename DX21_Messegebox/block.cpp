
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "block.h"
#include "player.h"
#include "camera.h"

//�u���b�N�̃e�N�X�`���̓ǂݍ���
static int	g_BlockTexture;

//�u���b�N�̈ʒu���W
D3DXVECTOR2	g_Block[BLOCK_MAX];

int Block_Count = 0;

void InitBlock()
{
	// TEX�̓ǂݍ���
	g_BlockTexture = Texture_SetTextureLoadFile("asset/steel_block.png");
	

	//�u���b�N�z�u
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
	
	//�u���b�N�z�u
	for (int i = 0; i < 50; i++)
	{
		g_Block[Block_Count].x = BLOCK_SIZE_X * i;
		g_Block[Block_Count].y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) + PLAYER_SIZE_Y - BLOCK_SIZE_Y*10;
		Block_Count++;
	}
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
		Sprite_Draw(g_BlockTexture, 
			g_Block[i].x, g_Block[i].y,
			BLOCK_SIZE_X, BLOCK_SIZE_Y,
			0, 0, 64, 64);
	}
}

//D3DXVECTOR2  GetBlockPosition(int n)
//{
//	//�w�肳�ꂽ�u���b�N�̈ʒu���W��Ԃ�
//	return g_Block[n];
//}

D3DXVECTOR2* GetBlockPosition()
{
	return g_Block;
}