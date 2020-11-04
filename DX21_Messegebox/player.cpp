
#include "Main.h"
#include "texture.h"
#include "Sprite.h"

//プレイヤー大きさX
#define PLAYER_SIZE_X (100.0f)

//プレイヤー大きさY
#define PLAYER_SIZE_Y (100.0f)


//プレイヤーテクスチャー読み込み
static int	  g_PlayerTexture;

//プレイヤー位置情報
D3DXVECTOR2	  g_PlayerPosition;

//ジャンプ時の数値
float	j_kansei;

//地面にプレイヤーがいるかどうか？
bool on_ground;



void InitPlayer()
{

	g_PlayerTexture = Texture_SetTextureLoadFile("asset/player_test.png");


	g_PlayerPosition.x = 520;
	g_PlayerPosition.y = 400;

	j_kansei = 0;

}


void UninitPlayer()
{

	Texture_Release(&g_PlayerTexture,1);

}


void UpdatePlayer()
{
	float stick_x = 0.0f;
	float stick_y = 0.0f;


	//Aを押して左に移動
	if (GetKeyState('A') & 0x80)
	{
		stick_x = -0.5f;

	}
	
	//Dを押して左に移動
	if (GetKeyState('D') & 0x80)
	{
		stick_x = 0.5f;

	}
	
	//プレイヤー左右移動計算
	g_PlayerPosition.x += stick_x * 20.0f;


	//ジャンプ
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		if (on_ground == true)
		{
			j_kansei = 30.0f;
		}

	}

	if (!(j_kansei == 0))
	{
		j_kansei -= 1.0f;

		if (j_kansei <= 0)
		{
			j_kansei = 0;
		}
	}

	// 重力
	g_PlayerPosition.y += 10;

	g_PlayerPosition.y -= j_kansei;

	if (!(g_PlayerPosition.y == 500 - PLAYER_SIZE_Y))
	{
		on_ground = false;
	}

	

	


	if (g_PlayerPosition.x < 0)
		g_PlayerPosition.x = 0;

	if (g_PlayerPosition.x > 1280 - PLAYER_SIZE_X)
		g_PlayerPosition.x = 1280 - PLAYER_SIZE_X;

	if (g_PlayerPosition.y < 0 - PLAYER_SIZE_Y )
		g_PlayerPosition.y = 0 - PLAYER_SIZE_Y ;

	if (g_PlayerPosition.y > 500 - PLAYER_SIZE_Y)
	{
		on_ground = true;
		g_PlayerPosition.y = 500 - PLAYER_SIZE_Y;
	}
		
}


void DrawPlayer()
{

	Sprite_Draw(g_PlayerTexture,g_PlayerPosition.x, g_PlayerPosition.y, PLAYER_SIZE_X, PLAYER_SIZE_Y,
	 0, 0, 250, 160);
}


D3DXVECTOR2 GetPlayerPosition()
{
	return g_PlayerPosition;
}