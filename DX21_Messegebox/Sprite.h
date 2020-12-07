/*==============================================================================

	TITLE
													Author : Ryuichi Tsunoda
													Date   :
==============================================================================*/
#ifndef SPRITE_H_
#define SPRITE_H_

void Sprite_Initialize(void);

void Sprite_Finalize(void);


//�X�v���C�g�̕`��
//���e�N�X�`���؂���T�C�Y�̃|���S���Ŏw����W�ɕ`��
//
//�����FtextureId...�e�N�X�`���Ǘ��ԍ�
//
//		dx       ...�`����Wx(����w��)
//		dy       ...�`����Wy(����w��)
//
void Sprite_Draw(int textureId, float dx, float dy);


//�X�v���C�g�̕`��
//���e�N�X�`���؂���T�C�Y�̃|���S���Ŏw����W�ɕ`��
//
//�����FtextureId...�e�N�X�`���Ǘ��ԍ�
//
//		dx       ...�`����Wx(����w��)
//		dy       ...�`����Wy(����w��)
//		tcx      ...�e�N�X�`���؂�����Wx
//		tcy      ...�e�N�X�`���؂�����Wy
//		tcw      ...�e�N�X�`���؂��蕝
//		tch      ...�e�N�X�`���؂��荂��
//
void Sprite_Draw(int textureId, float dx, float dy, int tcx, int tcy, int tcw, int tch);


//�X�v���C�g�̕`��
//���w��e�N�X�`���؂���T�C�Y�̃|���S���Ŏw����W�ɕ`��
//
//
//�����FtextureId...�e�N�X�`���Ǘ��ԍ�
//
//		dx       ...�`����Wx(����w��)
//		dy       ...�`����Wy(����w��)
//		dw		 ...�|���S���̃T�C�Y��
//		dh		 ...�|���S���̃T�C�Y����
//		tcx      ...�e�N�X�`���؂�����Wx
//		tcy      ...�e�N�X�`���؂�����Wy
//		tcw      ...�e�N�X�`���؂��蕝
//		tch      ...�e�N�X�`���؂��荂��
//
void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);


//�X�v���C�g�̕`��
//���w�肵���e�N�X�`���؂���T�C�Y�̃|���S���ŐF��ς��Ďw����W�ɕ`��
//
//
//�����FtextureId...�e�N�X�`���Ǘ��ԍ�
//
//		dx       ...�`����Wx(����w��)
//		dy       ...�`����Wy(����w��)
//		dw		 ...�|���S���̃T�C�Y��
//		dh		 ...�|���S���̃T�C�Y����
//		tcx      ...�e�N�X�`���؂�����Wx
//		tcy      ...�e�N�X�`���؂�����Wy
//		tcw      ...�e�N�X�`���؂��蕝
//		tch      ...�e�N�X�`���؂��荂��
//		D3DCOLOR color�@...�e�N�X�`���̐F��RGB�Őݒ�
//
void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, D3DCOLOR color);


//�X�v���C�g�̕`��
//����]�@�\�t��
//
//�����FtextureId...�e�N�X�`���Ǘ��ԍ�
//
//		dx       ...�`����Wx(����w��)
//		dy       ...�`����Wy(����w��)
//		dw		 ...�|���S���̃T�C�Y��
//		dh		 ...�|���S���̃T�C�Y����
//		tcx      ...�e�N�X�`���؂�����Wx
//		tcy      ...�e�N�X�`���؂�����Wy
//		tcw      ...�e�N�X�`���؂��蕝
//		tch      ...�e�N�X�`���؂��荂��
//		cx		 ...��]�̒��S���Wx
//		cy		 ...��]�̒��S���Wy
//		angle    ...��]�p�x(���W�A��)
//
void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch,
	float cx, float cy, float angle);

void Screen_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);

void Screen_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, D3DCOLOR color);

void Sprite_DrawLeft(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);

void Sprite_DrawLeft(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, D3DCOLOR color);

#endif // SPRITE_H_