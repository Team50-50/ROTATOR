/*==============================================================================

	タイトル画面の制御[titile.cpp]

													Author : トウ ミンヨウ
													Date   :

==============================================================================*/
#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "fade.h"
#include "keylogger.h"
#include "Texture.h"
#include "controller.h"
#include "sound.h"

/*----------------------------------------------------------------------------------------
  グローバル変数
 ----------------------------------------------------------------------------------------*/
static int g_TextureTitle;
static int g_TextureTitleLogo;
static int sec;

/*-----------------------------------------------------------------------------------------
 関数定義
-------------------------------------------------------------------------------------------*/
void InitTitle(void)
{

	g_TextureTitle = Texture_SetTextureLoadFile("asset/title.jpg");

	Texture_Load();

	g_TextureTitleLogo = Texture_SetTextureLoadFile("asset/title_logo.png");

	Texture_Load();

	PlaySound(SOUND_LABEL_BGM000);
	sec = 0;
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
		if (sec == 0)
		{
			PlaySound(SOUND_LABEL_SE_TITLE);
			sec = 1;
		}
		
	}
	
}


void DrawTitle(void)
{

	// スプライトを描画
	Screen_Draw(g_TextureTitle, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0, 0, 1280, 720);

	// スプライトを描画
	Screen_Draw(g_TextureTitleLogo, (SCREEN_WIDTH - 400) / 2, 100, 371, 122,
		0, 0, 371, 122);

}