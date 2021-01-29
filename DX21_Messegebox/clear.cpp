/*==============================================================================

	クリア画面の制御[clear.cpp]

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
static int g_TextureChear;
//static int g_TextureTitleLogo;
static int sec;

/*-----------------------------------------------------------------------------------------
 関数定義
-------------------------------------------------------------------------------------------*/
void InitClear(void)
{

	g_TextureChear = Texture_SetTextureLoadFile("asset/Clear.png");

	Texture_Load();

	PlaySound(SOUND_LABEL_SE_CLEARX);
	sec = 0;
}


void UninitClear(void)
{

	Texture_Release(&g_TextureChear, 1);
	
}


void UpdateClear(void)
{
	if (Keylogger_Press(KL_JUMP) || JoystickPress(ButtonB))
	{
		
		SetFade(FADE_OUT, SCENE_TITLE);
		
	}
	
}


void DrawClear(void)
{

	// スプライトを描画
	Screen_Draw(g_TextureChear, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0, 0, 1280, 720);

	//// スプライトを描画
	//Screen_Draw(g_TextureTitleLogo, (SCREEN_WIDTH - 400) / 2, 100, 371, 122,
	//	0, 0, 371, 122);

}