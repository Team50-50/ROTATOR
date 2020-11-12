#ifndef PLAYER_H
#define PLAYER_H

//�v���C���[�̑傫��X
#define PLAYER_SIZE_X (64.0f)

//�v���C���[�̑傫��Y
#define PLAYER_SIZE_Y (128.0f)

#define FRAME_MAX (3600)

void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();

D3DXVECTOR2 GetPlayerPosition();

//�L���[�\����
typedef struct
{
	D3DXVECTOR2 position_Data[FRAME_MAX];

	int recordFrame_head;
	int recordFrame_tail;
}Queue;

//�X�^�b�N�\����
typedef struct
{
	D3DXVECTOR2 position_Data[FRAME_MAX];
	int playFrame;
	int recordFrame;
}Stack;

//�G���L���[...position�f�[�^���L���[�ɒǉ�����A����Ō���Ƀf�[�^��ǉ�����B
void enqueue(Queue* q, D3DXVECTOR2 playerPosition);
//�f�L���[...position�f�[�^���L���[������o���A����擪�̃f�[�^(��ԌÂ���position�f�[�^)�����o���B
D3DXVECTOR2 dequeue(Queue* q);

Queue GetqCurrent(void);
Queue GetqPrev(void);

//PUSH...position�f�[�^���X�^�b�N�ɒǉ�����
void push(Stack* stack, D3DXVECTOR2 playerPosition);
//POP...position�f�[�^���X�^�b�N������o���A����Ō� PUSH ���� position�f�[�^��������o��
D3DXVECTOR2 pop(Stack* stack);

Stack GetstackPrev(void);
Stack GetstackCurrent(void);

#endif //PLAYER_H