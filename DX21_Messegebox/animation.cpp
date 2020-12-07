/*=======================================================================================

	 �A�j���[�V��������[animation.cpp]
												author:mgc
												date:2020/12/03
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#include"animation.h"

 //�A�j���[�V�����̏�����
 //
 //�����Fanimation	...Animation�\���̂̃|�C���^
 //
 //		type		...�A�j���[�V�����̎��
 //		tWidth		...�e�N�X�`���̕�
 //		tHeight		...�e�N�X�`���̍���
 //		aWsize		...���̃A�j���[�V�����̃p�^�[����
 //		aHsize		...�c�̃A�j���[�V�����̃p�^�[����
 //		aMax		...�A�j���[�V�����̃p�^�[����
 //
void InitAnimations(Animation *animation, int type, int tWidth, int tHeight, int aWsize, int aHsize, int aMax)
{
	animation[type].frame = 0;
	animation[type].animNo = 0;
	animation[type].texWidth = tWidth;
	animation[type].texHeight = tHeight;
	animation[type].animWSize = aWsize;
	animation[type].animHSize = aHsize;
	animation[type].animMax = aMax;
	animation[type].tcw = tWidth / aWsize;
	animation[type].tch = tHeight / aHsize;

	animation[type].tcx = 0;
	animation[type].tcy = 0;
	animation[type].isUse = false;

}


//�A�j���[�V�����̍X�V����
//
//�����Fanimation	...Animation�\���̂̃|�C���^
//
//		type		...�A�j���[�V�����̎��
//		frame		...�A�j���[�V�����X�V�̑���
//				frame�����傫����΁A�X�V���x���x���Ȃ�
//
void UpdateAnimations(Animation* animation, int type, int frame)
{
	animation[type].frame++;

	if (animation[type].frame > frame)
	{
		animation[type].frame = 0;
		animation[type].animNo = (animation[type].animNo + 1) % animation[type].animMax;
	}

	animation[type].tcx = (animation[type].animNo % animation[type].animWSize) * animation[type].tcw;
	animation[type].tcy = (animation[type].animNo / animation[type].animWSize) * animation[type].tch;

}
