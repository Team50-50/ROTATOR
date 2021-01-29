/*=======================================================================================

	 collision判定[collision.cpp]
												author:mgc
												date:2020/07/23
 -----------------------------------------------------------------------------------------

 =========================================================================================*/

#include "collision.h"
#include <d3dx9.h>
#include "map.h"
#include "stagechoice.h"

 //円と円の衝突判定
bool Collision_CircleAndCircleHit(const CollisionCircle* pA, const CollisionCircle* pB)
{
	D3DXVECTOR2 vec = pA->center - pB->center;

	return D3DXVec2LengthSq(&vec) < (pA->radius + pB->radius) * (pA->radius + pB->radius);
}

//矩形とマップチップの衝突判定
bool Collision_RectAndMapchipEdgeHit(const CollisionRect& rect, D3DXVECTOR2 vec, int& contactEdge, float& contactEdgePosition)
{
	CollisionRect Rect = rect;

	Rect.start += vec;
	Rect.end += vec;

	//0～63
	Rect.end.x -= 1.0f;
	Rect.end.y -= 1.0f;

	// 矩形のX軸範囲
	int width_range[]
	{
		(int)(Rect.start.x / MAPCHIP_WIDTH),
		(int)(Rect.end.x / MAPCHIP_WIDTH)
	};

	// 矩形のY軸範囲
	int height_range[]
	{
		(int)(Rect.start.y / MAPCHIP_HEIGHT),
		(int)(Rect.end.y / MAPCHIP_HEIGHT)
	};

	//範囲チェック
	for (int i = 0; i < 2; i++)
	{
		width_range[i] = max(width_range[i], 0);
		width_range[i] = min(width_range[i], MAP_XSIZE - 1);

		height_range[i] = max(height_range[i], 0);
		height_range[i] = min(height_range[i], MAP_YSIZE - 1);

	}

	D3DXVECTOR2 edge_list[EDGE_MAX][2]
	{
		//左
		{
			{(float)width_range[0],(float)height_range[0]},
			{(float)width_range[0],(float)height_range[1]}
		},

		//右
		{
			{(float)width_range[1],(float)height_range[0]},
			{(float)width_range[1],(float)height_range[1]}
		},

		//上
		{
			{(float)width_range[0],(float)height_range[0]},
			{(float)width_range[1],(float)height_range[0]}
		},

		//下
		{
			{(float)width_range[0],(float)height_range[1]},
			{(float)width_range[1],(float)height_range[1]}
		},
	};

	// 判定で使用するベクトルを決める
	bool is_use_edge_list[EDGE_MAX]
	{
		vec.x < 0.0f ? true : false,
		vec.x > 0.0f ? true : false,
		vec.y < 0.0f ? true : false,
		vec.y > 0.0f ? true : false,
	};

	int* map = NULL;
	switch (Getmap())
	{
	case 0:
		map = GetMapchip();
		break;
	case 1:
		map = GetMapchip2();
		break;
	case 2:
		map = GetMapchip3();
		break;
	}

	for (int i = 0; i < EDGE_MAX; i++)
	{
		//ベクトルに対応した辺だけ判定
		if (!is_use_edge_list[i]) continue;

		for (int y = (int)edge_list[i][0].y; y <= (int)edge_list[i][1].y; y++)
		{
			for (int x = (int)edge_list[i][0].x; x <= (int)edge_list[i][1].x; x++)
			{
				if (*(map + (y * MAP_XSIZE) + x) == 1)
				{
					// 接触した辺の座標を返す
					GetChipEdgeHit(i, x, y, contactEdge, contactEdgePosition);

					//当たり
					return true;
				}

			}
		}
	}

	return false;
}
