
#include "Main.h"
#include "texture.h"
#include "Sprite.h"

//�v���C���[�傫��X
#define PLAYER_SIZE_X (100.0f)

//�v���C���[�傫��Y
#define PLAYER_SIZE_Y (100.0f)


//�v���C���[�e�N�X�`���[�ǂݍ���
static int	  g_PlayerTexture;

//�v���C���[�ʒu���
D3DXVECTOR2	  g_PlayerPosition;

//�W�����v���̐��l
float	j_kansei;

//�n�ʂɃv���C���[�����邩�ǂ����H
bool on_ground;



void InitPlayer()
{

	g_PlayerTexture = Texture_SetTextureLoadFile("asset/player_test.png");


	g_PlayerPosition.x = 400;
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


	//A�������č��Ɉړ�
	if (GetKeyState('A') & 0x80)
	{
		stick_x = -0.5f;

	}
	
	//D�������č��Ɉړ�
	if (GetKeyState('D') & 0x80)
	{
		stick_x = 0.5f;

	}
	
	//�v���C���[���E�ړ��v�Z
	g_PlayerPosition.x += stick_x * 20.0f;


	//�W�����v
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

	// �d��
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