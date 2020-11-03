
#include "Main.h"
#include "texture.h"
#include "Sprite.h"


static int	  g_PlayerTexture;

D3DXVECTOR2	  g_PlayerPosition;

static int	  j_kansei;

bool on_ground;

int player_A_t;

void InitPlayer()
{

	g_PlayerTexture = Texture_SetTextureLoadFile("asset/player_test.png");

	//PlayBGM(BGM_01);

	g_PlayerPosition.x = 800;
	g_PlayerPosition.y = 400;

	j_kansei = 0;

	player_A_t = 0;
}


void UninitPlayer()
{

	Texture_Release(&g_PlayerTexture,1);

	//StopBGM();
}


void UpdatePlayer()
{
	float stick_x = 0.0f;
	float stick_y = 0.0f;


	// 左右移動
	if (GetKeyState(VK_LEFT) & 0x80)
	{
		stick_x = -0.5f;

		player_A_t = 1;

	}
	

	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		stick_x = 0.5f;

	}
	

	g_PlayerPosition.x += stick_x * 20.0f;

	// ジャンプ
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		if (on_ground == true)
		{
			j_kansei = 100;
		}

	}

	if (!(j_kansei == 0))
	{
		j_kansei -= 1;

		if (j_kansei <= 0)
		{
			j_kansei = 0;
		}
	}

	if (!(g_PlayerPosition.y = 500 - 100))
	{
		on_ground = false;
	}

	g_PlayerPosition.y -= j_kansei;

	// 重力
	g_PlayerPosition.y += 10;


	if (g_PlayerPosition.x < 0)
		g_PlayerPosition.x = 0;

	if (g_PlayerPosition.x > 1280 - 100)
		g_PlayerPosition.x = 1280 - 100;

	if (g_PlayerPosition.y < 0 - 100 )
		g_PlayerPosition.y = 0 - 100 ;

	if (g_PlayerPosition.y > 500 - 100)
	{
		on_ground = true;
		g_PlayerPosition.y = 500 - 100;
	}
		
}


void DrawPlayer()
{

	Sprite_Draw(g_PlayerTexture,g_PlayerPosition.x, g_PlayerPosition.y, 100.0f, 100.0f,
	 0, 0, 250, 160);
}


D3DXVECTOR2 GetPlayerPosition()
{
	return g_PlayerPosition;
}