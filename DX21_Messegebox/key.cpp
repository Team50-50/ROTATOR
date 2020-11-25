#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "key.h"
#include "player.h"
#include "stage.h"
#include "camera.h"


//ブロックのテクスチャの読み込み
static int	g_KeyTexture;

// 鍵の位置座標
Key Keys[KEY_MAX];

// プレイヤーの位置
D3DXVECTOR2 PlayerPosition;

// プレイヤーの鍵所持数
static int g_PlayerKeyPossession;

// (Draw用)プレイヤーの鍵を使った数
static int g_D_PlayerUsedKey;


void InitKey()
{

	// TEXの読み込み
	g_KeyTexture = Texture_SetTextureLoadFile("asset/key.png");

	// 鍵配列の初期化
	for (int i = 0; i < KEY_MAX; i++)
	{
		Keys[i].use = false;
		Keys[i].InPlayer = false;
		Keys[i].xy.x = 0;
		Keys[i].xy.y = 0;
	}

	g_PlayerKeyPossession = 0;

	//プレイヤーの現在位置を取得
	PlayerPosition = GetPlayerPosition();

	g_D_PlayerUsedKey = 0;

}


void UninitKey()
{

	//テクスチャの開放
	Texture_Release(&g_KeyTexture, 1);

}

void UpdateKey()
{
	
	// プレイヤー位置座標を保存
	PlayerPosition = GetPlayerPosition();

	// プレイヤーが鍵を触ったかどうか
	for (int i = 0; i < KEY_MAX; i++)
	{
		if (Collision_CircleAndCircleHit(&GamePlayer_GetCollision(), &GameKey_GetCollision(i)))
		{

			Keys[i].InPlayer = true;
			Keys[i].xy.x = 0;
			Keys[i].xy.y = 0;
			g_PlayerKeyPossession ++;

		}
	}
	/*for (int i = 0; i < KEY_MAX; i++)
	{
		if (Key[i].use == true)
		{
			if (WorldToScreen(Key[i].xy).x + KEY_SIZE_X > WorldToScreen(PlayerPosition).x &&
				WorldToScreen(Key[i].xy).x              < WorldToScreen(PlayerPosition).x + PLAYER_SIZE_X) {

				if (WorldToScreen(Key[i].xy).y + KEY_SIZE_Y > WorldToScreen(PlayerPosition).y &&
					WorldToScreen(Key[i].xy).y              < WorldToScreen(PlayerPosition).y + PLAYER_SIZE_Y) {

					Key[i].InPlayer == true;
					g_PlayerKeyPossession ++;

				}
			}
		}
	}*/

}

void DrawKey()
{
	g_D_PlayerUsedKey = GetPlayerUseKey();


	// 鍵を描画
	for (int i = 0; i < KEY_MAX; i++)
	{
		if (Keys[i].use == true)
		{
			if (Keys[i].InPlayer == true)
			{
				for (int i = 0; i < g_PlayerKeyPossession - g_D_PlayerUsedKey; i++)
				{
					Sprite_Draw(g_KeyTexture, 200 + (i * 10), 200, KEY_SIZE_X, KEY_SIZE_Y,
						0, 0, 10, 10);
				}
			}
			else
			{
				Sprite_Draw(g_KeyTexture, WorldToScreen(Keys[i].xy).x, WorldToScreen(Keys[i].xy).y, KEY_SIZE_X, KEY_SIZE_Y,
					0, 0, 10, 10);
			}
		}
	}

}

void SetKey(float x, float y)
{
	for (int i = 0; i < KEY_MAX; i++)
	{
		if (Keys[i].use == false)
		{
			Keys[i].use = true;
			Keys[i].InPlayer = false;
			Keys[i].xy.x = x;
			Keys[i].xy.y = y;
			break;
		}
	}
}

CollisionCircle GameKey_GetCollision(int index)
{
	CollisionCircle c = {
		D3DXVECTOR2(
			Keys[index].xy.x + KEY_SIZE_X * 0.5f,
			Keys[index].xy.x + KEY_SIZE_Y * 0.5f
		),
		KEY_SIZE_X * 0.5f
	};

	return c;
}

Key* GetKeys()
{
	return Keys;
}

int GetPlayerKeyPossession()
{
	return g_PlayerKeyPossession;
}