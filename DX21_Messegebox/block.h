#pragma once

// �u���b�N��Max���i�z��̐��j
#define BLOCK_MAX (100)

//�u���b�N�̑傫��X
#define BLOCK_SIZE_X (64.0f)

//�u���b�N�̑傫��Y
#define BLOCK_SIZE_Y (64.0f)


void InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();


//�u���b�N�̈ʒu���W��n���֐�
//
//int n�̓u���b�N�̔z��
D3DXVECTOR2  GetBlockPosition(int n);




