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
	bool RL; //向きを判定する用　右向き=false  左向き=true

	Animation animation[TYPE_MAX];

}Player;

//プレイヤーの大きさX
#define PLAYER_SIZE_X (64.0f)

//プレイヤーの大きさY
#define PLAYER_SIZE_Y (128.0f)

#define JUMP_FORCE (-20.0f)
#define GRAVITY (1.0f)

void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();

//ゲームプレイヤーの移動処理
void GamePlayer_MoveLeft(void);
void GamePlayer_MoveRight(void);
void GamePlayer_Jump(void);

CollisionCircle GamePlayer_GetCollision(void);
D3DXVECTOR2 GetPlayerPosition();

DataStorage GetPrev(void);
DataStorage GetDebug(void);

int GetPlayerUseKey(void);

#endif //PLAYER_H