/*=======================================================================================

	 狙いシステム制御[sniper.cpp]
												author:mgc
												date:2020/11/23
 -----------------------------------------------------------------------------------------

 =========================================================================================*/

#define _CRT_SECURE_NO_WARNINGS

#include <d3dx9.h>
#include <D3dx9math.h>

#include "sniper.h"
#include "Mydirect3d.h"
#include "Texture.h"
#include "Sprite.h"
#include "player.h"
#include "block.h"
#include "camera.h"
#include "directinput.h"
#include "controller.h"
#include "keylogger.h"
#include "bg.h"
#include "explosion.h"
#include "map.h"
#include "debug_font.h"

#include<stdio.h>



 /*-----------------------------------------------------------------------------------------
  グローバル変数
 -------------------------------------------------------------------------------------------*/
static int	g_TextureRocket = TEXTURE_INVALID_ID;
static int	g_Texturelaser = TEXTURE_INVALID_ID;
static int	g_TextureReRocket = TEXTURE_INVALID_ID;
static D3DXVECTOR2 g_LaserPosition;
static Rocket g_rocket[ROCKET_MAX];
static Rocket g_reversionRocket[ROCKET_MAX];
static int g_rmax;
static float g_LaserAngle;
static int g_rocketCnt;

static DataStorage g_RocketCurrent[ROCKET_MAX];
static DataStorage g_RocketPrev[ROCKET_MAX];

static bool flag1 = false;
static bool flag2 = false;


/*-----------------------------------------------------------------------------------------
 関数定義
-------------------------------------------------------------------------------------------*/
void InitSniper(int rocket_max)
{
	g_Texturelaser = Texture_SetTextureLoadFile("asset/red.tga");
	g_TextureRocket = Texture_SetTextureLoadFile("asset/bullet.png");
	g_TextureReRocket = Texture_SetTextureLoadFile("asset/bullet.png");

	Texture_Load();

	g_rmax = rocket_max;

	g_LaserAngle = 0.0f;
	g_rocketCnt = 0;

	flag1 = false;
	flag2 = false;

	for (int i = 0; i < ROCKET_MAX; i++)
	{
		g_rocket[i].enable = false;
		g_rocket[i].a = 255;
		g_rocket[i].frame = 0;

		g_reversionRocket[i].enable = false;
		g_reversionRocket[i].a = 255;
		g_reversionRocket[i].frame = 0;

		InitRecord(&g_RocketCurrent[i]);
		InitRecord(&g_RocketPrev[i]);

	}

}

void UninitSniper(void)
{
	Texture_Release(&g_Texturelaser, 1);
	Texture_Release(&g_TextureRocket, 1);
	Texture_Release(&g_TextureReRocket, 1);
}

void UpdateSniper(void)
{
	if (Keylogger_Press(KL_J))
	{
		if (GetKeyState('S') & 0x80)
		{
			g_LaserAngle += 0.05f;

		}

		if (GetKeyState('W') & 0x80)
		{
			g_LaserAngle -= 0.05f;
		}

	}

	//コントローラー
	if (JoystickPress(ButtonLT))
	{

		if (JoystickPress(RStickDown))
		{
			g_LaserAngle += 0.05f;

		}

		if (JoystickPress(RStickUP))
		{
			g_LaserAngle -= 0.05f;
		}

	}


	Player player = GetPlayer();

	g_LaserPosition = {
		player.position.x + PLAYER_SIZE_X * 0.5f,
		player.position.y + PLAYER_SIZE_Y * 0.5f
	};

	Block* block;
	block = GetBlockPosition();

	for (int i = 0; i < ROCKET_MAX; i++)
	{
		if (g_rocket[i].enable)
		{
			if (g_rocket[i].a == 255)
			{
				g_rocket[i].position.x += cosf(g_rocket[i].r_angle) * ROCKET_SPEED;
				g_rocket[i].position.y += sinf(g_rocket[i].r_angle) * ROCKET_SPEED;

				//ロケットのcollisionの範囲を決める
				g_rocket[i].collision.center.x = g_rocket[i].position.x + cosf(ROCKET_WIDTH * 0.5f);
				g_rocket[i].collision.center.y = g_rocket[i].position.y + sinf(ROCKET_HEIGHT * 0.5f) + ROCKET_HEIGHT * 0.5f;
				g_rocket[i].collision.radius = ROCKET_WIDTH * 0.5f;
			}

			if (g_rocket[i].a == 0)
			{
				g_rocket[i].frame++;

				if (g_rocket[i].frame >= 360)
				{
					g_rocket[i].enable = false;
				}
			}
		}
		else
		{
			g_rocket[i].r_angle = g_LaserAngle;
		}

		if (g_rocket[i].position.y < 0.0f || g_rocket[i].position.y > STAGE_HEIGHT ||
			g_rocket[i].position.x < 0.0f || g_rocket[i].position.x > STAGE_WIDTH)
		{
			g_rocket[i].a = 0;
		}

		//===============================================================================
		//ロケラン発射の記録&&逆再生
		//===============================================================================
		if (g_RocketCurrent[i].Vdata_tail == 0)
		{
			flag1 = false;
			flag2 = true;
		}
		if (g_RocketCurrent[i].Vdata_tail == 360)
		{
			flag1 = true;
		}

		if (flag2)
		{
			DataRecord(
				&g_RocketCurrent[i],
				g_rocket[i].position,
				g_rocket[i].enable,
				g_rocket[i].a,
				g_rocket[i].r_angle
			);

			deq_TFData(&g_RocketPrev[i]);
			deq_Vec2Data(&g_RocketPrev[i]);
			deq_NumData(&g_RocketPrev[i]);
			deq_DecimalData(&g_RocketPrev[i]);
		}

		if (g_RocketCurrent[i].Vdata_tail > 360)
		{
			deq_TFData(&g_RocketCurrent[i]);
			deq_NumData(&g_RocketCurrent[i]);
			deq_Vec2Data(&g_RocketCurrent[i]);
			deq_DecimalData(&g_RocketCurrent[i]);
		}

		if (flag1)
		{
			if (GetKeyState('B') & 0x80 || JoystickPress(ButtonRT))
			{
				flag2 = false;

				DataRecord(
					&g_RocketPrev[i],
					pop_Vec2Data(&g_RocketCurrent[i]),
					pop_TFData(&g_RocketCurrent[i]),
					pop_NumData(&g_RocketCurrent[i]),
					pop_DecimalData(&g_RocketCurrent[i])
				);
			}

		}

		//=================================================================================
		//ロケットの記録&&逆再生
		//=================================================================================
		for (int j = 0; j < g_RocketPrev[i].Vdata_tail; j++)
		{
			if (!g_RocketPrev[i].tfData[j]) continue;

			if (GetKeyState('B') & 0x80 || JoystickPress(ButtonRT))
			{
				g_reversionRocket[i].enable = g_RocketPrev[i].tfData[j];
				g_reversionRocket[i].position = g_RocketPrev[i].vec2Data[j];
				g_reversionRocket[i].a = g_RocketPrev[i].numData[j];
				g_reversionRocket[i].r_angle = g_RocketPrev[i].decimalData[j];
			}

		}

		if (g_reversionRocket[i].a == 255)
		{
			//逆行ロケットのcollisionの範囲を決める
			g_reversionRocket[i].collision.center.x = g_reversionRocket[i].position.x + cosf(ROCKET_WIDTH * 0.5f);
			g_reversionRocket[i].collision.center.y = g_reversionRocket[i].position.y + sinf(ROCKET_HEIGHT * 0.5f) + ROCKET_HEIGHT * 0.5f;
			g_reversionRocket[i].collision.radius = ROCKET_WIDTH * 0.5f;

			for (int k = 0; k < 2; k++)
			{
				if (Collision_CircleAndCircleHit(&g_reversionRocket[i].collision, &GetPlayer().collision[k]))
				{
					//*Get_RocketMax() += 1;
					
					reversionRocket_Destory(i);

				}

			}

		}
	}


}

void DrawSniper(void)
{

	if (Keylogger_Press(KL_J) || JoystickPress(ButtonLT))
	{
		Sprite_Draw(g_Texturelaser, g_LaserPosition.x, g_LaserPosition.y,
			1000.0f, 5.0f, 0, 0, 1000, 5,
			0.0f, 2.5f, g_LaserAngle);
	}
	//=========================================================
	//ロケット
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	for (int i = 0; i < ROCKET_MAX; i++)
	{
		if (g_rocket[i].enable)
		{
			Sprite_Draw(g_TextureRocket,
				g_rocket[i].position.x,
				g_rocket[i].position.y,
				ROCKET_WIDTH, ROCKET_HEIGHT, 0, 0, 32.0f, 32.0f, 0.0f, 16.0f, g_rocket[i].r_angle,
				D3DCOLOR_RGBA(255, 255, 255, g_rocket[i].a));
		}

		if (g_reversionRocket[i].enable)
		{
			if (GetKeyState('B') & 0x80 || JoystickPress(ButtonRT))
			{
				Sprite_Draw(g_TextureReRocket,
					g_reversionRocket[i].position.x,
					g_reversionRocket[i].position.y,
					ROCKET_WIDTH, ROCKET_HEIGHT, 0, 0, 32.0f, 32.0f, 0.0f, 16.0f, g_reversionRocket[i].r_angle,
					D3DCOLOR_RGBA(255, 255, 255, g_reversionRocket[i].a));
			}
		}

	}

	Screen_Draw(g_TextureRocket, 500.0f, 60.0f, 80.0f, 80.0f, 0, 0, 32, 32);
	char Buf[64];
	sprintf(Buf, "X");
	DebugFont_Draw(590.0f, 70.0f, Buf);
	sprintf(Buf, "%d", g_rmax);
	DebugFont_Draw(650.0f, 70.0f, Buf);

}

void Rocket_Spawn(float x, float y)
{
	for (int i = 0; i < ROCKET_MAX; i++)
	{
		if (g_rocket[i].enable) continue;

		g_rocket[i].enable = true;
		g_rocket[i].a = 255;
		g_rocket[i].frame = 0;
		g_rocket[i].position = D3DXVECTOR2(x, y);

		g_rocketCnt++;

		break;
	}
}

void reversionRocket_Spawn(float x, float y)
{
	for (int i = 0; i < ROCKET_MAX; i++)
	{
		if (g_reversionRocket[i].enable) continue;

		g_reversionRocket[i].enable = true;
		g_reversionRocket[i].a = 255;
		g_reversionRocket[i].frame = 0;
		g_reversionRocket[i].position = D3DXVECTOR2(x, y);

		break;
	}
}

void Rocket_Destory(int index)
{
	g_rocket[index].a = 0;

	//g_rocket[index].enable = false;

	Explosion_Spawn(g_rocket[index].position.x - 50.0f, g_rocket[index].position.y - 50.0f);
}

void reversionRocket_Destory(int index)
{
	//g_reversionRocket[index].a = 0;

	g_reversionRocket[index].enable = false;

	//Explosion_Spawn(g_rocket[index].position.x - 50.0f, g_rocket[index].position.y - 50.0f);
}

Rocket* Get_Rocket(void)
{
	return g_rocket;
}

int* Get_RocketMax(void)
{
	return &g_rmax;
}

DataStorage* GetRocket_Prev(void)
{
	return g_RocketPrev;
}

int& Get_RocketCount(void)
{
	return g_rocketCnt;
}