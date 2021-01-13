/*=======================================================================================

	 collision����[collision.cpp]
												author:mgc
												date:2020/07/23
 -----------------------------------------------------------------------------------------

 =========================================================================================*/

#include "collision.h"
#include <d3dx9.h>
#include "map.h"

bool Collision_CircleAndCircleHit(const CollisionCircle* pA, const CollisionCircle* pB)
{
	D3DXVECTOR2 vec = pA->center - pB->center;

	return D3DXVec2LengthSq(&vec) < (pA->radius + pB->radius) * (pA->radius + pB->radius);
}

//��`�ƃ}�b�v�`�b�v�̏Փ˔���
bool Collision_RectAndMapchipEdgeHit(const CollisionRect& rect, D3DXVECTOR2 vec, int& contactEdge, float& contactEdgePosition)
{
	CollisionRect Rect = rect;

	Rect.start += vec;
	Rect.end += vec;

	//0�`63
	Rect.end.x -= 1.0f;
	Rect.end.y -= 1.0f;

	// ��`��X���͈�
	int width_range[]
	{
		(int)(Rect.start.x / MAPCHIP_WIDTH),
		(int)(Rect.end.x / MAPCHIP_WIDTH)
	};

	// ��`��Y���͈�
	int height_range[]
	{
		(int)(Rect.start.y / MAPCHIP_HEIGHT),
		(int)(Rect.end.y / MAPCHIP_HEIGHT)
	};

	//�͈̓`�F�b�N
	for (int i = 0; i < 2; i++)
	{
		width_range[i] = max(width_range[i], 0);
		width_range[i] = min(width_range[i], MAP_XSIZE - 1);

		height_range[i] = max(height_range[i], 0);
		height_range[i] = min(height_range[i], MAP_YSIZE - 1);

	}

	D3DXVECTOR2 edge_list[EDGE_MAX][2]
	{
		//��
		{
			{(float)width_range[0],(float)height_range[0]},
			{(float)width_range[0],(float)height_range[1]}
		},

		//�E
		{
			{(float)width_range[1],(float)height_range[0]},
			{(float)width_range[1],(float)height_range[1]}
		},

		//��
		{
			{(float)width_range[0],(float)height_range[0]},
			{(float)width_range[1],(float)height_range[0]}
		},

		//��
		{
			{(float)width_range[0],(float)height_range[1]},
			{(float)width_range[1],(float)height_range[1]}
		},
	};

	// ����Ŏg�p����x�N�g�������߂�
	bool is_use_edge_list[EDGE_MAX]
	{
		vec.x < 0.0f ? true : false,
		vec.x > 0.0f ? true : false,
		vec.y < 0.0f ? true : false,
		vec.y > 0.0f ? true : false,
	};

	int* map = GetMapchip();

	for (int i = 0; i < EDGE_MAX; i++)
	{
		//�x�N�g���ɑΉ������ӂ�������
		if (!is_use_edge_list[i]) continue;

		for (int y = (int)edge_list[i][0].y; y <= (int)edge_list[i][1].y; y++)
		{
			for (int x = (int)edge_list[i][0].x; x <= (int)edge_list[i][1].x; x++)
			{
				if (*(map + (y * MAP_XSIZE) + x) == 1)
				{
					// �ڐG�����ӂ̍��W��Ԃ�
					GetChipEdgeHit(i, x, y, contactEdge, contactEdgePosition);

					//������
					return true;
				}

			}
		}
	}

	return false;
}
