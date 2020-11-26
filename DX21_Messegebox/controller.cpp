/*=======================================================================================

	 �R���g���[���[����[controller.cpp]
												author:mgc
												date:2020/11/26
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#include"directinput.h"
#include"controller.h"
#include <d3dx9.h>

 /*-----------------------------------------------------------------------------------------
  �O���[�o���ϐ�
 ------------------------------------------------------------------------------------------*/
static ButtonState g_JoyStates[ButtonKindMax];


/*-----------------------------------------------------------------------------------------
   �֐���`
 -------------------------------------------------------------------------------------------*/
void InitController(void)
{
	// ���͏��̏�����
	for (int i = 0; i < ButtonKindMax; i++)
	{
		g_JoyStates[i] = JoyStateNone;
	}
}

void UpdateController(void)
{
	LPDIRECTINPUTDEVICE8 gamepadDevice = GamePad_GetDevice();

	if (gamepadDevice == nullptr)
	{
		return;
	}

	DIJOYSTATE pad_data;

	// �f�o�C�X�擾
	HRESULT hr = gamepadDevice->GetDeviceState(sizeof(DIJOYSTATE), &pad_data);
	if (FAILED(hr))
	{
		// �ēx����J�n
		if (FAILED(gamepadDevice->Acquire()))
		{
			for (int i = 0; i < ButtonKindMax; i++)
			{
				g_JoyStates[i] = JoyStateNone;
			}
			gamepadDevice->Poll();
		}
		return;
	}

	bool is_push[ButtonKindMax];

	//==================================================================
	// ���X�e�B�b�N�̐ݒ�
	//==================================================================
	//�A�i���O�X�e�B�b�N�̍��E�̏�Ԃ� -1000�`+1000

	int unresponsive_range = 200;

	if (pad_data.lX < -unresponsive_range)
	{
		is_push[LStickLeft] = true;
	}
	else if (pad_data.lX > unresponsive_range)
	{
		is_push[LStickRight] = true;
	}

	if (pad_data.lY < -unresponsive_range)
	{
		is_push[LStickUP] = true;
	}
	else if (pad_data.lY > unresponsive_range)
	{
		is_push[LStickDown] = true;
	}

	//==================================================================
	// �E�X�e�B�b�N�̐ݒ�
	//==================================================================
	if (pad_data.lZ < -unresponsive_range)
	{
		is_push[RStickLeft] = true;
	}
	else if (pad_data.lZ > unresponsive_range)
	{
		is_push[RStickRight] = true;
	}

	if (pad_data.lRz < -unresponsive_range)
	{
		is_push[RStickUP] = true;
	}
	else if (pad_data.lRz > unresponsive_range)
	{
		is_push[RStickDown] = true;
	}


	//==================================================================
	// �\���L�[�̐ݒ�
	//==================================================================
	if (pad_data.rgdwPOV[0] != 0xFFFFFFFF)
	{
		float rad = D3DXToRadian((pad_data.rgdwPOV[0] / 100.0f));

		float x = sinf(rad);
		float y = cosf(rad);

		if (x < -0.01f)
		{
			is_push[LeftButton] = true;
		}
		else if (x > 0.01f)
		{
			is_push[RightButton] = true;
		}

		if (y > 0.01f)
		{
			is_push[UpButton] = true;
		}
		else if (y < -0.01f)
		{
			is_push[DownButton] = true;
		}
	}



	//==================================================================
	// �{�^���̐ݒ�
	//==================================================================
	for (int i = 0; i < 32; i++)
	{
		if (!(pad_data.rgbButtons[i] & 0x80))
		{
			continue;
		}

		switch (i)
		{
		case 0:
			is_push[ButtonY] = true;
			break;
		case 1:
			is_push[ButtonB] = true;
			break;
		case 2:
			is_push[ButtonA] = true;
			break;
		case 3:
			is_push[ButtonX] = true;
			break;
		case 4:
			is_push[ButtonLB] = true;
			break;
		case 5:
			is_push[ButtonRB] = true;
			break;
		case 6:
			is_push[ButtonLT] = true;
			break;
		case 7:
			is_push[ButtonRT] = true;
			break;
		case 8:
			is_push[Button_BACK] = true;
			break;
		case 9:
			is_push[Button_START] = true;
			break;
		}
	}


	// ���͏�񂩂�{�^���̏�Ԃ��X�V����
	for (int i = 0; i < ButtonKindMax; i++)
	{
		if (is_push[i] == true)
		{
			if (g_JoyStates[i] == JoyStateNone)
			{
				g_JoyStates[i] = JoyStateDown;
			}
			else
			{
				g_JoyStates[i] = JoyStatePush;
			}
		}
		else
		{
			if (g_JoyStates[i] == JoyStatePush)
			{
				g_JoyStates[i] = JoyStateUp;
			}
			else
			{
				g_JoyStates[i] = JoyStateNone;
			}
		}
	}
}

bool JoystickPress(ButtonKind button)
{
	if (g_JoyStates[button] == JoyStatePush)
	{
		return true;
	}

	return false;
}

bool JoystickRelease(ButtonKind button)
{
	if (g_JoyStates[button] == JoyStateUp)
	{
		return true;
	}

	return false;
}

bool JoystickTrigger(ButtonKind button)
{
	if (g_JoyStates[button] == JoyStateDown)
	{
		return true;
	}

	return false;
}
