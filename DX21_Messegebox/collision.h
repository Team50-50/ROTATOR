/*=======================================================================================

	 collision����[collision.h]
												author:mgc
												date:2020/07/23
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef COLLISION_H
#define COLLISION_H

#include <d3dx9.h>

//�~��collision
typedef struct CollisionCircle_tag
{
	D3DXVECTOR2 center;
	float radius;

}CollisionCircle;

//��`��collision
typedef struct CollisionRect_tag
{
	D3DXVECTOR2 start;	//����̍��W
	D3DXVECTOR2 end;	//�E���̍��W

}CollisionRect;

//��`�̕ӂ̎��
enum {
	EDGENONE = -1,
	LEFTEDGE,
	RIGHTEDGE,
	TOPEDGE,
	BOTTOMEDGE,
	EDGE_MAX
};

//�~�Ɖ~�̏Փ˔���
bool Collision_CircleAndCircleHit(const CollisionCircle* pA, const CollisionCircle* pB);

//��`�ƃ}�b�v�`�b�v�̕ӂ̏Փ˔���
bool Collision_RectAndMapchipEdgeHit(const CollisionRect& rect, D3DXVECTOR2 vec, int& contactEdge, float& contactEdgePosition);

#endif