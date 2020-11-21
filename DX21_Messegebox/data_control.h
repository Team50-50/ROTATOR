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
	int data_head;
	int data_tail;

}DataWarehouse;

void DataRecord(DataWarehouse* data, D3DXVECTOR2 positionData);


D3DXVECTOR2 dequeue(DataWarehouse* data);


D3DXVECTOR2 pop(DataWarehouse* data);


#endif // !DATA_H_

