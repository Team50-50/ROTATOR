/*==============================================================================

	�w�i�̐���[bg.cpp]

													Author : �g�E �~�����E
													Date   :

==============================================================================*/
#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "camera.h"
#include "bg.h"
#include "map.h"
#include "stagechoice.h"

/*-----------------------------------------------------------------------------------------
  �O���[�o���ϐ�
 -------------------------------------------------------------------------------------------*/
static const char* TextureFileNames[] = {
	"asset/BG.png",
	"asset/messageImage_1610629813418.jpg",
	"asset/messageImage_1610629806617.jpg"
	
};

static const int TextureCnt = ARRAYSIZE(TextureFileNames);

//�u���b�N�̃e�N�X�`���̓ǂݍ���
static int	g_BGTexture[TextureCnt];

/*-----------------------------------------------------------------------------------------
 �֐���`
-------------------------------------------------------------------------------------------*/
void InitBG(void)
{

	for (int i = 0; i < TextureCnt; i++)
	{
		g_BGTexture[i] = Texture_SetTextureLoadFile(TextureFileNames[i]);
	}

}


void UninitBG(void)
{
	for (int i = 0; i < TextureCnt; i++)
	{
		Texture_Release(&g_BGTexture[i], 1);
	}

}


void DrawBG(void)
{

	// �X�v���C�g��`��
	Sprite_Draw(g_BGTexture[Getmap()], 0.0f, 0.0f, STAGE_WIDTH, STAGE_HEIGHT,
		0, 0, 1440, 960);

}