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
#include"data_control.h"
#include"controller.h"

 /*----------------------------------------------------------------------------------------
	グローバル変数
  ----------------------------------------------------------------------------------------*/
static int g_TextureExplosion = TEXTURE_INVALID_ID;
static Explosion g_Explosions[EXPLOSION_MAX];

static DataStorage g_Current[EXPLOSION_MAX];
static DataStorage g_Prev[EXPLOSION_MAX];

static bool flag1 = false;
static bool flag2 = false;

/*-----------------------------------------------------------------------------------------
   関数定義
 -------------------------------------------------------------------------------------------*/
void InitExplosion(void)
{
	g_TextureExplosion = Texture_SetTextureLoadFile("asset/Explosion_black.png");

	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_Explosions[i].a = 255;
		g_Explosions[i].frame = 0;
		g_Explosions[i].lifeFrame = 0;
		g_Explosions[i].enable = false;

		InitAnimations(g_Explosions[i].animation, DEFAULT, 500, 400, 5, 4, 20);

		InitRecord(&g_Current[i]);
		InitRecord(&g_Prev[i]);
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
			if (g_Explosions[i].a == 255)
			{
				g_Explosions[i].frame++;
				g_Explosions[i].animation[DEFAULT].isUse = true;

				if (g_Explosions[i].frame > 70)
				{
					g_Explosions[i].animation[DEFAULT].animNo = 0;
					Explosion_Destory(i);
				}

			}

			if (g_Explosions[i].a == 0)
			{
				g_Explosions[i].lifeFrame++;
				if (g_Explosions[i].lifeFrame >= 360)
				{
					g_Explosions[i].enable = false;
				}
			}

		}

		//===============================================================================
		//爆発アニメーションの記録&&再生&&逆再生
		//===============================================================================
		if (g_Current[i].Idata_tail == 0)
		{
			flag1 = false;
			flag2 = true;
		}
		if (g_Current[i].Idata_tail == 360)
		{
			flag1 = true;
		}

		if (flag2)
		{
			DataRecord(
				&g_Current[i],
				g_Explosions[i].position,
				g_Explosions[i].animation[DEFAULT].animNo,
				g_Explosions[i].a,
				g_Explosions[i].enable
			);

			deq_Vec2Data(&g_Prev[i]);
			deq_NumData(&g_Prev[i]);
			deq_aData(&g_Prev[i]);
			deq_TFData(&g_Prev[i]);

			if (g_Explosions[i].a == 255 && g_Explosions[i].animation[DEFAULT].isUse == true)
			{
				//アニメーションを更新
				UpdateAnimations(g_Explosions[i].animation, DEFAULT, 3);
			}
		}


		if (g_Current[i].Idata_tail > 360)
		{
			deq_NumData(&g_Current[i]);
			deq_aData(&g_Current[i]);
			deq_Vec2Data(&g_Current[i]);
			deq_TFData(&g_Current[i]);
		}

		if (flag1)
		{
			if (GetKeyState('B') & 0x80 || JoystickPress(ButtonRT))
			{
				flag2 = false;

				DataRecord(
					&g_Prev[i],
					pop_Vec2Data(&g_Current[i]),
					pop_NumData(&g_Current[i]),
					pop_aData(&g_Current[i]),
					pop_TFData(&g_Current[i])
				);

			}
		}
	}
}

void DrawExplosion(void)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (!g_Explosions[i].enable) continue;

		if (g_Explosions[i].animation[DEFAULT].isUse)
		{
			Sprite_Draw(g_TextureExplosion, g_Explosions[i].position.x, g_Explosions[i].position.y, 100.0f, 100.0f,
				g_Explosions[i].animation[DEFAULT].tcx, g_Explosions[i].animation[DEFAULT].tcy,
				g_Explosions[i].animation[DEFAULT].tcw, g_Explosions[i].animation[DEFAULT].tch,
				D3DCOLOR_RGBA(255, 255, 255, g_Explosions[i].a));
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
			g_Explosions[i].a = 255;
			g_Explosions[i].frame = 0;
			g_Explosions[i].lifeFrame = 0;

			break;
		}
	}

}

void Explosion_Destory(int index)
{
	g_Explosions[index].a = 0;
}

DataStorage* GetRE_Prev(void)
{
	return g_Prev;
}