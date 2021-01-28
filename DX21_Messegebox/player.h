/*=======================================================================================

	 �v���C���̐���[player.h]
												author:�g�E �~�����E & �}�R�E�`���E
												date:
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef PLAYER_H
#define PLAYER_H

#include "data_control.h"
#include"collision.h"
#include"animation.h"
#include"block.h"

 /*-----------------------------------------------------------------------------------------
	�\���̐錾
 -------------------------------------------------------------------------------------------*/
typedef struct
{
	D3DXVECTOR2 position;
	D3DXVECTOR2 direction;
	D3DXVECTOR2 PrevPosition;
	D3DXVECTOR2 start;
	D3DXVECTOR2 end;

	float JumpVelocity;

	bool enable;
	bool isJump;
	bool RL; //�����𔻒肷��p�@�E����=false  ������=true

	Animation animation[TYPE_MAX];

	CollisionCircle collision[2];

}Player;

/*-----------------------------------------------------------------------------------------
	�萔�錾
-------------------------------------------------------------------------------------------*/
//�v���C���[�̑傫��X
#define PLAYER_SIZE_X (60.0f)

//�v���C���[�̑傫��Y
#define PLAYER_SIZE_Y (120.0f)


#define JUMP_FORCE (18.0f)
#define GRAVITY (1.0f)

void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();

DataStorage GetPrev(void);
DataStorage GetDebug(void);

int GetPlayerUseKey(void);

CollisionCircle* Get_PlayerCollision(void);

void SetPlayerMapPos(int contact_edge, float contact_pos);

Player GetPlayer(void);

#endif //PLAYER_H