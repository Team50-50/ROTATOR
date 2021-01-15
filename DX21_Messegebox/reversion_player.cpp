/*==============================================================================

	再生プレイヤの制御[reversion_player.cpp]

													Author : マコウチュウ
													Date   :

==============================================================================*/
#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "player.h"
#include "revesion_player.h"
#include "directinput.h"
#include "controller.h"
#include "camera.h"
#include "data_control.h"
#include "animation.h"

/*-----------------------------------------------------------------------------------------
 グローバル変数
-------------------------------------------------------------------------------------------*/
static int g_TextureVPlayer[TYPE_MAX];

Player g_ReversionPlayer[2];
static int frame = 0;

void ReversionPlayer_Initialize(void)
{
	g_TextureVPlayer[DEFAULT] = Texture_SetTextureLoadFile("asset/player.png");
	g_TextureVPlayer[WALKING] = Texture_SetTextureLoadFile("asset/HEW_CHARA_Aniamtion_run_renban.png");

	for (int i = 0; i < 2; i++)
	{
		InitAnimations(g_ReversionPlayer[i].animation, WALKING, 192, 256, 3, 2, 6);
	}
}


void ReversionPlayer_Finalize(void)
{
	Texture_Release(&g_TextureVPlayer[DEFAULT], 1);
	Texture_Release(&g_TextureVPlayer[WALKING], 1);

}


void ReversionPlayer_Update(void)
{
	frame++;
	DataStorage prevData = GetPrev();
	DataStorage debugData = GetDebug();

	
	for (int i = 0; i < prevData.Vdata_tail; i++)
	{
		if (GetKeyState('B') & 0x80 || JoystickPress(ButtonRT))
		{
			g_ReversionPlayer[0].position = prevData.vec2Data[i];
			g_ReversionPlayer[0].RL = prevData.tfData[i];
			g_ReversionPlayer[0].animation[WALKING].animNo = prevData.numData[i];
			g_ReversionPlayer[0].direction.x = prevData.decimalData[i];
		}

	}
	for (int i = 0; i < debugData.Vdata_tail; i++)
	{
		g_ReversionPlayer[1].position = debugData.vec2Data[i];
		g_ReversionPlayer[1].RL = debugData.tfData[i];
		g_ReversionPlayer[1].animation[WALKING].animNo = debugData.numData[i];
		g_ReversionPlayer[1].direction.x = debugData.decimalData[i];
	}
	if (frame >= 360)
	{
		g_ReversionPlayer[1].enable = true;

		if (g_ReversionPlayer[1].direction.x != 0.0f)
		{
			g_ReversionPlayer[1].animation[DEFAULT].isUse = false;
			g_ReversionPlayer[1].animation[WALKING].isUse = true;
		}
		else
		{
			g_ReversionPlayer[1].animation[DEFAULT].isUse = true;
			g_ReversionPlayer[1].animation[WALKING].isUse = false;
		}
	}
	if ((frame >= 360 && GetKeyState('B') & 0x80) || 
		(frame >= 360 && JoystickPress(ButtonRT)))
	{
		g_ReversionPlayer[0].enable = true;

		if (g_ReversionPlayer[0].direction.x != 0.0f)
		{
			g_ReversionPlayer[0].animation[DEFAULT].isUse = false;
			g_ReversionPlayer[0].animation[WALKING].isUse = true;
		}
		else
		{
			g_ReversionPlayer[0].animation[DEFAULT].isUse = true;
			g_ReversionPlayer[0].animation[WALKING].isUse = false;
		}
	}
}


void ReversionPlayer_Draw(void)
{
	if (g_ReversionPlayer[0].enable)
	{
		if (g_ReversionPlayer[0].animation[DEFAULT].isUse)
		{
			if (!g_ReversionPlayer[0].RL)
			{
				Sprite_Draw(g_TextureVPlayer[DEFAULT], g_ReversionPlayer[0].position.x,
					g_ReversionPlayer[0].position.y,
					PLAYER_SIZE_X, PLAYER_SIZE_Y, 0, 0, 64, 128);
			}
			else
			{
				Sprite_DrawLeft(g_TextureVPlayer[DEFAULT], g_ReversionPlayer[0].position.x,
					g_ReversionPlayer[0].position.y,
					PLAYER_SIZE_X, PLAYER_SIZE_Y, 0, 0, 64, 128);
			}
		}

		if (g_ReversionPlayer[0].animation[WALKING].isUse)
		{
			UpdateAnimations(g_ReversionPlayer[0].animation, WALKING);

			if (!g_ReversionPlayer[0].RL)
			{
				Sprite_Draw(g_TextureVPlayer[WALKING], g_ReversionPlayer[0].position.x,
					g_ReversionPlayer[0].position.y, PLAYER_SIZE_X, PLAYER_SIZE_Y,
					g_ReversionPlayer[0].animation[WALKING].tcx, g_ReversionPlayer[0].animation[WALKING].tcy,
					g_ReversionPlayer[0].animation[WALKING].tcw, g_ReversionPlayer[0].animation[WALKING].tch);
			}
			else
			{
				Sprite_DrawLeft(g_TextureVPlayer[WALKING], g_ReversionPlayer[0].position.x,
					g_ReversionPlayer[0].position.y, PLAYER_SIZE_X, PLAYER_SIZE_Y,
					g_ReversionPlayer[0].animation[WALKING].tcx, g_ReversionPlayer[0].animation[WALKING].tcy,
					g_ReversionPlayer[0].animation[WALKING].tcw, g_ReversionPlayer[0].animation[WALKING].tch);
			}

		}
	}

	if (g_ReversionPlayer[1].enable)
	{
		if (g_ReversionPlayer[1].animation[DEFAULT].isUse)
		{
			if (!g_ReversionPlayer[1].RL)
			{
				Sprite_Draw(g_TextureVPlayer[DEFAULT], g_ReversionPlayer[1].position.x,
					g_ReversionPlayer[1].position.y,
					PLAYER_SIZE_X, PLAYER_SIZE_Y, 0, 0, 64, 128, D3DCOLOR_RGBA(255, 0, 255, 110));
			}
			else
			{
				Sprite_DrawLeft(g_TextureVPlayer[DEFAULT], g_ReversionPlayer[1].position.x,
					g_ReversionPlayer[1].position.y,
					PLAYER_SIZE_X, PLAYER_SIZE_Y, 0, 0, 64, 128, D3DCOLOR_RGBA(255, 0, 255, 110));
			}
		}

		if (g_ReversionPlayer[1].animation[WALKING].isUse)
		{
			UpdateAnimations(g_ReversionPlayer[1].animation, WALKING);

			if (!g_ReversionPlayer[1].RL)
			{
				Sprite_Draw(g_TextureVPlayer[WALKING], g_ReversionPlayer[1].position.x,
					g_ReversionPlayer[1].position.y, PLAYER_SIZE_X, PLAYER_SIZE_Y,
					g_ReversionPlayer[1].animation[WALKING].tcx, g_ReversionPlayer[1].animation[WALKING].tcy,
					g_ReversionPlayer[1].animation[WALKING].tcw, g_ReversionPlayer[1].animation[WALKING].tch,
					D3DCOLOR_RGBA(255, 0, 255, 110));
			}
			else
			{
				Sprite_DrawLeft(g_TextureVPlayer[WALKING], g_ReversionPlayer[1].position.x,
					g_ReversionPlayer[1].position.y, PLAYER_SIZE_X, PLAYER_SIZE_Y,
					g_ReversionPlayer[1].animation[WALKING].tcx, g_ReversionPlayer[1].animation[WALKING].tcy,
					g_ReversionPlayer[1].animation[WALKING].tcw, g_ReversionPlayer[1].animation[WALKING].tch,
					D3DCOLOR_RGBA(255, 0, 255, 110));
			}

		}
	}
}
