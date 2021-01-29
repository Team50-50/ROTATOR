/*==============================================================================

	プレイヤの制御[player.cpp]

													Author : トウ ミンヨウ & マコウチュウ
													Date   :


==============================================================================*/
#define _CRT_SECURE_NO_WARNINGS

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
#include "map.h"
#include "fade.h"
#include "sound.h"



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
Dore* dore;
// 鍵の所持数
static int g_PlayerKey;
// 鍵の使った数
static int g_PlayerUsedKey;

static bool flag1 = false;
static bool flag2 = false;
static bool flag3 = false;
static bool flag4 = false;
static bool flag5 = false;
static float a = 0.f;
static float g_value = 0.0f;

// 移動方向のon/off
bool CangoR;
bool CangoL;


/*-----------------------------------------------------------------------------------------
 関数定義
-------------------------------------------------------------------------------------------*/
void InitPlayer()
{
	//プレイヤーのテクスチャ読み込み
	g_PlayerTexture[DEFAULT] = Texture_SetTextureLoadFile("asset/player.png");
	g_PlayerTexture[WALKING] = Texture_SetTextureLoadFile("asset/HEW_CHARA_Aniamtion_run_renban.png");
	g_TextureGreen = Texture_SetTextureLoadFile("asset/green.tga");
	g_TextureRed = Texture_SetTextureLoadFile("asset/red.tga");
	g_TextureBlue = Texture_SetTextureLoadFile("asset/blue.tga");



	//プレイヤーの初期位置の定義
	g_Player.position = { 90.0f,776.0f };
	g_Player.JumpVelocity = 0.0f;

	//移動on/offの初期化
	CangoR = true;
	CangoL = true;
	
	g_Player.isJump = true;
	g_Player.RL = false;

	// 鍵の使った数の初期化
	g_PlayerUsedKey = 0;

	InitRecord(&g_Current);
	InitRecord(&g_Prev);
	InitRecord(&g_Debug);

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
	float speed = 5.0f;

	g_Player.start = g_Player.position;
	g_Player.end = { g_Player.position.x + PLAYER_SIZE_X, g_Player.position.y + PLAYER_SIZE_Y };

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

		g_Player.direction.x -= speed;
	}

	//Dを押して右に移動
	if (GetKeyState('D') & 0x80 || JoystickPress(LStickRight))
	{
		g_Player.RL = false;
		g_Player.animation[DEFAULT].isUse = false;
		g_Player.animation[WALKING].isUse = true;

		g_Player.direction.x += speed;
	}
	if (CangoR == false && CangoL == false)
	{
		CangoR = true;
		CangoL = true;
	}

	//ジャンプ
	if (Keylogger_Press(KL_JUMP)|| JoystickPress(ButtonY))
	{
		if (!g_Player.isJump)
		{
			g_Player.isJump = true;
			g_Player.JumpVelocity = JUMP_FORCE;
		}

	}

	//プレイヤーの落下
	if (g_Player.isJump)
	{
		g_Player.direction.y = (g_Player.position.y - g_Player.PrevPosition.y) - g_Player.JumpVelocity;
		g_Player.JumpVelocity -= 1.0f;
	}

	g_Player.direction.y += GRAVITY;

	if (Keylogger_Release(KL_J) || JoystickRelease(ButtonLT))
	{
		Rocket_Spawn(g_Player.position.x + 32.0f, g_Player.position.y + 48.0f);

	}

	//======================================================================================
	//プレイヤーとマップチップの判定を行う
	//======================================================================================
	CollisionRect rect
	{
		{g_Player.position.x,g_Player.position.y},
		{g_Player.position.x + PLAYER_SIZE_X,g_Player.position.y + PLAYER_SIZE_Y}
	};

	int contact_edge = EDGENONE;
	float contact_pos = 0.0f;
	//プレイヤーとチップのX軸判定
	if (!Collision_RectAndMapchipEdgeHit(rect, { g_Player.direction.x, 0.0f }, contact_edge, contact_pos))
	{
		flag3 = false;
	}
	else
	{
		flag3 = true;
		SetPlayerMapPos(contact_edge, contact_pos);
	}

	//プレイヤーとチップのY軸判定
	if (!Collision_RectAndMapchipEdgeHit(rect, { 0.0f, g_Player.direction.y }, contact_edge, contact_pos))
	{
		flag4 = false;
		g_Player.isJump = true;
	}
	else
	{
		flag4 = true;
		SetPlayerMapPos(contact_edge, contact_pos);

	}
g_Player.start = {
		g_Player.position.x,
		g_Player.position.y
	};
	g_Player.end = {
		g_Player.position.x + PLAYER_SIZE_X,
		g_Player.position.y + PLAYER_SIZE_Y
	};
	
	//プレイヤーの移動処理
	if (!flag3)
	{
		g_Player.position.x += g_Player.direction.x;
	}
	if (!flag4)
	{
		g_Player.position.y += g_Player.direction.y;

	}

	//=================================================================================
	//プレイヤーとブロックの衝突判定
	//=================================================================================
	Block* block = GetBlockPosition();

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (block[i].use && block[i].a == 255)
		{
			
			//プレイヤーがブロックの上にいる時の衝突判定
			if (g_Player.end.y <= block[i].start.y)
			{
				if (g_Player.end.x > block[i].start.x && g_Player.start.x < block[i].end.x)
				{
					if (g_Player.end.y + g_Player.direction.y > block[i].start.y)
					{
						g_Player.isJump = false;
						g_Player.position.y = block[i].start.y - PLAYER_SIZE_Y;

					}
				}

			}

			//プレイヤーがブロックの下にいる時の衝突判定
			if (g_Player.start.y >= block[i].end.y)
			{

				if (g_Player.end.x > block[i].start.x && g_Player.start.x < block[i].end.x)
				{

					if (g_Player.start.y + g_Player.direction.y < block[i].end.y)
					{
						g_Player.position.y = block[i].end.y;
						g_Player.isJump = true;

					}
				}
			}
			//プレイヤーがブロックの左にいる時の衝突判定
			if (g_Player.direction.x > 0.0f)
			{
				if (g_Player.end.x <= block[i].start.x)
				{
					if (g_Player.start.y < block[i].end.y && g_Player.end.y > block[i].start.y)
					{
						if (g_Player.end.x + g_Player.direction.x > block[i].start.x)
						{
							g_Player.position.x = block[i].start.x - PLAYER_SIZE_X;
						}
					}
				}
			}

			//プレイヤーがブロックの右にいる時の衝突判定
			if (g_Player.direction.x < 0.0f)
			{
				if (g_Player.start.x >= block[i].end.x)
				{
					if (g_Player.start.y < block[i].end.y && g_Player.end.y > block[i].start.y)
					{
						if (g_Player.start.x + g_Player.direction.x < block[i].end.x)
						{
							g_Player.position.x = block[i].end.x;
						}
					}
				}
			}

			//=========================================================================================
			//プレイヤーとブロックの <角> の衝突判定
			//=========================================================================================
			if (g_Player.end.x - block[i].start.x <= 0 && g_Player.end.y - block[i].start.y <= 0 &&
				g_Player.end.x + g_Player.direction.x - block[i].start.x > 0 &&
				g_Player.end.y + g_Player.direction.y - block[i].start.y > 0)
			{
				if (g_Player.end.x + g_Player.direction.x - block[i].start.x >= g_Player.end.y + g_Player.direction.y - block[i].start.y)
				{
					g_Player.position.y = block[i].start.y - PLAYER_SIZE_Y;
				}
				else
				{
					g_Player.position.x = block[i].start.x - PLAYER_SIZE_X;
				}

			}

			if (block[i].end.x - g_Player.start.x <= 0 && g_Player.end.y - block[i].start.y <= 0 &&
				block[i].end.x - (g_Player.start.x + g_Player.direction.x) > 0 &&
				g_Player.end.y + g_Player.direction.y - block[i].start.y > 0)
			{
				if (block[i].end.x - (g_Player.start.x + g_Player.direction.x) >= g_Player.end.y + g_Player.direction.y - block[i].start.y)
				{
					g_Player.position.y = block[i].start.y - PLAYER_SIZE_Y;
				}
				else
				{
					g_Player.position.x = block[i].end.x;
				}

			}

			if (g_Player.end.x - block[i].start.x <= 0 && block[i].end.y - g_Player.start.y <= 0 &&
				g_Player.end.x + g_Player.direction.x - block[i].start.x > 0 &&
				block[i].end.y - (g_Player.start.y + g_Player.direction.y) > 0)
			{
				if (g_Player.end.x + g_Player.direction.x - block[i].start.x >= block[i].end.y - (g_Player.start.y + g_Player.direction.y))
				{
					g_Player.position.y = block[i].end.y;
				}
				else
				{
					g_Player.position.x = block[i].start.x - PLAYER_SIZE_X;
				}
			}

			if (block[i].end.x - g_Player.start.x <= 0 && block[i].end.y - g_Player.start.y <= 0 &&
				block[i].end.x - (g_Player.start.x + g_Player.direction.x) > 0 &&
				block[i].end.y - (g_Player.start.y + g_Player.direction.y) > 0)
			{
				if (block[i].end.x - (g_Player.start.x + g_Player.direction.x) >= block[i].end.y - (g_Player.start.y + g_Player.direction.y))
				{
					g_Player.position.y = block[i].end.y;
				}
				else
				{
					g_Player.position.x = block[i].end.x;
				}
			}
		}
	}

	////地面
	//if (g_Player.position.y >= 747.0f)
	//{

	//	g_Player.position.y = 747.0f;

	//	g_Player.isJump = false;

	//}

	g_Player.PrevPosition = g_Player.position;

	//プレイヤーの円のcollision
	g_Player.collision[0].center = {
		g_Player.position.x + PLAYER_SIZE_X * 0.5f,
		g_Player.position.y + 64.0f * 0.5f
	};
	g_Player.collision[0].radius = PLAYER_SIZE_X * 0.5f;

	g_Player.collision[1].center = {
		g_Player.position.x + PLAYER_SIZE_X * 0.5f,
		(g_Player.position.y + 64.0f) + 64.0f * 0.5f
	};
	g_Player.collision[1].radius = PLAYER_SIZE_X * 0.5f;


	// 扉の位置座標を取得
	dore = GetDores();
	// プレイヤーの鍵所持数を取得
	g_PlayerKey = GetPlayerKeyPossession();

	// 扉の当たり判定
	for (int i = 0; i < DORE_MAX; i++)
	{
		if (!dore[i].use) continue;

		//プレイヤーがドアの左にいる時の衝突判定
		if (g_Player.direction.x > 0.0f)
		{
			if (g_Player.end.x <= dore[i].start.x)
			{
				if (g_Player.start.y < dore[i].end.y && g_Player.end.y > dore[i].start.y)
				{
					if (g_Player.end.x + g_Player.direction.x > dore[i].start.x)
					{
						g_Player.position.x = dore[i].start.x - PLAYER_SIZE_X;
						if (GetplayerKey() > 0)
						{
							dore[i].use = false;
							GetplayerKey() -= 1;

							PlaySound(SOUND_LABEL_SE_DOOR);
						}
					}
				}
			}
		}

		//プレイヤーがドアの右にいる時の衝突判定
		if (g_Player.direction.x < 0.0f)
		{
			if (g_Player.start.x >= dore[i].end.x)
			{
				if (g_Player.start.y < dore[i].end.y && g_Player.end.y > dore[i].start.y)
				{
					if (g_Player.start.x + g_Player.direction.x < dore[i].end.x)
					{
						g_Player.position.x = dore[i].end.x;
						if (GetplayerKey() > 0)
						{
							dore[i].use = false;
							GetplayerKey() -= 1;

							PlaySound(SOUND_LABEL_SE_DOOR);
						}
					}
				}
			}
		}
	}

	//================================================================================
	//プレイヤーの記録&&再生&&逆再生
	//=================================================================================
	if (g_Current.Vdata_tail == 0)
	{
		flag1 = false;
		flag2 = true;
		flag5 = false;

	}
	if (g_Current.Vdata_tail == 360)
	{
		flag1 = true;
	}

	if (flag2)
	{
		DataRecord(&g_Current, g_Player.position, g_Player.RL, g_Player.animation[WALKING].animNo, g_Player.direction.x);

		deq_Vec2Data(&g_Prev);
		deq_TFData(&g_Prev);
		deq_NumData(&g_Prev);
		deq_DecimalData(&g_Prev);
	}
	if (g_Current.Vdata_tail > 360)
	{
		DataRecord(&g_Debug, deq_Vec2Data(&g_Current), deq_TFData(&g_Current), deq_NumData(&g_Current), deq_DecimalData(&g_Current));
	}
	if (g_Debug.Vdata_tail > 360)
	{
		deq_Vec2Data(&g_Debug);
		deq_TFData(&g_Debug);
		deq_NumData(&g_Debug);
		deq_DecimalData(&g_Debug);
	}
	if (flag1)
	{
		if (Keylogger_Trigger(KL_B) || JoystickTrigger(ButtonRT))
		{
			flag2 = false;
			flag5 = true;	
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

	if (flag5)
	{
		DataRecord(&g_Prev, pop_Vec2Data(&g_Current), pop_TFData(&g_Current), pop_NumData(&g_Current), pop_DecimalData(&g_Current));
	}

	if (Keylogger_Press(KL_R))
	{
		SetFade(FADE_OUT, SCENE_GAME);
		//PlaySE(SE_06);
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
				g_Player.position.y+10, PLAYER_SIZE_X, PLAYER_SIZE_Y,
				g_Player.animation[WALKING].tcx, g_Player.animation[WALKING].tcy,
				g_Player.animation[WALKING].tcw, g_Player.animation[WALKING].tch);
		}
		else
		{
			Sprite_DrawLeft(g_PlayerTexture[WALKING], g_Player.position.x,
				g_Player.position.y+10, PLAYER_SIZE_X, PLAYER_SIZE_Y,
				g_Player.animation[WALKING].tcx, g_Player.animation[WALKING].tcy,
				g_Player.animation[WALKING].tcw, g_Player.animation[WALKING].tch);
		}
	}

	Screen_Draw(g_TextureRed, 850.0f, 5.0f, 360.0f, 50.0f, 0, 0, 1000, 200);

	if (!flag1)
	{
		D3DXCOLOR color(1.0f, 1.0f, 1.0f, a);

		Screen_Draw(g_TextureGreen, 850.0f, 5.0f, g_Current.Vdata_tail, 50.0f, 0, 0, 1000, 200, color);

		//Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	}
	else
	{
		Screen_Draw(g_TextureGreen, 850.0f, 5.0f, g_Current.Vdata_tail, 50.0f, 0, 0, 1000, 200);
	}

	if (flag1 && flag2)
	{
		Screen_Draw(g_TextureBlue, 850.0f, 5.0f, 360.0f, 50.0f, 0, 0, 1000, 200);
	}

	char Buf[64];
	sprintf(Buf, "frame=%d", g_Current.Vdata_tail);
	//DebugFont_Draw(900.0f, 50.0f, Buf);
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

Player GetPlayer(void)
{
	return g_Player;
}

CollisionCircle* Get_PlayerCollision(void)
{
	return g_Player.collision;
}

// マップチップの辺の位置に座標を調整する
void SetPlayerMapPos(int contact_edge, float contact_pos)
{
	switch (contact_edge)
	{
	case LEFTEDGE:	//チップの左の辺に当たった時の処理
		g_Player.position.x = contact_pos - PLAYER_SIZE_X;
		break;
	case RIGHTEDGE:	//チップの右の辺に当たった時の処理
		g_Player.position.x = contact_pos;
		break;
	case TOPEDGE:	//チップの上の辺に当たった時の処理
		g_Player.position.y = contact_pos - PLAYER_SIZE_Y;
		g_Player.isJump = false;
		break;
	case BOTTOMEDGE://チップの下の辺に当たった時の処理
		g_Player.position.y = contact_pos;

		break;
	}
}

bool GetFlag(void)
{
	return flag5;
}