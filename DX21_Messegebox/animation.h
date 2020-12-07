/*=======================================================================================

	 �A�j���[�V��������[animation.h]
												author:mgc
												date:2020/12/03
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef ANIMATION_H_
#define ANIMATION_H_

typedef struct Animation_tag
{
	int frame;
	int texWidth;
	int texHeight;
	int animNo;
	int animWSize;
	int animHSize;
	int animMax;
	int tcw;
	int tch;
	int tcx;
	int tcy;

	bool isUse;

}Animation;


//�A�j���[�V�����̎��
enum {
	IDLE,
	WALKING,
	TYPE_MAX
};

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
void InitAnimations(Animation* animation, int type, int tWidth, int tHeight, int aWsize, int aHsize, int aMax);


//�A�j���[�V�����̍X�V����
//
//�����Fanimation	...Animation�\���̂̃|�C���^
//
//		motion		...�A�j���[�V�����̎��
//		frame		...�A�j���[�V�����X�V�̑���
//				frame�����傫����΁A�X�V���x���x���Ȃ�
//
void UpdateAnimations(Animation* animation, int type, int frame);


#endif // !ANIMATION_H_


