/*=======================================================================================

	 狙いシステム制御[sniper.cpp]
												author:mgc
												date:2020/11/23
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
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

 /*-----------------------------------------------------------------------------------------
  グローバル変数
 -------------------------------------------------------------------------------------------*/
static int	g_TextureRocket = TEXTURE_INVALID_ID;
static int	g_Texturelaser = TEXTURE_INVALID_ID;
static Rocket g_rocket[ROCKET_MAX];
static float angle;

void InitSniper(void)
{
	g_Texturelaser = Texture_SetTextureLoadFile("asset/red.tga");
	g_TextureRocket = Texture_SetTextureLoadFile("asset/bullet.png");

	angle = 0.0f;


	for (int i = 0; i < ROCKET_MAX; i++)
	{
		g_rocket[i].enable = false;

	}

}

void UninitSniper(void)
{
	Texture_Release(&g_TextureRocket, 1);
}

void UpdateSniper(void)
{

	if (Keylogger_Press(KL_J))
	{
		
		if (GetKeyState('S') & 0x80)
		{
			angle += 0.05f;
			
		}

		if (GetKeyState('W') & 0x80)
		{
			angle -= 0.05f;
			
		}
		
	}

	//コントローラー
	if (JoystickPress(ButtonLT))
	{

		if (JoystickPress(RStickDown))
		{
			angle += 0.05f;

		}

		if (JoystickPress(RStickUP))
		{
			angle -= 0.05f;

		}

	}


	Player player = GetPlayer();

	float CX = player.position.x + PLAYER_SIZE_X * 0.5f;
	float CY = player.position.y + PLAYER_SIZE_Y * 0.5f;

	Block* block;
	block = GetBlockPosition();

	for (int i = 0; i < ROCKET_MAX; i++)
	{
		/*g_rocket[i].target.x = CX + cosf(g_rocket[i].r_angle) * 1000;
		g_rocket[i].target.y = CY + sinf(g_rocket[i].r_angle) * 1000;*/

		if (g_rocket[i].enable)
		{
			g_rocket[i].position.x += cosf(g_rocket[i].r_angle) * ROCKET_SPEED;
			g_rocket[i].position.y += sinf(g_rocket[i].r_angle) * ROCKET_SPEED;

			//ロケットのcollisionの範囲を決める
			g_rocket[i].collision.center.x = g_rocket[i].position.x + cosf(ROCKET_WIDTH * 0.5f);
			g_rocket[i].collision.center.y = g_rocket[i].position.y + sinf(ROCKET_HEIGHT * 0.5f) + ROCKET_HEIGHT * 0.5f;
			g_rocket[i].collision.radius = ROCKET_WIDTH * 0.5f;

		}
		else
		{
			g_rocket[i].r_angle = angle;
		}

		if (g_rocket[i].position.y < 0.0f || g_rocket[i].position.y > STAGE_HEIGHT ||
			g_rocket[i].position.x < 0.0f || g_rocket[i].position.x > STAGE_WIDTH)
		{
			g_rocket[i].enable = false;
		}
	}

}

void DrawSniper(void)
{
	Player player = GetPlayer();
	float CX = player.position.x + PLAYER_SIZE_X * 0.5f;
	float CY = player.position.y + PLAYER_SIZE_Y * 0.5f;

	if (Keylogger_Press(KL_J) || JoystickPress(ButtonLT))
	{
		Sprite_Draw(g_Texturelaser,CX, CY ,
			1000.0f, 5.0f, 0, 0, 1000, 5,
			0.0f, 2.5f, angle);
	}
	//=========================================================
	//ロケット
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	for (int i = 0; i < ROCKET_MAX; i++)
	{
		if (!g_rocket[i].enable) continue;

		Sprite_Draw(g_TextureRocket,
			g_rocket[i].position.x,
			g_rocket[i].position.y,
			ROCKET_WIDTH, ROCKET_HEIGHT, 0, 0, 32.0f, 32.0f, 0.0f, 16.0f, g_rocket[i].r_angle);

	}
}

void Rocket_Spawn(float x, float y)
{
	for (int i = 0; i < ROCKET_MAX; i++)
	{
		if (g_rocket[i].enable) continue;

		g_rocket[i].enable = true;

		g_rocket[i].position = D3DXVECTOR2(x, y);

		break;
	}
}

Rocket* Get_Rocket(void)
{
	return g_rocket;
}