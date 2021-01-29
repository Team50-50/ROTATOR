/*=======================================================================================

	 マップの制御[map.cpp]
												author:mgc
												date:2020/12/23
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#define _CRT_SECURE_NO_WARNINGS

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
#include "dore.h"
#include "map.h"
#include <stdio.h>
#include "debug_font.h"
#include "fade.h"
#include "stagechoice.h"
#include "sound.h"



 /*-----------------------------------------------------------------------------------------
  グローバル変数
 -------------------------------------------------------------------------------------------*/
static int g_Mapchip[MAP_YSIZE][MAP_XSIZE]
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 0, 0, 0, 6, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 0, 0, 0, 6, 6, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 0, 4, 0, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 4, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
	{ 1, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
	{ 1, 0, 0, 0, 4, 0, 0, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{ 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

static int g_Mapchip2[MAP_YSIZE][MAP_XSIZE]
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 0, 0, 6, 6, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 0, 0, 6, 6, 6, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 4, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 4, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 1},
	{ 1, 0, 0, 0, 1, 0, 0, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 1, 0, 0, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{ 1, 0, 0, 0, 6, 0, 0, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
	{ 1, 0, 0, 0, 6, 0, 0, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
	{ 1, 0, 0, 0, 6, 0, 0, 1, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

static int g_Mapchip3[MAP_YSIZE][MAP_XSIZE]
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 6, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 6, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 6, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 6, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 1, 0, 0, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 0, 0, 4, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 1},
	{ 1, 0, 0, 0, 6, 0, 0, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{ 1, 0, 0, 0, 6, 0, 0, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 1, 1},
	{ 1, 0, 0, 0, 6, 0, 0, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, 1, 1},
	{ 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 6, 1, 1},
	{ 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 4, 1, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

static int g_TextureMapchip = TEXTURE_INVALID_ID;
static int g_Texturekey = TEXTURE_INVALID_ID;
static int g_TextureGoal = TEXTURE_INVALID_ID;
CollisionCircle keyCircleCollision[20];
CollisionCircle blockCircleCollision[350];
CollisionCircle goalCircleCollision;
static int g_keyCnt;
static int g_playerkey;
static int g_blockCnt;
static int kx_NO[20];
static int ky_NO[20];
static int bx_NO[20];
static int by_NO[20];
static bool hit = false;
static int sec = 0;

/*-----------------------------------------------------------------------------------------
 関数定義
-------------------------------------------------------------------------------------------*/
void InitMap()
{
	g_TextureMapchip = Texture_SetTextureLoadFile("asset/mapchips.png");


	g_Texturekey = Texture_SetTextureLoadFile("asset/key.png");


	g_TextureGoal= Texture_SetTextureLoadFile("asset/exit6.png");


	hit = false;
	g_playerkey = 0;
	g_keyCnt = 0;
	g_blockCnt = 0;

	for (int y = 0; y < MAP_YSIZE; y++)
	{
		for (int x = 0; x < MAP_XSIZE; x++)
		{
			// チップ番号取得
			int chipNO = g_Mapchip[y][x];

			if (chipNO == 0) continue;

			if (chipNO == 10)
			{
				g_Mapchip[y][x] = 4;

				//鍵のチップ番号の要素数を取得
				kx_NO[g_keyCnt] = x;
				ky_NO[g_keyCnt] = y;

				//鍵のcollisionの範囲を決める
				keyCircleCollision[g_keyCnt].center =
				{ (float)MAPCHIP_WIDTH * x + MAPCHIP_WIDTH * 0.5f,
				  (float)MAPCHIP_HEIGHT * y + MAPCHIP_HEIGHT * 0.5f
				};
				keyCircleCollision[g_keyCnt].radius = MAPCHIP_WIDTH * 0.4f;

				keyCircleCollision[g_keyCnt].enable = true;

				g_keyCnt++;
			}

			if (chipNO == 1)
			{
				//ブロックのチップ番号の要素数を取得
				bx_NO[g_blockCnt] = x;
				by_NO[g_blockCnt] = y;

				//ブロックのcollisionの範囲を決める
				blockCircleCollision[g_blockCnt].center =
				{ (float)MAPCHIP_WIDTH * x + MAPCHIP_WIDTH * 0.5f,
				  (float)MAPCHIP_HEIGHT * y + MAPCHIP_HEIGHT * 0.5f
				};
				blockCircleCollision[g_blockCnt].radius = MAPCHIP_WIDTH * 0.5f;

				g_blockCnt++;

			}

			//鍵の円のcollisionをセットする
			if (chipNO == 4)
			{
				//鍵のチップ番号の要素数を取得
				kx_NO[g_keyCnt] = x;
				ky_NO[g_keyCnt] = y;

				//鍵のcollisionの範囲を決める
				keyCircleCollision[g_keyCnt].center =
				{ (float)MAPCHIP_WIDTH * x + MAPCHIP_WIDTH * 0.5f,
				  (float)MAPCHIP_HEIGHT * y + MAPCHIP_HEIGHT * 0.5f
				};
				keyCircleCollision[g_keyCnt].radius = MAPCHIP_WIDTH * 0.4f;

				keyCircleCollision[g_keyCnt].enable = true;

				g_keyCnt++;
			}

			if (chipNO == 6)
			{
				SetBlock(MAPCHIP_WIDTH * x, MAPCHIP_HEIGHT * y, 1, 1, BLOCK_TYPE::BLOCK_NORMAL);
			}

			if (chipNO == 7)
			{
				SetDore(MAPCHIP_WIDTH * x, MAPCHIP_HEIGHT * y);
			}

			if (chipNO == 8)
			{
				SetBlock(MAPCHIP_WIDTH * x, MAPCHIP_HEIGHT * y, 8, 1, BLOCK_TYPE::BLOCK_OFFSETY);
			}

			if (chipNO == 9)
			{
				goalCircleCollision.center = {
					(float)MAPCHIP_WIDTH * x + MAPCHIP_WIDTH * 0.5f,
					(float)MAPCHIP_HEIGHT * y + MAPCHIP_HEIGHT * 0.5f
				};
				goalCircleCollision.radius = MAPCHIP_WIDTH * 0.4f;
			}
		}
	}
	

}

void UninitMap()
{
	Texture_Release(&g_Texturekey, 1);
	Texture_Release(&g_TextureMapchip, 1);
	Texture_Release(&g_TextureGoal, 1);
}

void UpdateMap()
{
	CollisionCircle* playerCollision = Get_PlayerCollision();
	hit = false;

	//プレイヤーと鍵の衝突判定
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < g_keyCnt; j++)
		{
			if(!keyCircleCollision[j].enable) continue;

			if (Collision_CircleAndCircleHit(&playerCollision[i], &keyCircleCollision[j]))
			{
				g_Mapchip[ky_NO[j]][kx_NO[j]] = 10;
				hit = true;
				keyCircleCollision[j].enable = false;
				
				PlaySound(SOUND_LABEL_SE_COIN);

			}
		}

		// ゴール
		if (Collision_CircleAndCircleHit(&playerCollision[i], &goalCircleCollision))
		{
			if (sec == 0)
			{
				PlaySound(SOUND_LABEL_SE_CLEAR);
				sec = 1;
			}
			
			SetFade(FADE_OUT, SCENE_SCLEAR);
		}
	}

	if (hit)
	{
		g_playerkey++;
	}


	Rocket* rocket = Get_Rocket();

	//ロケットとブロックの衝突判定
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
			// チップ番号取得
			int chipNO = g_Mapchip[y][x];

			if (chipNO == 0) continue;

			//テクスチャ切り取り座標を更新
			int tcx = chipNO % 4 * MAPCHIP_WIDTH;
			int tcy = chipNO / 4 * MAPCHIP_HEIGHT;

			//描画座標
			D3DXVECTOR2 position = { (float)MAPCHIP_WIDTH * x,(float)MAPCHIP_HEIGHT * y };

			Sprite_Draw(g_TextureMapchip, position.x, position.y, tcx, tcy, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

			if (chipNO == 9)
			{
				Sprite_Draw(g_TextureGoal, MAPCHIP_WIDTH * x, MAPCHIP_HEIGHT * y, 64.0f, 64.0f, 0, 0, 64, 32);
			}
		}
	}

	Screen_Draw(g_Texturekey, 500.0f, 0.0f, 80.0f, 80.0f, 0, 0, 64, 64);
	char Buf[64];
	sprintf(Buf, "X");
	DebugFont_Draw(590.0f, 20.0f, Buf);

	sprintf(Buf, "%d", g_playerkey);
	DebugFont_Draw(650.0f, 20.0f, Buf);

}

//チップ4辺の接触情報を返す
void GetChipEdgeHit(int rectEdge, int chip_No_x, int chip_No_y, int& contactEdge, float& contactPosition)
{
	//チップ座標を算出
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

int& GetplayerKey(void)
{
	return g_playerkey;
}