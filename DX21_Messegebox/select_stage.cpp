
#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "fade.h"


void InitSelectStage(void)
{



}


void UninitSelectStage(void)
{



}


void UpdateSelectStage(void)
{

	if (GetKeyState(VK_SPACE) & 0x80)
	{
		SetFade(FADE_OUT, SCENE_GAME);
	}

}


void DrawSelectStage(void)
{

	// スプライトを描画

}