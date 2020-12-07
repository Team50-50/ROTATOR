#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "player.h"
#include "revesion_player.h"
#include "directinput.h"
#include "controller.h"
#include "camera.h"
#include "data_control.h"

/*-----------------------------------------------------------------------------------------
 グローバル変数
-------------------------------------------------------------------------------------------*/
static int g_TextureVPlayer = TEXTURE_INVALID_ID;
static int g_TextureVPlayer2 = TEXTURE_INVALID_ID;
//VPlayer g_VPlayer[VPLAYER_MAX];
ReversionPlayer g_ReversionPlayer[2];
static int frame = 0;

void ReversionPlayer_Initialize(void)
{
	g_TextureVPlayer = Texture_SetTextureLoadFile("asset/player.png");
	g_TextureVPlayer2 = Texture_SetTextureLoadFile("asset/player.png");
	
}


void ReversionPlayer_Finalize(void)
{
	Texture_Release(&g_TextureVPlayer, 1);
	Texture_Release(&g_TextureVPlayer2, 1);
}


void ReversionPlayer_Update(void)
{
	frame++;
	DataStorage prevData = GetPrev();
	DataStorage debugData = GetDebug();

	//プレイヤー前のフレームのpositionデータをスタック領域から取得する
	for (int i = 0; i < prevData.data_tail; i++)
	{
		if (GetKeyState('B') & 0x80 || JoystickPress(ButtonRT))
		{
			//Bキーを押し続けたら、プレイヤー前のフレームのpositionデータを1フレームずつ、仮想プレイヤーに代入する
			//Bキーを離したら、仮想プレイヤーがその場で止まる
			g_ReversionPlayer[0].position = prevData.positionData[i];
		}

	}
	for (int i = 0; i < debugData.data_tail; i++)
	{
		g_ReversionPlayer[1].position = debugData.positionData[i];
	}
	if (frame >= 360)
	{
		g_ReversionPlayer[1].enable = true;
	}
	if ((frame >= 360 && GetKeyState('B') & 0x80) || 
		(frame >= 360 && JoystickPress(ButtonRT)))
	{
		g_ReversionPlayer[0].enable = true;
	}
}


void ReversionPlayer_Draw(void)
{
	//Bを押すと逆行キャラクターを描画
	if (g_ReversionPlayer[0].enable)
	{
		Sprite_Draw(g_TextureVPlayer, g_ReversionPlayer[0].position.x,
			g_ReversionPlayer[0].position.y,
			PLAYER_SIZE_X, PLAYER_SIZE_Y, 0, 0, 64, 128);
	}
	if (g_ReversionPlayer[1].enable)
	{
		Sprite_Draw(g_TextureVPlayer, g_ReversionPlayer[1].position.x,
			g_ReversionPlayer[1].position.y,
			PLAYER_SIZE_X, PLAYER_SIZE_Y, 0, 0, 64, 128, D3DCOLOR_RGBA(255, 0, 255, 110));
	}
}

////逆行キャラクターの位置情報を取得
//ReversionPlayer GetVPlayer(void)
//{
//	return g_ReversionPlayer;
//}


