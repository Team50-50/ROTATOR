#ifndef PLAYER_H
#define PLAYER_H

#include "data_control.h"

//プレイヤーの大きさX
#define PLAYER_SIZE_X (64.0f)

//プレイヤーの大きさY
#define PLAYER_SIZE_Y (128.0f)


void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();

D3DXVECTOR2 GetPlayerPosition();

DataStorage GetPrev(void);
DataStorage GetDebug(void);

#endif //PLAYER_H