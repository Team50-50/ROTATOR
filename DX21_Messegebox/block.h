#pragma once

// ブロックのMax数（配列の数）
#define BLOCK_MAX (100)

//ブロックの大きさX
#define BLOCK_SIZE_X (64.0f)

//ブロックの大きさY
#define BLOCK_SIZE_Y (64.0f)


void InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();


//ブロックの位置座標を渡す関数
//
//int nはブロックの配列数
D3DXVECTOR2  GetBlockPosition(int n);




