
#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "fade.h"
#include "keylogger.h"

static int g_TextureTitle;


void InitTitle(void)
{

	g_TextureTitle = Texture_SetTextureLoadFile("asset/title(kari).png");

	Texture_SetTextureLoadFile("asset/stageC(kari).png");
	Texture_SetTextureLoadFile("asset/player.png");
	Texture_SetTextureLoadFile("asset/HEW_CHARA_Aniamtion_run_renban.png");
	Texture_SetTextureLoadFile("asset/green.tga");
	Texture_SetTextureLoadFile("asset/red.tga");
	Texture_SetTextureLoadFile("asset/blue.tga");
	Texture_SetTextureLoadFile("asset/BG.png");
	Texture_SetTextureLoadFile("asset/testblock.jpg");
	Texture_SetTextureLoadFile("asset/block.png");
	Texture_SetTextureLoadFile("asset/key.png");
	Texture_SetTextureLoadFile("asset/dore.png");
	Texture_SetTextureLoadFile("asset/player.png");
	Texture_SetTextureLoadFile("asset/HEW_CHARA_Aniamtion_run_renban.png");
	Texture_SetTextureLoadFile("asset/bullet.png");
	Texture_SetTextureLoadFile("asset/Explosion_black.png");
	Texture_SetTextureLoadFile("asset/mapchip.png");
}


void UninitTitle(void)
{

	Texture_Release(&g_TextureTitle, 1);

}


void UpdateTitle(void)
{
	if (Keylogger_Press(KL_JUMP))
	{
		SetFade(FADE_OUT, SCENE_STAGECHOICE);
	}
}


void DrawTitle(void)
{

	// スプライトを描画
	Sprite_Draw(g_TextureTitle, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0, 0, 1920, 1080);

}