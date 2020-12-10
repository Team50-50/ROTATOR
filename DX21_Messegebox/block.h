#pragma once

#include <d3dx9.h>
#include "collision.h"

// �u���b�N��Max���i�z��̐��j
#define BLOCK_MAX (1024)

//�u���b�N�̑傫��X
#define BLOCK_SIZE_X (64.0f)

//�u���b�N�̑傫��Y
#define BLOCK_SIZE_Y (64.0f)


typedef struct {

	bool  use;
	D3DXVECTOR2 xy;

	int   Width_Quantity;
	int   High_Quantity;

}Block;


void InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();

void SetBlock(float x, float y, int w, int h);

//�u���b�N�̈ʒu���W��n���֐�
Block*  GetBlockPosition();

// 
CollisionCircle GameBlock_GetCollision(int index);