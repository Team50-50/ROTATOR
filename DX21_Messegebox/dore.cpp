#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "dore.h"
#include "player.h"
#include "key.h"
#include "stage.h"
#include "camera.h"


// ���̃e�N�X�`���̓ǂݍ���
static int	g_DoreTexture;

// ���̈ʒu���W
Dore Dores[KEY_MAX];

// �v���C���[�̌�������
static int g_PlayerKeyPossession2;


void InitDore()
{

	// TEX�̓ǂݍ���
	g_DoreTexture = Texture_SetTextureLoadFile("asset/dore.png");

	// ���z��̏�����
	for (int i = 0; i < KEY_MAX; i++)
	{
		Dores[i].use = false;
		Dores[i].xy.x = 0;
		Dores[i].xy.y = 0;
	}

}


void UninitDore()
{

	//�e�N�X�`���̊J��
	Texture_Release(&g_DoreTexture, 1);

}

void UpdateDore()
{

	// �v���C���[�̌���������ۑ�
	g_PlayerKeyPossession2 = GetPlayerKeyPossession();

}

void DrawDore()
{

	// ����`��
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
	
	Dores[num].use = false;
	Dores[num].xy.x = 0;
	Dores[num].xy.y = 0;

}

Dore* GetDores()
{
	return Dores;
}