/*==============================================================================

	�^�C�g����ʂ̐���[titile.cpp]

													Author : �g�E �~�����E
													Date   :

==============================================================================*/
#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "fade.h"
#include "keylogger.h"
#include "Texture.h"
#include "controller.h"

/*----------------------------------------------------------------------------------------
  �O���[�o���ϐ�
 ----------------------------------------------------------------------------------------*/
static int g_TextureTitle;

/*-----------------------------------------------------------------------------------------
 �֐���`
-------------------------------------------------------------------------------------------*/
void InitTitle(void)
{

	g_TextureTitle = Texture_SetTextureLoadFile("asset/title(kari).png");

	Texture_Load();

	
}


void UninitTitle(void)
{

	Texture_Release(&g_TextureTitle, 1);

}


void UpdateTitle(void)
{
	if (Keylogger_Press(KL_JUMP) || JoystickPress(ButtonB))
	{
		SetFade(FADE_OUT, SCENE_STAGECHOICE);
	}
}


void DrawTitle(void)
{

	// �X�v���C�g��`��
	Screen_Draw(g_TextureTitle, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0, 0, 1920, 1080);

}