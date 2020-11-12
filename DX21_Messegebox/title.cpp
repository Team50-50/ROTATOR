
#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "fade.h"


void InitTitle(void)
{



}


void UninitTitle(void)
{



}


void UpdateTitle(void)
{

	if (GetKeyState(VK_SPACE) & 0x80)
	{
		SetFade(FADE_OUT, SCENE_SELECT_STAGE);
	}

}


void DrawTitle(void)
{

	// スプライトを描画

}