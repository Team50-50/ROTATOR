#ifndef PLAYER_H
#define PLAYER_H

//プレイヤーの大きさX
#define PLAYER_SIZE_X (64.0f)

//プレイヤーの大きさY
#define PLAYER_SIZE_Y (128.0f)

#define FRAME_MAX (3600)

void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();

D3DXVECTOR2 GetPlayerPosition();

//キュー構造体
typedef struct
{
	D3DXVECTOR2 position_Data[FRAME_MAX];

	int recordFrame_head;
	int recordFrame_tail;
}Queue;

//スタック構造体
typedef struct
{
	D3DXVECTOR2 position_Data[FRAME_MAX];
	int playFrame;
	int recordFrame;
}Stack;

//エンキュー...positionデータをキューに追加する、毎回最後尾にデータを追加する。
void enqueue(Queue* q, D3DXVECTOR2 playerPosition);
//デキュー...positionデータをキューから取り出す、毎回先頭のデータ(一番古いのpositionデータ)を取り出す。
D3DXVECTOR2 dequeue(Queue* q);

Queue GetqCurrent(void);
Queue GetqPrev(void);

//PUSH...positionデータをスタックに追加する
void push(Stack* stack, D3DXVECTOR2 playerPosition);
//POP...positionデータをスタックから取り出す、毎回最後 PUSH した positionデータからを取り出す
D3DXVECTOR2 pop(Stack* stack);

Stack GetstackPrev(void);
Stack GetstackCurrent(void);

#endif //PLAYER_H