/*=======================================================================================

	 ブロックの制御[block.h]
												author:トウ ミンヨウ　& マコウチュウ
												date:
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
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
	D3DXVECTOR2 direction;
	D3DXVECTOR2 start;
	D3DXVECTOR2 end;
	bool  use;
	bool  fall;
	int   Width_Quantity;
	int   High_Quantity;
	int type;
	CollisionRect rect;
}Block;

//ブロックのタイプ
enum BLOCK_TYPE
{
	BLOCK_NORMAL,
	BLOCK_OFFSETY,
	BLOCKTYPE_MAX
};

void InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();

void SetBlock(float x, float y, int w, int h, int type);

//ブロックの位置座標を渡す関数
Block*  GetBlockPosition();

void SetBlockMapPos(int contact_edge, float contact_pos, int index);