/*=======================================================================================

	 爆発アニメーション[explosion.cpp]
												author:mgc
												date:2020/12/09
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#include"texture.h"
#include"sprite.h"
#include<d3dx9.h>
#include"explosion.h"
#include"animation.h"


 /*----------------------------------------------------------------------------------------
	グローバル変数
  ----------------------------------------------------------------------------------------*/
static int g_TextureExplosion = TEXTURE_INVALID_ID;
static Explosion g_Explosions[EXPLOSION_MAX];



/*-----------------------------------------------------------------------------------------
   関数定義
 -------------------------------------------------------------------------------------------*/
void InitExplosion(void)
{
	g_TextureExplosion = Texture_SetTextureLoadFile("asset/Explosion_black.png");

	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_Explosions[i].frame = 0;
		g_Explosions[i].enable = false;

		InitAnimations(g_Explosions[i].animation, DEFAULT, 500, 400, 5, 4, 20);
	}

}

void UninitExplosion(void)
{
	Texture_Release(&g_TextureExplosion, 1);
}

void UpdateExplosion(void)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosions[i].enable)
		{
			g_Explosions[i].frame++;
			g_Explosions[i].animation[DEFAULT].isUse = true;

			if (g_Explosions[i].frame > 70)
			{
				g_Explosions[i].animation[DEFAULT].animNo = 0;
				g_Explosions[i].enable = false;
			}



		}



	}
}

void DrawExplosion(void)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{

		if (g_Explosions[i].enable)
		{
			if (g_Explosions[i].animation[DEFAULT].isUse)
			{
				UpdateAnimations(g_Explosions[i].animation, DEFAULT, 3);

				Sprite_Draw(g_TextureExplosion, g_Explosions[i].position.x, g_Explosions[i].position.y, 100.0f, 100.0f,
					g_Explosions[i].animation[DEFAULT].tcx, g_Explosions[i].animation[DEFAULT].tcy,
					g_Explosions[i].animation[DEFAULT].tcw, g_Explosions[i].animation[DEFAULT].tch);
			}
		}
	}
}


void Explosion_Spawn(float x, float y)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (!g_Explosions[i].enable)
		{

			g_Explosions[i].enable = true;

			g_Explosions[i].position = D3DXVECTOR2(x, y);

			g_Explosions[i].frame = 0;

			break;
		}
	}

}

