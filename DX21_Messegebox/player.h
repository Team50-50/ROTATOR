#ifndef PLAYER_H
#define PLAYER_H

#include "data_control.h"
#include"collision.h"
#include"animation.h"

typedef struct
{
	D3DXVECTOR2 position;
	D3DXVECTOR2 speed;
	D3DXVECTOR2 direction;

	bool enable;
	bool isJump;
	bool RL; //�����𔻒肷��p�@�E����=false  ������=true

	Animation animation[TYPE_MAX];

}Player;

//�v���C���[�̑傫��X
#define PLAYER_SIZE_X (64.0f)

//�v���C���[�̑傫��Y
#define PLAYER_SIZE_Y (128.0f)

#define JUMP_FORCE (-20.0f)
#define GRAVITY (1.0f)

void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();

//�Q�[���v���C���[�̈ړ�����
void GamePlayer_MoveLeft(void);
void GamePlayer_MoveRight(void);
void GamePlayer_Jump(void);

CollisionCircle GamePlayer_GetCollision(void);
D3DXVECTOR2 GetPlayerPosition();

DataStorage GetPrev(void);
DataStorage GetDebug(void);

int GetPlayerUseKey(void);

#endif //PLAYER_H