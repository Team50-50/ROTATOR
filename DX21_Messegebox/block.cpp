
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

void InitBlock()
{
	// TEX�̓ǂݍ���
	g_BlockTexture = Texture_SetTextureLoadFile("asset/testblock.jpg");
	
	//�u���b�N�z�u
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		g_Block[i].x = BLOCK_SIZE_X * i;
		g_Block[i].y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10) +PLAYER_SIZE_Y;
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
			WorldToScreen(g_Block[i]).x, WorldToScreen(g_Block[i]).y,
			BLOCK_SIZE_X, BLOCK_SIZE_Y,
			0, 0, 64, 64);
	}
}

D3DXVECTOR2  GetBlockPosition(int n)
{
	//�w�肳�ꂽ�u���b�N�̈ʒu���W��Ԃ�
	return g_Block[n];
}



