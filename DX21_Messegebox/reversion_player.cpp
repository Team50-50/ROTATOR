#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "player.h"
#include "revesion_player.h"

static int g_TextureVPlayer = TEXTURE_INVALID_ID;
//VPlayer g_VPlayer[VPLAYER_MAX];
ReversionPlayer g_ReversionPlayer;

//�u���b�N�̕`����W
D3DXVECTOR2	g_ReversionPlayer_DrawPositition;

//�v���C���[�����݂�����W
D3DXVECTOR2	Current_PlayerPositionR;

//�v���C���[���X�^�[�g�������ɂ������W
D3DXVECTOR2	Start_PlayerPositionR;

void ReversionPlayer_Initialize(void)
{
	g_TextureVPlayer = Texture_SetTextureLoadFile("asset/player.png");

	//�v���C���[�̌��݈ʒu���擾
	Current_PlayerPositionR = GetPlayerPosition();

	//�v���C���[�̃X�^�[�g�ʒu��ۑ�
	Start_PlayerPositionR.x = Current_PlayerPositionR.x;
	Start_PlayerPositionR.y = Current_PlayerPositionR.y;
}


void ReversionPlayer_Finalize(void)
{
	Texture_Release(&g_TextureVPlayer, 1);
}


void ReversionPlayer_Update(void)
{
	//Queue q = GetqPrev();
	Stack prev_stack = GetstackPrev();

	//�v���C���[�O�̃t���[����position�f�[�^���X�^�b�N�̈悩��擾����
	for (int i = 0; i < prev_stack.recordFrame; i++)
	{
		if (GetKeyState('B') & 0x80)
		{
			//B�L�[��������������A�v���C���[�O�̃t���[����position�f�[�^��1�t���[�����A���z�v���C���[�ɑ������
			//B�L�[�𗣂�����A���z�v���C���[�����̏�Ŏ~�܂�
			g_ReversionPlayer.position = prev_stack.position_Data[i];
		}

	}

	//�v���C���[�̌��݈ʒu��ǂݍ���
	Current_PlayerPositionR = GetPlayerPosition();

	//�Đ��L�����N�^�[�̕`��ʒu���X�V
	g_ReversionPlayer_DrawPositition.x = g_ReversionPlayer.position.x - (Current_PlayerPositionR.x - Start_PlayerPositionR.x);
	g_ReversionPlayer_DrawPositition.y = g_ReversionPlayer.position.y - (Current_PlayerPositionR.y - Start_PlayerPositionR.y);;

}


void ReversionPlayer_Draw(void)
{
	//B�������Ƌt�s�L�����N�^�[��`��
	if (GetKeyState('B') & 0x80)
	{
		Sprite_Draw(g_TextureVPlayer, g_ReversionPlayer_DrawPositition.x, g_ReversionPlayer_DrawPositition.y,
			PLAYER_SIZE_X, PLAYER_SIZE_Y, 0, 0, 64, 128);
	}

}

//�t�s�L�����N�^�[�̈ʒu�����擾
ReversionPlayer GetVPlayer(void)
{
	return g_ReversionPlayer;
}


