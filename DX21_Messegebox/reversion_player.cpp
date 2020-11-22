#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "player.h"
#include "revesion_player.h"
#include "directinput.h"
#include "camera.h"
#include "data_control.h"

/*-----------------------------------------------------------------------------------------
 �O���[�o���ϐ�
-------------------------------------------------------------------------------------------*/
static int g_TextureVPlayer = TEXTURE_INVALID_ID;
static int g_TextureVPlayer2 = TEXTURE_INVALID_ID;
//VPlayer g_VPlayer[VPLAYER_MAX];
ReversionPlayer g_ReversionPlayer[2];
static int frame = 0;

void ReversionPlayer_Initialize(void)
{
	g_TextureVPlayer = Texture_SetTextureLoadFile("asset/player.png");
	g_TextureVPlayer2 = Texture_SetTextureLoadFile("asset/player.png");
	
}


void ReversionPlayer_Finalize(void)
{
	Texture_Release(&g_TextureVPlayer, 1);
	Texture_Release(&g_TextureVPlayer2, 1);
}


void ReversionPlayer_Update(void)
{
	frame++;
	DataStorage prevData = GetPrev();
	DataStorage debugData = GetDebug();

	//�v���C���[�O�̃t���[����position�f�[�^���X�^�b�N�̈悩��擾����
	for (int i = 0; i < prevData.data_tail; i++)
	{
		if (GetKeyState('B') & 0x80)
		{
			//B�L�[��������������A�v���C���[�O�̃t���[����position�f�[�^��1�t���[�����A���z�v���C���[�ɑ������
			//B�L�[�𗣂�����A���z�v���C���[�����̏�Ŏ~�܂�
			g_ReversionPlayer[0].position = prevData.positionData[i];
		}

	}
	for (int i = 0; i < debugData.data_tail; i++)
	{
		g_ReversionPlayer[1].position = debugData.positionData[i];
	}
	if (frame >= 360)
	{
		g_ReversionPlayer[1].enable = true;
	}
	if (frame >= 360 && GetKeyState('B') & 0x80)
	{
		g_ReversionPlayer[0].enable = true;
	}
}


void ReversionPlayer_Draw(void)
{
	//B�������Ƌt�s�L�����N�^�[��`��
	if (g_ReversionPlayer[0].enable)
	{
		Sprite_Draw(g_TextureVPlayer, WorldToScreen(g_ReversionPlayer[0].position).x,
			WorldToScreen(g_ReversionPlayer[0].position).y,
			PLAYER_SIZE_X, PLAYER_SIZE_Y, 0, 0, 64, 128);
	}
	if (g_ReversionPlayer[1].enable)
	{
		Sprite_Draw(g_TextureVPlayer, WorldToScreen(g_ReversionPlayer[1].position).x,
			WorldToScreen(g_ReversionPlayer[1].position).y,
			PLAYER_SIZE_X, PLAYER_SIZE_Y, 0, 0, 64, 128, D3DCOLOR_RGBA(255, 0, 255, 110));
	}
}

////�t�s�L�����N�^�[�̈ʒu�����擾
//ReversionPlayer GetVPlayer(void)
//{
//	return g_ReversionPlayer;
//}


