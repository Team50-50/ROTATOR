
#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "player.h"
#include "block.h"
#include "key.h"
#include "dore.h"
#include "directinput.h"
#include "controller.h"
#include "keylogger.h"
#include "camera.h"
#include "data_control.h"
#include "debug_font.h"
#include "sniper.h"
#include <stdio.h>

/*-----------------------------------------------------------------------------------------
 グローバル変数
-------------------------------------------------------------------------------------------*/
//プレイヤーテクスチャー読み込み
static int	g_PlayerTexture = TEXTURE_INVALID_ID;
static int g_TextureGreen = TEXTURE_INVALID_ID;
static int g_TextureRed = TEXTURE_INVALID_ID;
static int g_TextureBlue = TEXTURE_INVALID_ID;

static DataStorage g_Current;
static DataStorage g_Prev;
static DataStorage g_Debug;


//ブロック位置
//D3DXVECTOR2	BlockPosition[BLOCK_MAX];
D3DXVECTOR2*	BlockPosition;

// 扉位置
Dore* DoresPosition;
// 鍵の所持数
static int g_PlayerKey;
// 鍵の使った数
static int g_PlayerUsedKey;

//プレイヤー位置情報
D3DXVECTOR2	g_PlayerPosition;


//ジャンプ時の移動量
float	jump_amount;

// 地面にプレイヤーがいるかどうか？
bool on_ground;

static bool flag1 = false;
static bool flag2 = false;
static float a = 0.f;
static float g_value = 0.0f;

// 移動方向のon/off
bool CangoR;
bool CangoL;

void InitPlayer()
{
	//プレイヤーのテクスチャ読み込み
	g_PlayerTexture = Texture_SetTextureLoadFile("asset/player.png");
	g_TextureGreen = Texture_SetTextureLoadFile("asset/green.tga");
	g_TextureRed = Texture_SetTextureLoadFile("asset/red.tga");
	g_TextureBlue = Texture_SetTextureLoadFile("asset/blue.tga");

	//プレイヤーの初期位置の定義
	g_PlayerPosition.x = ((SCREEN_WIDTH - PLAYER_SIZE_X) / 2);
	g_PlayerPosition.y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10);

	//ジャンプ時の移動量を初期化
	jump_amount = 0;

	//移動on/offの初期化
	CangoR = true;
	CangoL = true;

	// 鍵の使った数の初期化
	g_PlayerUsedKey = 0;

	g_Current.data_head = 0;
	g_Current.data_tail = 0;
	g_Prev.data_head = 0;
	g_Prev.data_tail = 0;
	g_Debug.data_head = 0;
	g_Debug.data_tail = 0;
}


void UninitPlayer()
{
	//テクスチャの解放
	Texture_Release(&g_PlayerTexture,1);
	Texture_Release(&g_TextureGreen, 1);
	Texture_Release(&g_TextureRed, 1);
	Texture_Release(&g_TextureBlue, 1);
}


void UpdatePlayer()
{

	//Aを押して左に移動
	if (GetKeyState('A') & 0x80 || JoystickPress(LStickLeft))
	{
		if (CangoL == true)
		{
			g_PlayerPosition.x -= 10.0f;//移動量
		}
	}
	
	//Dを押して左に移動
	if (GetKeyState('D') & 0x80 || JoystickPress(LStickRight))
	{
		if (CangoR == true)
		{
			g_PlayerPosition.x += 10.0f;//移動量
		}
	}
	
	//ジャンプ
	if (GetKeyState(VK_SPACE) & 0x80 || JoystickPress(ButtonY))
	{
		if (on_ground == true)
		{
			jump_amount = 16.0f;//ジャンプ量
		}

	}

	if (Keylogger_Release(KL_J) || JoystickRelease(ButtonLT))
	{
		Rocket_Spawn(g_PlayerPosition.x + 32.0f, g_PlayerPosition.y + 64.0f);

	}

	
	
	//重力を常に発生させる
	jump_amount -= 1.0f;

	//プレイヤー落下処理
	g_PlayerPosition.y -= jump_amount;
	
	//ブロックの位置座標を取得
	BlockPosition = GetBlockPosition();

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_PlayerPosition.x + PLAYER_SIZE_X > BlockPosition[i].x && g_PlayerPosition.x < BlockPosition[i].x + BLOCK_SIZE_X)
		{
			if (g_PlayerPosition.y >= BlockPosition[i].y - PLAYER_SIZE_Y)
			{
				on_ground = true;
				g_PlayerPosition.y = BlockPosition[i].y - PLAYER_SIZE_Y;
				jump_amount = 0;
			}
			else
			{
				on_ground = false;
			}
		}

	}

	// 扉の位置座標を取得
	DoresPosition = GetDores();
	g_PlayerKey = GetPlayerKeyPossession();

	for (int i = 0; i < DORE_MAX; i++)
	{
		if (DoresPosition[i].use == true)
		{
			if (g_PlayerPosition.x < DoresPosition[i].xy.x + (DORE_SIZE_X * 0.5))
			{
				if (g_PlayerPosition.x + PLAYER_SIZE_X > DoresPosition[i].xy.x)
				{
					if (g_PlayerKey > 0)
					{
						
						DelDore(i);
						g_PlayerUsedKey++;

					}
					else
					{
						CangoR = false;
						CangoL = true;
					}
				}
				else
				{
					CangoR = true;
				}
			}
			if (g_PlayerPosition.x + PLAYER_SIZE_X > DoresPosition[i].xy.x + (DORE_SIZE_X * 0.5))
			{
				if (g_PlayerPosition.x < DoresPosition[i].xy.x + DORE_SIZE_X)
				{
					if (g_PlayerKey > 0)
					{

						DelDore(i);
						g_PlayerUsedKey++;

					}
					else
					{
						CangoR = false;
						CangoL = true;
					}
				}
				else
				{
					CangoL = true;
				}
			}
		}
	}
	


	if (g_Current.data_tail == 0)
	{
		flag1 = false;
		flag2 = true;

	}
	if (g_Current.data_tail == 360)
	{
		flag1 = true;
	}

	if (flag2)
	{
		DataRecord(&g_Current, g_PlayerPosition);
		dequeue(&g_Prev);
	}
	if (g_Current.data_tail > 360)
	{
		DataRecord(&g_Debug, dequeue(&g_Current));
	}
	if (g_Debug.data_tail > 360)
	{
		dequeue(&g_Debug);
	}
	if (flag1)
	{
		if (GetKeyState('B') & 0x80 || JoystickPress(ButtonRT))
		{
			flag2 = false;
			DataRecord(&g_Prev, pop(&g_Current));

		}
	}
	else
	{
		g_value += 0.05f;
		a = sinf(g_value);
		if (a <= 0)
		{
			a *= -1;
		}
	}

	
}


void DrawPlayer()
{
	
	//プレイヤーを画面中央に描画
	Sprite_Draw(g_PlayerTexture, WorldToScreen(g_PlayerPosition).x,
		WorldToScreen(g_PlayerPosition).y, PLAYER_SIZE_X, PLAYER_SIZE_Y,
	 0, 0, PLAYER_SIZE_X, PLAYER_SIZE_Y);
	Sprite_Draw(g_TextureRed, 850.0f,5.0f, 360.0f, 50.0f, 0, 0, 1000, 200);
	
	if (!flag1)
	{
		D3DXCOLOR color(1.0f, 1.0f, 1.0f, a);

		Sprite_Draw(g_TextureGreen, 850.0f, 5.0f, g_Current.data_tail, 50.0f, 0, 0, 1000, 200,color);

		//Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	}
	else
	{
		Sprite_Draw(g_TextureGreen, 850.0f, 5.0f, g_Current.data_tail, 50.0f, 0, 0, 1000, 200);
	}

	if (flag1 && flag2)
	{
		Sprite_Draw(g_TextureBlue, 850.0f, 5.0f, 360.0f, 50.0f, 0, 0, 1000, 200);
	}

	char Buf[64];
	sprintf(Buf, "frame=%d", g_Current.data_tail);
	DebugFont_Draw(900.0f, 50.0f, Buf);
}

CollisionCircle GamePlayer_GetCollision(void)
{
	CollisionCircle c = {
		D3DXVECTOR2(
			g_PlayerPosition.x + PLAYER_SIZE_X * 0.5f,
			g_PlayerPosition.y + PLAYER_SIZE_Y * 0.5f
		),
		PLAYER_SIZE_X * 0.5f
	};

	return c;
}

D3DXVECTOR2 GetPlayerPosition()
{
	return g_PlayerPosition;
}


DataStorage GetPrev(void)
{
	return g_Prev;
}

DataStorage GetDebug(void)
{
	return g_Debug;
}

int GetPlayerUseKey(void)
{
	return g_PlayerUsedKey;
}