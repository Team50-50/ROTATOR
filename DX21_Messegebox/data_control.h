/*=======================================================================================

	 ÉfÅ[É^êßå‰[data_control.h]
												author:mgc
												date:2020/11/19
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef DATA_H_
#define DATA_H_

#include<d3dx9.h>


#define RECORDFRAME_MAX (400)

typedef struct
{
	D3DXVECTOR2 positionData[RECORDFRAME_MAX];
	bool rlData[RECORDFRAME_MAX];
	int animData[RECORDFRAME_MAX];
	float directionData[RECORDFRAME_MAX];

	int Pdata_tail;
	int Rdata_tail;
	int Adata_tail;
	int Ddata_tail;

}DataStorage;

void DataRecord(DataStorage* data, D3DXVECTOR2 playerPosition, bool RL, int anim, float direction);

D3DXVECTOR2 deq_Positiondata(DataStorage* data);

D3DXVECTOR2 pop_Positiondata(DataStorage* data);

bool deq_RLdata(DataStorage* data);

bool pop_RLdata(DataStorage* data);

int deq_Animdata(DataStorage* data);

int pop_Animdata(DataStorage* data);

float deq_Directiondata(DataStorage* data);

float pop_Directiondata(DataStorage* data);

#endif // !DATA_H_

