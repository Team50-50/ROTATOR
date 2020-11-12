
#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "player.h"
#include "block.h"
#include "directinput.h"

//�v���C���[�e�N�X�`���[�ǂݍ���
static int	g_PlayerTexture;

//�u���b�N�ʒu
D3DXVECTOR2	BlockPosition[BLOCK_MAX];

//�v���C���[�ʒu���
D3DXVECTOR2	g_PlayerPosition;

//�v���C���[����ʂɕ`�悷��ʒu
D3DXVECTOR2	Draw_PlayerPosition;


static Queue g_qCurrent;
static Queue g_qPrev;
static Stack g_sCurrent;
static Stack g_sPrev;

//�W�����v���̈ړ���
float	jump_amount;

//�n�ʂɃv���C���[�����邩�ǂ����H
bool on_ground;

void InitPlayer()
{
	//�v���C���[�̃e�N�X�`���ǂݍ���
	g_PlayerTexture = Texture_SetTextureLoadFile("asset/player.png");

	//�v���C���[�̏����ʒu�̒�`
	g_PlayerPosition.x = ((SCREEN_WIDTH - PLAYER_SIZE_X) / 2);
	g_PlayerPosition.y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10);

	//�W�����v���̈ړ��ʂ�������
	jump_amount = 0;
	
}


void UninitPlayer()
{
	//�e�N�X�`���̉��
	Texture_Release(&g_PlayerTexture,1);

}


void UpdatePlayer()
{

	//A�������č��Ɉړ�
	if (GetKeyState('A') & 0x80)
	{
		g_PlayerPosition.x -= 10.0f;//�ړ���

	}
	
	//D�������č��Ɉړ�
	if (GetKeyState('D') & 0x80)
	{
		g_PlayerPosition.x += 10.0f;//�ړ���

	}
	
	//�W�����v
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		if (on_ground == true)
		{
			jump_amount = 16.0f;//�W�����v��
		}

	}
	//===========================================
	//�R���g���[���[
	//������������������������������������������
	if (IsButtonPush(LeftButton))
	{
		g_PlayerPosition.x -= 10.0f;//�ړ���
	}
	if (IsButtonPush(RightButton))
	{
		g_PlayerPosition.x += 10.0f;//�ړ���
	}
	if (IsButtonDown(ButtonB) || IsButtonPush(ButtonX) || IsButtonUp(ButtonY))
	{
		if (on_ground == true)
		{
			jump_amount = 16.0f;//�W�����v��
		}
	}
	
	//�d�͂���ɔ���������
	jump_amount -= 1.0f;

	//�v���C���[��������
	g_PlayerPosition.y -= jump_amount;
	
	//�u���b�N�̈ʒu���W���擾
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		BlockPosition[i] = GetBlockPosition(i);
	}

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_PlayerPosition.x + PLAYER_SIZE_X > BlockPosition[i].x && g_PlayerPosition.x < BlockPosition[i].x + BLOCK_SIZE_X)
		{
			if (g_PlayerPosition.y >= BlockPosition[i].y - PLAYER_SIZE_Y)
			{
				on_ground = true;
				g_PlayerPosition.y = BlockPosition[i].y - PLAYER_SIZE_Y;
				jump_amount = 0;
			}
			else
			{
				on_ground = false;
			}
		}
		
	}

	//================================================================
	//�X�^�b�N�\���ŁA�v���C���[��position�f�[�^�̍X�V�������s��
	//================================================================
	if (!(GetKeyState('B') & 0x80))
	{
		//�t�s���ĂȂ��Ƃ��Ƀv���C���[�̃|�W�V�������L�^
		push(&g_sCurrent, g_PlayerPosition);
	}
	if (GetKeyState('B') & 0x80)
	{
		//B�L�[��������������A���̃t���[���̃f�[�^�z��̖����̃v���C���[position�����o��
		//�O�̃t���[���̃v���C���[position�f�[�^�Ƃ��ċL�^����
		push(&g_sPrev, pop(&g_sCurrent));
	}

	//===========================================
	//�R���g���[���[
	//������������������������������������������
	if (IsButtonPush(ButtonRT))
	{
		push(&g_sCurrent, g_PlayerPosition);
	}
	if (IsButtonPush(ButtonLT))
	{
		push(&g_sPrev, pop(&g_sCurrent));
	}
	
}


void DrawPlayer()
{
	
	//�v���C���[����ʒ����ɕ`��
	Sprite_Draw(g_PlayerTexture, ((SCREEN_WIDTH - PLAYER_SIZE_X) / 2), ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10), PLAYER_SIZE_X, PLAYER_SIZE_Y,
	 0, 0, PLAYER_SIZE_X, PLAYER_SIZE_Y);
	

}


D3DXVECTOR2 GetPlayerPosition()
{
	return g_PlayerPosition;
}

//PUSH...position�f�[�^���X�^�b�N�ɒǉ�����
void push(Stack* stack, D3DXVECTOR2 playerPosition)
{
	if (stack->recordFrame > FRAME_MAX)
	{
		return;
	}
	stack->position_Data[stack->recordFrame] = playerPosition;

	stack->recordFrame++;
}

//POP...position�f�[�^���X�^�b�N������o���A����Ō� PUSH ���� position�f�[�^��������o��
D3DXVECTOR2 pop(Stack* stack)
{
	D3DXVECTOR2 ret;

	//�f�[�^���X�^�b�N����S�����o���ꂽ�ꍇ (#�o�O�̌���#)
	if (stack->recordFrame == 0)
	{
		return stack->position_Data[stack->recordFrame];
	}

	ret = stack->position_Data[stack->recordFrame - 1];

	stack->recordFrame--;

	return ret;
}

Stack GetstackPrev(void)
{
	return g_sPrev;
}

Stack GetstackCurrent(void)
{
	return g_sCurrent;
}