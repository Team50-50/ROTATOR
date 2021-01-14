
#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "fade.h"

#define	FADE_RATE	(5)		// �t�F�[�h�W��(���邭�܂��͈Â��Ȃ鑬�x)

static int g_TextureFade = TEXTURE_INVALID_ID;

int			g_Fade = FADE_IN;	// �t�F�[�h�̏��
int			g_NextScene;		// ����Scene
D3DCOLOR		g_Color;			// �t�F�[�h�̃J���[�i���l�j

int       apha;

void InitFade(void)
{
	g_TextureFade = Texture_SetTextureLoadFile("asset/fade_black.png");	//Fade�摜

	g_Fade = FADE_IN;
	g_Color = D3DCOLOR_RGBA(  255, 255, 255, 255);
	//                         R    G    B    ��

	apha = 255;
}


void UninitFade(void)
{

	Texture_Release(&g_TextureFade,1);

}


void UpdateFade(void)
{
	if (g_Fade != FADE_NONE)
	{// �t�F�[�h������
		if (g_Fade == FADE_OUT)
		{// �t�F�[�h�A�E�g����
			apha += FADE_RATE;
			g_Color = D3DCOLOR_RGBA(255, 255, 255, (int)apha);		// ���l�����Z���ĉ�ʂ������Ă���
			if (apha >= 255)
			{
				// �t�F�[�h�C�������ɐ؂�ւ�
				apha = 255;
				SetFade(FADE_IN, g_NextScene);

				// ���[�h��ݒ�
				SetScene(g_NextScene);
			}

		}
		else if (g_Fade == FADE_IN)
		{// �t�F�[�h�C������
			apha -= FADE_RATE;
			g_Color = D3DCOLOR_RGBA(255, 255, 255, (int)apha);		// ���l�����Z���ĉ�ʂ𕂂��オ�点��
			if (apha <= 0)
			{
				// �t�F�[�h�����I��
				apha = 0;
				SetFade(FADE_NONE, g_NextScene);
			}

		}
	}

}


void DrawFade(void)
{
	if (g_Fade == FADE_NONE) return;	// �t�F�[�h���Ȃ��̂Ȃ�`�悵�Ȃ�

	//SetTexture(NULL);	// �e�N�X�`���[���g��Ȃ�

	// �X�v���C�g��`��
	Sprite_Draw(g_TextureFade, -SCREEN_WIDTH * 0.5, -SCREEN_HEIGHT * 0.5, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		g_Color);

	/*Sprite_Draw(NULL, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		g_Color);*/

	/*DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		g_Color);*/

}

//=============================================================================
// �t�F�[�h�̏�Ԑݒ�
//=============================================================================
void SetFade(int fade, int nextScene)
{
	g_Fade = fade;
	g_NextScene = nextScene;
}