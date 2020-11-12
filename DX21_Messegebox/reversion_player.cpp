#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "player.h"
#include "revesion_player.h"
#include "directinput.h"

static int g_TextureVPlayer = TEXTURE_INVALID_ID;
//VPlayer g_VPlayer[VPLAYER_MAX];
ReversionPlayer g_ReversionPlayer;

//ブロックの描画座標
D3DXVECTOR2	g_ReversionPlayer_DrawPositition;

//プレイヤーが現在いる座標
D3DXVECTOR2	Current_PlayerPositionR;

//プレイヤーがスタートした時にいた座標
D3DXVECTOR2	Start_PlayerPositionR;

void ReversionPlayer_Initialize(void)
{
	g_TextureVPlayer = Texture_SetTextureLoadFile("asset/player.png");

	//プレイヤーの現在位置を取得
	Current_PlayerPositionR = GetPlayerPosition();

	//プレイヤーのスタート位置を保存
	Start_PlayerPositionR.x = Current_PlayerPositionR.x;
	Start_PlayerPositionR.y = Current_PlayerPositionR.y;
}


void ReversionPlayer_Finalize(void)
{
	Texture_Release(&g_TextureVPlayer, 1);
}


void ReversionPlayer_Update(void)
{
	//Queue q = GetqPrev();
	Stack prev_stack = GetstackPrev();

	//プレイヤー前のフレームのpositionデータをスタック領域から取得する
	for (int i = 0; i < prev_stack.recordFrame; i++)
	{
		if (GetKeyState('B') & 0x80)
		{
			//Bキーを押し続けたら、プレイヤー前のフレームのpositionデータを1フレームずつ、仮想プレイヤーに代入する
			//Bキーを離したら、仮想プレイヤーがその場で止まる
			g_ReversionPlayer.position = prev_stack.position_Data[i];
		}

		//===========================================
		//コントローラー
		//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
		if (IsButtonPush(ButtonLT))
		{
			g_ReversionPlayer.position = prev_stack.position_Data[i];
		}

	}

	//プレイヤーの現在位置を読み込み
	Current_PlayerPositionR = GetPlayerPosition();

	//再生キャラクターの描画位置を更新
	g_ReversionPlayer_DrawPositition.x = g_ReversionPlayer.position.x - (Current_PlayerPositionR.x - Start_PlayerPositionR.x);
	g_ReversionPlayer_DrawPositition.y = g_ReversionPlayer.position.y - (Current_PlayerPositionR.y - Start_PlayerPositionR.y);;

}


void ReversionPlayer_Draw(void)
{
	//Bを押すと逆行キャラクターを描画
	if (GetKeyState('B') & 0x80)
	{
		Sprite_Draw(g_TextureVPlayer, g_ReversionPlayer_DrawPositition.x, g_ReversionPlayer_DrawPositition.y,
			PLAYER_SIZE_X, PLAYER_SIZE_Y, 0, 0, 64, 128);
	}

}

//逆行キャラクターの位置情報を取得
ReversionPlayer GetVPlayer(void)
{
	return g_ReversionPlayer;
}


