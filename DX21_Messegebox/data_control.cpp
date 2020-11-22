/*=======================================================================================

	 ƒf[ƒ^§Œä[data_control.cpp]
												author:mgc
												date:2020/11/19
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#include"data_control.h"

void DataRecord(DataStorage* data, D3DXVECTOR2 playerPosition)
{
	if (data->data_tail > RECORDFRAME_MAX)
	{
		return;
	}
	data->positionData[data->data_tail] = playerPosition;
	data->data_tail++;

}

D3DXVECTOR2 dequeue(DataStorage* data)
{
	D3DXVECTOR2 tmp;
	if (data->data_tail == 0)
	{
		return data->positionData[data->data_head];
	}

	tmp = data->positionData[data->data_head];

	for (int i = 0; i < data->data_tail - 1; i++)
	{
		data->positionData[i] = data->positionData[i + 1];
	}
	data->positionData[data->data_tail - 1] = D3DXVECTOR2(0.0f, 0.0f);
	data->data_tail--;
	return tmp;
}

D3DXVECTOR2 pop(DataStorage* data)
{
	D3DXVECTOR2 ret;

	if (data->data_tail == 0)
	{
		return data->positionData[data->data_tail];
	}

	ret = data->positionData[data->data_tail - 1];

	data->data_tail--;

	return ret;
}

