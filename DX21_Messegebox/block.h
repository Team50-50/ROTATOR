#pragma once

#include <d3dx9.h>
#include "collision.h"

// ブロックのMax数（配列の数）
#define BLOCK_MAX (1024)

//ブロックの大きさX
#define BLOCK_SIZE_X (64.0f)

//ブロックの大きさY
#define BLOCK_SIZE_Y (64.0f)


typedef struct {

	D3DXVECTOR2 position;
	D3DXVECTOR2 start;
	D3DXVECTOR2 end;
	bool  use;
	int   Width_Quantity;
	int   High_Quantity;

}Block;


void InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();

void SetBlock(float x, float y, int w, int h);

//ブロックの位置座標を渡す関数
Block*  GetBlockPosition();