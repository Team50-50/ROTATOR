/*=======================================================================================

	 �}�b�v�̐���[map.cpp]
												author:mgc
												date:2020/12/23
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "block.h"
#include "key.h"
#include "dore.h"
#include "player.h"
#include "key.h"
#include "sniper.h"
#include "block.h"
#include "explosion.h"
#include "collision.h"
#include "map.h"
#include <stdio.h>
#include "debug_font.h"


 /*-----------------------------------------------------------------------------------------
  �O���[�o���ϐ�
 -------------------------------------------------------------------------------------------*/
static int g_Mapchip[MAP_YSIZE][MAP_XSIZE]
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 4, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 4, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 4, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

static int g_TextureId = TEXTURE_INVALID_ID;
CollisionCircle keyCircleCollision[20];
CollisionCircle blockCircleCollision[350];
static int g_keyCnt;
static int g_blockCnt;
static int kx_NO[20];
static int ky_NO[20];
static int bx_NO[20];
static int by_NO[20];
static int aa = 0;

/*-----------------------------------------------------------------------------------------
 �֐���`
-------------------------------------------------------------------------------------------*/
void InitMap()
{
	g_TextureId = Texture_SetTextureLoadFile("asset/mapchip.png");

	g_keyCnt = 0;
	g_blockCnt = 0;

	for (int y = 0; y < MAP_YSIZE; y++)
	{
		for (int x = 0; x < MAP_XSIZE; x++)
		{
			// �`�b�v�ԍ��擾
			int chipNO = g_Mapchip[y][x];

			if (chipNO == 0) continue;

			if (chipNO == 1)
			{
				//�u���b�N�̃`�b�v�ԍ��̗v�f�����擾
				bx_NO[g_blockCnt] = x;
				by_NO[g_blockCnt] = y;

				//�u���b�N��collision�͈̔͂����߂�
				blockCircleCollision[g_blockCnt].center =
				{ (float)MAPCHIP_WIDTH * x + MAPCHIP_WIDTH * 0.5f,
				  (float)MAPCHIP_HEIGHT * y + MAPCHIP_HEIGHT * 0.5f
				};
				blockCircleCollision[g_blockCnt].radius = MAPCHIP_WIDTH * 0.5f;

				g_blockCnt++;

			}

			//���̉~��collision���Z�b�g����
			if (chipNO == 4)
			{
				//���̃`�b�v�ԍ��̗v�f�����擾
				kx_NO[g_keyCnt] = x;
				ky_NO[g_keyCnt] = y;

				//����collision�͈̔͂����߂�
				keyCircleCollision[g_keyCnt].center =
				{ (float)MAPCHIP_WIDTH * x + MAPCHIP_WIDTH * 0.5f,
				  (float)MAPCHIP_HEIGHT * y + MAPCHIP_HEIGHT * 0.5f
				};
				keyCircleCollision[g_keyCnt].radius = MAPCHIP_WIDTH * 0.4f;

				g_keyCnt++;
			}

			if (chipNO == 6)
			{
				SetBlock(MAPCHIP_WIDTH * x, MAPCHIP_HEIGHT * y, 1, 1, BLOCK_TYPE::BLOCK_NORMAL);
			}
			if (chipNO == 8)
			{
				SetBlock(MAPCHIP_WIDTH * x, MAPCHIP_HEIGHT * y, 8, 1, BLOCK_TYPE::BLOCK_OFFSETY);
			}
		}
	}

}

void UninitMap()
{
	Texture_Release(&g_TextureId, 1);
}

void UpdateMap()
{
	CollisionCircle* playerCollision = Get_PlayerCollision();

	//�v���C���[�ƌ��̏Փ˔���
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < g_keyCnt; j++)
		{
			if (Collision_CircleAndCircleHit(&playerCollision[i], &keyCircleCollision[j]))
			{
				g_Mapchip[ky_NO[j]][kx_NO[j]] = 0;

			}
		}
	}

	Rocket* rocket = Get_Rocket();

	//���P�b�g�ƃu���b�N�̏Փ˔���
	for (int i = 0; i < ROCKET_MAX; i++)
	{
		for (int j = 0; j < g_blockCnt; j++)
		{
			if (Collision_CircleAndCircleHit(&rocket[i].collision, &blockCircleCollision[j]))
			{
				if (rocket[i].enable)
				{
					Explosion_Spawn(rocket[i].position.x - 50.0f, rocket[i].position.y - 50.0f);
				}
				rocket[i].enable = false;

			}

		}
	}

}

void DrawMap()
{
	for (int y = 0; y < MAP_YSIZE; y++)
	{
		for (int x = 0; x < MAP_XSIZE; x++)
		{
			// �`�b�v�ԍ��擾
			int chipNO = g_Mapchip[y][x];

			if (chipNO == 0) continue;

			//�e�N�X�`���؂�����W���X�V
			int tcx = chipNO % 4 * MAPCHIP_WIDTH;
			int tcy = chipNO / 4 * MAPCHIP_HEIGHT;

			//�`����W
			D3DXVECTOR2 position = { (float)MAPCHIP_WIDTH * x,(float)MAPCHIP_HEIGHT * y };

			Sprite_Draw(g_TextureId, position.x, position.y, tcx, tcy, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

		}
	}

}

//�`�b�v4�ӂ̐ڐG����Ԃ�
void GetChipEdgeHit(int rectEdge, int chip_No_x, int chip_No_y, int& contactEdge, float& contactPosition)
{
	//�`�b�v���W���Z�o
	D3DXVECTOR2 chip_pos = D3DXVECTOR2(chip_No_x * MAPCHIP_WIDTH, chip_No_y * MAPCHIP_HEIGHT);

	switch (rectEdge)
	{
	case LEFTEDGE:
		contactEdge = RIGHTEDGE;
		contactPosition = chip_pos.x + MAPCHIP_WIDTH;
		break;
	case RIGHTEDGE:
		contactEdge = LEFTEDGE;
		contactPosition = chip_pos.x;
		break;
	case TOPEDGE:
		contactEdge = BOTTOMEDGE;
		contactPosition = chip_pos.y + MAPCHIP_HEIGHT;
		break;
	case BOTTOMEDGE:
		contactEdge = TOPEDGE;
		contactPosition = chip_pos.y;
		break;
	}
}

int* GetMapchip(void)
{
	return (int*)g_Mapchip;
}

int GetKeyCnt(void)
{
	return g_keyCnt;
}

CollisionCircle* Get_KeyCollision(void)
{
	return keyCircleCollision;
}