
#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "camera.h"
#include "bg.h"

static int g_TextureBG;

void InitBG(void)
{

	g_TextureBG = Texture_SetTextureLoadFile("asset/BG.png");	//”wŒi‰æ‘œ

}


void UninitBG(void)
{

	Texture_Release(&g_TextureBG, 1);

}


void DrawBG(void)
{

	// ƒXƒvƒ‰ƒCƒg‚ð•`‰æ
	Sprite_Draw(g_TextureBG, 0.0f, 0.0f, STAGE_WIDTH, STAGE_HEIGHT,
		0, 0, 1440, 960);

}