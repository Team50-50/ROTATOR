/*==============================================================================

	扉の制御[dore.cpp]

													Author : トウ ミンヨウ　& マコウチュウ
													Date   :


==============================================================================*/
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "dore.h"
#include "player.h"
#include "key.h"
#include "stage.h"
#include "camera.h"

/*-----------------------------------------------------------------------------------------
  グローバル変数
 -------------------------------------------------------------------------------------------*/
// 扉のテクスチャの読み込み
static int	g_DoreTexture;

// 扉の位置座標
Dore Dores[KEY_MAX];

// プレイヤーの鍵所持数
static int g_PlayerKeyPossession2;

/*-----------------------------------------------------------------------------------------
 関数定義
-------------------------------------------------------------------------------------------*/
void InitDore()
{

	// TEXの読み込み
	g_DoreTexture = Texture_SetTextureLoadFile("asset/dore.png");

	// 扉配列の初期化
	for (int i = 0; i < KEY_MAX; i++)
	{
		Dores[i].use = false;
		Dores[i].xy.x = 0;
		Dores[i].xy.y = 0;
	}

}


void UninitDore()
{

	//テクスチャの開放
	Texture_Release(&g_DoreTexture, 1);

}

void UpdateDore()
{

	// プレイヤーの鍵所持数を保存
	g_PlayerKeyPossession2 = GetPlayerKeyPossession();

}

void DrawDore()
{

	// 扉を描画
	for (int i = 0; i < DORE_MAX; i++)
	{
		if (Dores[i].use == true)
		{
			
		    Sprite_Draw(g_DoreTexture, Dores[i].xy.x, Dores[i].xy.y, DORE_SIZE_X, DORE_SIZE_Y,
				0, 0, 64, 64);
			
		}
	}

}

void SetDore(float x, float y)
{
	// 扉を配置
	for (int i = 0; i < KEY_MAX; i++)
	{
		if (Dores[i].use == false)
		{
			Dores[i].use = true;
			Dores[i].xy.x = x;
			Dores[i].xy.y = y;
			break;
		}
	}
}

void DelDore(int num)
{
	// 扉を削除
	Dores[num].use = false;
	Dores[num].xy.x = 0;
	Dores[num].xy.y = 0;

}

Dore* GetDores()
{
	// 扉の座標取得
	return Dores;
}