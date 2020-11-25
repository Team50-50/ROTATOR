#ifndef PLAYER_H
#define PLAYER_H

#include "data_control.h"
#include"collision.h"

//�v���C���[�̑傫��X
#define PLAYER_SIZE_X (64.0f)

//�v���C���[�̑傫��Y
#define PLAYER_SIZE_Y (128.0f)


void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();

CollisionCircle GamePlayer_GetCollision(void);
D3DXVECTOR2 GetPlayerPosition();

DataStorage GetPrev(void);
DataStorage GetDebug(void);

int GetPlayerUseKey(void);

#endif //PLAYER_H