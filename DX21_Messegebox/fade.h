#pragma once

// �t�F�[�h�̏��
enum
{
	FADE_NONE = 0,		// �����Ȃ����
	FADE_IN,			// �t�F�[�h�C������
	FADE_OUT,			// �t�F�[�h�A�E�g����
	FADE_MAX
};


void InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

// Fade�����t���̃V�[���؂�ւ��֐�
void SetFade(int fade, int nextScene);
