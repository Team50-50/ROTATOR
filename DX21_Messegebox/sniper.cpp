/*=======================================================================================

	 �_���V�X�e������[sniper.cpp]
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
#include "camera.h"
#include "directinput.h"
#include "controller.h"
#include "keylogger.h"
#include "bg.h"

 /*-----------------------------------------------------------------------------------------
  �O���[�o���ϐ�
 -------------------------------------------------------------------------------------------*/
static int	g_TextureRocket = TEXTURE_INVALID_ID;
static D3DXVECTOR2 playerPosition;
static Rocket g_rocket[ROCKET_MAX];
static float angle;


void InitSniper(void)
{
	//g_Texturelaser = Texture_SetTextureLoadFile("asset/");
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

	//�R���g���[���[
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


	playerPosition = GetPlayerPosition();

	float CX = playerPosition.x + PLAYER_SIZE_X * 0.5f;
	float CY = playerPosition.y + PLAYER_SIZE_Y * 0.5f;


	for (int i = 0; i < ROCKET_MAX; i++)
	{
		/*g_rocket[i].target.x = CX + cosf(g_rocket[i].r_angle) * 1000;
		g_rocket[i].target.y = CY + sinf(g_rocket[i].r_angle) * 1000;*/

		if (g_rocket[i].enable)
		{
			g_rocket[i].position.x += cosf(g_rocket[i].r_angle) * ROCKET_SPEED;
			g_rocket[i].position.y += sinf(g_rocket[i].r_angle) * ROCKET_SPEED;
		
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
	playerPosition = GetPlayerPosition();
	float CX = playerPosition.x + PLAYER_SIZE_X * 0.5f;
	float CY = playerPosition.y + PLAYER_SIZE_Y * 0.5f;

	if (Keylogger_Press(KL_J) || JoystickPress(ButtonLT))
	{
		Sprite_Draw(-1,CX, CY ,
			1000.0f, 5.0f, 0, 0, 1000, 5,
			0.0f, 2.5f, angle);
	}
	//=========================================================
	//���P�b�g
	//������������������������������������������������������������
	for (int i = 0; i < ROCKET_MAX; i++)
	{
		if (!g_rocket[i].enable) continue;

		Sprite_Draw(g_TextureRocket,
			g_rocket[i].position.x,
			g_rocket[i].position.y,
			32.0f, 32.0f, 0, 0, 32.0f, 32.0f, 0.0f, 16.0f, g_rocket[i].r_angle);

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
