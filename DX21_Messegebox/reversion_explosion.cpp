/*=======================================================================================

	 逆再生爆発アニメーション[reversion_explosion.cpp]
												author:mgc
												date:2021/01/24
 -----------------------------------------------------------------------------------------

 =========================================================================================*/

#include"texture.h"
#include"sprite.h"
#include<d3dx9.h>
#include"explosion.h"
#include"reversion_explosion.h"
#include"animation.h"
#include"data_control.h"
#include"controller.h"

 /*----------------------------------------------------------------------------------------
	グローバル変数
  ----------------------------------------------------------------------------------------*/
static int g_TextureRExplosion = TEXTURE_INVALID_ID;
static Explosion g_RExplosions[REXPLOSION_MAX];


/*-----------------------------------------------------------------------------------------
   関数定義
 -------------------------------------------------------------------------------------------*/
void InitRExplosion(void)
{
	g_TextureRExplosion = Texture_SetTextureLoadFile("asset/Explosion_black.png");

	for (int i = 0; i < REXPLOSION_MAX; i++)
	{
		g_RExplosions[i].a = 255;
		g_RExplosions[i].frame = 0;
		g_RExplosions[i].lifeFrame = 0;
		g_RExplosions[i].enable = false;

		InitAnimations(g_RExplosions[i].animation, DEFAULT, 500, 400, 5, 4, 20);
	}
}

void UninitRExplosion(void)
{
	Texture_Release(&g_TextureRExplosion, 1);
}

void UpdateRExplosion(void)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		for (int j = 0; j < GetRE_Prev()[i].Idata_tail; j++)
		{
			if (!GetRE_Prev()[i].tfData[j]) continue;

			if (GetKeyState('B') & 0x80 || JoystickPress(ButtonRT))
			{
				g_RExplosions[i].enable = GetRE_Prev()[i].tfData[j];
				g_RExplosions[i].position = GetRE_Prev()[i].vec2Data[j];
				g_RExplosions[i].a = GetRE_Prev()[i].aData[j];
				g_RExplosions[i].animation[DEFAULT].animNo = GetRE_Prev()[i].numData[j];
			}
		}

		if (g_RExplosions[i].a == 255)
		{
			g_RExplosions[i].animation[DEFAULT].isUse = true;
			UpdateAnimations(g_RExplosions[i].animation, DEFAULT);
		}
	}
}

void DrawRExplosion(void)
{
	for (int i = 0; i < REXPLOSION_MAX; i++)
	{
		if (g_RExplosions[i].enable)
		{

			if (g_RExplosions[i].animation[DEFAULT].isUse && g_RExplosions[i].animation[DEFAULT].animNo != 0)
			{
				Sprite_Draw(g_TextureRExplosion, g_RExplosions[i].position.x, g_RExplosions[i].position.y, 100.0f, 100.0f,
					g_RExplosions[i].animation[DEFAULT].tcx, g_RExplosions[i].animation[DEFAULT].tcy,
					g_RExplosions[i].animation[DEFAULT].tcw, g_RExplosions[i].animation[DEFAULT].tch,
					D3DCOLOR_RGBA(255, 255, 255, g_RExplosions[i].a));
			}
		}
	}
}


void RExplosion_Destory(int index)
{
	g_RExplosions[index].enable = false;
}
