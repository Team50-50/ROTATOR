
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
static int g_PlayerTexture[TYPE_MAX];
static int g_TextureGreen = TEXTURE_INVALID_ID;
static int g_TextureRed = TEXTURE_INVALID_ID;
static int g_TextureBlue = TEXTURE_INVALID_ID;

static Player g_Player;

static DataStorage g_Current;
static DataStorage g_Prev;
static DataStorage g_Debug;

// 扉位置
Dore* DoresPosition;
// 鍵の所持数
static int g_PlayerKey;
// 鍵の使った数
static int g_PlayerUsedKey;

static bool flag1 = false;
static bool flag2 = false;
static float a = 0.f;
static float g_value = 0.0f;

// 移動方向のon/off
bool CangoR;
bool CangoL;

bool on_ground = false;

void InitPlayer()
{
	//プレイヤーのテクスチャ読み込み
	g_PlayerTexture[DEFAULT] = Texture_SetTextureLoadFile("asset/player.png");
	g_PlayerTexture[WALKING] = Texture_SetTextureLoadFile("asset/HEW_CHARA_Aniamtion_run_renban.png");
	g_TextureGreen = Texture_SetTextureLoadFile("asset/green.tga");
	g_TextureRed = Texture_SetTextureLoadFile("asset/red.tga");
	g_TextureBlue = Texture_SetTextureLoadFile("asset/blue.tga");

	//プレイヤーの初期位置の定義
	g_Player.position = { 50.0f,200.0f };

	//移動on/offの初期化
	CangoR = true;
	CangoL = true;
	
	g_Player.isJump = true;
	g_Player.RL = false;

	// 鍵の使った数の初期化
	g_PlayerUsedKey = 0;



	InitAnimations(g_Player.animation, WALKING, 192, 256, 3, 2, 6);
}


void UninitPlayer()
{
	//テクスチャの解放
	Texture_Release(&g_PlayerTexture[DEFAULT], 1);
	Texture_Release(&g_PlayerTexture[WALKING], 1);
	Texture_Release(&g_TextureGreen, 1);
	Texture_Release(&g_TextureRed, 1);
	Texture_Release(&g_TextureBlue, 1);
}


void UpdatePlayer()
{
	//進行方向を長さ1にする
	D3DXVec2Normalize(&g_Player.direction, &g_Player.direction);

	//次のフレームのために進行方向をクリアしておく
	g_Player.direction = D3DXVECTOR2(0.0f, 0.0f);

	for (int i = 0; i < TYPE_MAX; i++)
	{
		g_Player.animation[i].isUse = false;
	}

	g_Player.animation[DEFAULT].isUse = true;

	
	//Aを押して左に移動
	if (GetKeyState('A') & 0x80 || JoystickPress(LStickLeft))
	{
		g_Player.RL = true;
		g_Player.animation[DEFAULT].isUse = false;
		g_Player.animation[WALKING].isUse = true;
		if (CangoL == true)
		{
			GamePlayer_MoveLeft();
			CangoR = true;
		}
	}

	//Dを押して右に移動
	if (GetKeyState('D') & 0x80 || JoystickPress(LStickRight))
	{
		g_Player.RL = false;
		g_Player.animation[DEFAULT].isUse = false;
		g_Player.animation[WALKING].isUse = true;
		if (CangoR == true)
		{
			GamePlayer_MoveRight();
			CangoL = true;
		}
	}
	/*if (GetKeyState('A') & 0x80 || JoystickPress(LStickLeft) && GetKeyState('D') & 0x80 || JoystickPress(LStickRight))
	{
		CangoR = false;
		CangoL = false;
	}
	else
	{
		CangoR = true;
		CangoL = true;
	}*/

	//ジャンプ
	if (GetKeyState(VK_SPACE) & 0x80 || JoystickPress(ButtonY))
	{
		GamePlayer_Jump();

	}

	if (Keylogger_Release(KL_J) || JoystickRelease(ButtonLT))
	{
		Rocket_Spawn(g_Player.position.x + 32.0f, g_Player.position.y + 64.0f);

	}

	

	g_Player.position.y += g_Player.speed.y;

	if (on_ground == false)
	{
		g_Player.speed.y += GRAVITY;
	}

	if (g_Player.position.y >= 747.0f)
	{
		//プレイヤー落下処理
		g_Player.position.y = 747.0f;

		g_Player.isJump = false;

	}

	//ブロックの位置座標を取得
	Block* BlockPosition = GetBlockPosition();


	// ブロックの当たり判定を作成
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		// 上方判定
		if (g_Player.position.x + PLAYER_SIZE_X > BlockPosition[i].xy.x &&
			g_Player.position.x < BlockPosition[i].xy.x + BLOCK_SIZE_X * BlockPosition[i].Width_Quantity)
		{

			if (g_Player.position.y + PLAYER_SIZE_Y >= BlockPosition[i].xy.y)
			{
				if (g_Player.position.y + PLAYER_SIZE_Y <= BlockPosition[i].xy.y + (BLOCK_SIZE_Y * BlockPosition[i].High_Quantity) / 2)
				{
					on_ground = true;
					g_Player.isJump = false;
					g_Player.position.y = BlockPosition[i].xy.y - PLAYER_SIZE_Y;
				}
			}
			else
			{
				on_ground = false;
			}

			if (g_Player.position.y <= BlockPosition[i].xy.y + BLOCK_SIZE_Y * BlockPosition[i].High_Quantity)
			{
				if (g_Player.position.y >= BlockPosition[i].xy.y + (BLOCK_SIZE_Y * BlockPosition[i].High_Quantity) / 2)
				{
					on_ground = false;
					g_Player.position.y = BlockPosition[i].xy.y + (BLOCK_SIZE_Y * BlockPosition[i].High_Quantity);

				}
			}
		}
		if ((g_Player.position.y >= BlockPosition[i].xy.y &&
			g_Player.position.y <= BlockPosition[i].xy.y + (BLOCK_SIZE_Y * BlockPosition[i].High_Quantity)))
		{

			if (g_Player.position.x + PLAYER_SIZE_X > BlockPosition[i].xy.x)
			{
				if (g_Player.position.x + PLAYER_SIZE_X < BlockPosition[i].xy.x + BLOCK_SIZE_X * BlockPosition[i].Width_Quantity)
				{
					g_Player.position.x = BlockPosition[i].xy.x - BLOCK_SIZE_X * BlockPosition[i].Width_Quantity;
				}
			}

			if (g_Player.position.x < BlockPosition[i].xy.x + BLOCK_SIZE_X * BlockPosition[i].Width_Quantity)
			{
				if (g_Player.position.x > BlockPosition[i].xy.x - (BLOCK_SIZE_X * BlockPosition[i].Width_Quantity) / 2)
				{
					g_Player.position.x = BlockPosition[i].xy.x + BLOCK_SIZE_X * BlockPosition[i].Width_Quantity;
				}
			}
		}
		// ブロック左右判定

		if ((g_Player.position.y < BlockPosition[i].xy.y + (BLOCK_SIZE_Y * BlockPosition[i].High_Quantity) &&
			g_Player.position.y > BlockPosition[i].xy.y + ((BLOCK_SIZE_Y * BlockPosition[i].High_Quantity) * 0.5)) ||
			(g_Player.position.y + PLAYER_SIZE_Y > BlockPosition[i].xy.y &&
				g_Player.position.y + PLAYER_SIZE_Y > BlockPosition[i].xy.y + ((BLOCK_SIZE_Y * BlockPosition[i].High_Quantity) * 0.5)))
		{
			// 左側
			if (g_Player.position.x < BlockPosition[i].xy.x + ((BLOCK_SIZE_X * BlockPosition[i].Width_Quantity) * 0.5))
			{
				if (g_Player.position.x + PLAYER_SIZE_X > BlockPosition[i].xy.x)
				{
					//g_Player.direction.x = 0.0f;
					CangoR = false;
				}

			}

			// 右側
			if (g_Player.position.x + PLAYER_SIZE_X > BlockPosition[i].xy.x + ((BLOCK_SIZE_X * BlockPosition[i].Width_Quantity) * 0.5))
			{
				if (g_Player.position.x < BlockPosition[i].xy.x + BLOCK_SIZE_X * BlockPosition[i].Width_Quantity)
				{
					//g_Player.direction.x = 0.0f;
					CangoL = false;
				}

			}
		}
		
	}

	//プレイヤー座標の更新 (移動方向×速度)
	g_Player.position.x += g_Player.direction.x * g_Player.speed.x;

	// 扉の位置座標を取得
	DoresPosition = GetDores();
	// プレイヤーの鍵所持数を取得
	g_PlayerKey = GetPlayerKeyPossession();

	// 扉の当たり判定
	for (int i = 0; i < DORE_MAX; i++)
	{
		// 上方判定
		//if (g_Player.position.x + PLAYER_SIZE_X > DoresPosition[i].xy.x && g_Player.position.x < DoresPosition[i].xy.x + DORE_SIZE_X)
		//{

		//	if (g_Player.position.y + PLAYER_SIZE_Y >= DoresPosition[i].xy.y)
		//	{
		//		if (g_Player.position.y + PLAYER_SIZE_Y <= DoresPosition[i].xy.y + DORE_SIZE_Y / 2)
		//		{
		//			on_ground = true;
		//			g_Player.isJump = false;
		//			g_Player.position.y = DoresPosition[i].xy.y - PLAYER_SIZE_Y;
		//			//jump_amount = 0;
		//		}
		//	}
		//	else
		//	{
		//		on_ground = false;
		//	}

		//	if (g_Player.position.y <= DoresPosition[i].xy.y + DORE_SIZE_Y)
		//	{
		//		if (g_Player.position.y >= DoresPosition[i].xy.y + DORE_SIZE_Y / 2)
		//		{
		//			on_ground = false;
		//			g_Player.position.y = DoresPosition[i].xy.y + DORE_SIZE_Y;

		//		}
		//	}
		//}
		//if ((g_Player.position.y >= DoresPosition[i].xy.y && g_Player.position.y <= DoresPosition[i].xy.y + DORE_SIZE_Y))
		//{

		//	if (g_Player.position.x + PLAYER_SIZE_X > DoresPosition[i].xy.x)
		//	{
		//		if (g_Player.position.x + PLAYER_SIZE_X < DoresPosition[i].xy.x + DORE_SIZE_X)
		//		{
		//			g_Player.position.x = DoresPosition[i].xy.x - DORE_SIZE_X;
		//		}
		//	}
		//	if (g_Player.position.x < DoresPosition[i].xy.x + DORE_SIZE_X)
		//	{
		//		if (g_Player.position.x > DoresPosition[i].xy.x - DORE_SIZE_X / 2)
		//		{
		//			g_Player.position.x = DoresPosition[i].xy.x + DORE_SIZE_X;
		//		}
		//	}
		//}

		// 左右判定
		if (DoresPosition[i].use == true)
		{
			if (g_Player.position.y <= DoresPosition[i].xy.y + DORE_SIZE_Y && g_Player.position.y + PLAYER_SIZE_Y >= DoresPosition[i].xy.y)
			{
				if (g_Player.position.x < DoresPosition[i].xy.x + (DORE_SIZE_X * 0.5))
				{
					if (g_Player.position.x + PLAYER_SIZE_X > DoresPosition[i].xy.x)
					{
						if (g_PlayerKey > 0)
						{
							DelDore(i);
							g_PlayerUsedKey++;
						}
						else
						{
							CangoR = false;
						}
					}
				}
				if (g_Player.position.x + PLAYER_SIZE_X > DoresPosition[i].xy.x + (DORE_SIZE_X * 0.5))
				{
					if (g_Player.position.x < DoresPosition[i].xy.x + DORE_SIZE_X)
					{
						if (g_PlayerKey > 0)
						{
							DelDore(i);
							g_PlayerUsedKey++;
						}
						else
						{
							CangoL = false;
						}
					}
				}
			}
		}
	}



	if (g_Current.Pdata_tail == 0)
	{
		flag1 = false;
		flag2 = true;

	}
	if (g_Current.Pdata_tail == 360)
	{
		flag1 = true;
	}

	if (flag2)
	{
		DataRecord(&g_Current, g_Player.position, g_Player.RL, g_Player.animation[WALKING].animNo, g_Player.direction.x);

		deq_Positiondata(&g_Prev);
		deq_RLdata(&g_Prev);
		deq_Animdata(&g_Prev);
		deq_Directiondata(&g_Prev);
	}
	if (g_Current.Pdata_tail > 360)
	{
		DataRecord(&g_Debug, deq_Positiondata(&g_Current), deq_RLdata(&g_Current), deq_Animdata(&g_Current), deq_Directiondata(&g_Current));
	}
	if (g_Debug.Pdata_tail > 360)
	{
		deq_Positiondata(&g_Debug);
		deq_RLdata(&g_Debug);
		deq_Animdata(&g_Debug);
		deq_Directiondata(&g_Debug);
	}
	if (flag1)
	{
		if (GetKeyState('B') & 0x80 || JoystickPress(ButtonRT))
		{
			flag2 = false;
			DataRecord(&g_Prev, pop_Positiondata(&g_Current), pop_RLdata(&g_Current), pop_Animdata(&g_Current), pop_Directiondata(&g_Current));

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
	if (g_Player.animation[DEFAULT].isUse)
	{
		if (!g_Player.RL)
		{
			Sprite_Draw(g_PlayerTexture[DEFAULT], g_Player.position.x,
				g_Player.position.y, PLAYER_SIZE_X, PLAYER_SIZE_Y,
				0, 0, PLAYER_SIZE_X, PLAYER_SIZE_Y);
		}
		else
		{
			Sprite_DrawLeft(g_PlayerTexture[DEFAULT], g_Player.position.x,
				g_Player.position.y, PLAYER_SIZE_X, PLAYER_SIZE_Y,
				0, 0, PLAYER_SIZE_X, PLAYER_SIZE_Y);
		}
	}

	if (g_Player.animation[WALKING].isUse)
	{
		UpdateAnimations(g_Player.animation, WALKING, 15);

		if (!g_Player.RL)
		{
			Sprite_Draw(g_PlayerTexture[WALKING], g_Player.position.x,
				g_Player.position.y, PLAYER_SIZE_X, PLAYER_SIZE_Y,
				g_Player.animation[WALKING].tcx, g_Player.animation[WALKING].tcy,
				g_Player.animation[WALKING].tcw, g_Player.animation[WALKING].tch);
		}
		else
		{
			Sprite_DrawLeft(g_PlayerTexture[WALKING], g_Player.position.x,
				g_Player.position.y, PLAYER_SIZE_X, PLAYER_SIZE_Y,
				g_Player.animation[WALKING].tcx, g_Player.animation[WALKING].tcy,
				g_Player.animation[WALKING].tcw, g_Player.animation[WALKING].tch);
		}
	}

	Screen_Draw(g_TextureRed, 850.0f, 5.0f, 360.0f, 50.0f, 0, 0, 1000, 200);

	if (!flag1)
	{
		D3DXCOLOR color(1.0f, 1.0f, 1.0f, a);

		Screen_Draw(g_TextureGreen, 850.0f, 5.0f, g_Current.Pdata_tail, 50.0f, 0, 0, 1000, 200, color);

		//Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	}
	else
	{
		Screen_Draw(g_TextureGreen, 850.0f, 5.0f, g_Current.Pdata_tail, 50.0f, 0, 0, 1000, 200);
	}

	if (flag1 && flag2)
	{
		Screen_Draw(g_TextureBlue, 850.0f, 5.0f, 360.0f, 50.0f, 0, 0, 1000, 200);
	}

	char Buf[64];
	sprintf(Buf, "frame=%d", g_Current.Pdata_tail);
	DebugFont_Draw(900.0f, 50.0f, Buf);
}

//ゲームプレイヤーの移動処理
void GamePlayer_MoveLeft(void)
{
	g_Player.direction.x = -1.0f;
	g_Player.speed.x = 5.0f;
}
void GamePlayer_MoveRight(void)
{
	g_Player.direction.x = 1.0f;
	g_Player.speed.x = 5.0f;
}
void GamePlayer_Jump(void)
{
	if (!g_Player.isJump)
	{
		g_Player.speed.y = JUMP_FORCE;
		g_Player.isJump = true;
	}
}

CollisionCircle GamePlayer_GetCollision(void)
{
	CollisionCircle c = {
		D3DXVECTOR2(
			g_Player.position.x + PLAYER_SIZE_X * 0.5f,
			g_Player.position.y + PLAYER_SIZE_Y * 0.5f
		),
		PLAYER_SIZE_X * 0.5f
	};

	return c;
}

D3DXVECTOR2 GetPlayerPosition()
{
	return g_Player.position;
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