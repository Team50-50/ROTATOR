/*=======================================================================================

	 ƒf[ƒ^§Œä[data_control.cpp]
												author:mgc
												date:2020/11/19
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#include"data_control.h"

void DataRecord(DataStorage* data, D3DXVECTOR2 playerPosition, bool RL, int anim, float direction)
{
	if (data->Pdata_tail > RECORDFRAME_MAX ||
		data->Rdata_tail > RECORDFRAME_MAX ||
		data->Adata_tail > RECORDFRAME_MAX ||
		data->Ddata_tail > RECORDFRAME_MAX)
	{
		return;
	}
	data->positionData[data->Pdata_tail] = playerPosition;
	data->rlData[data->Rdata_tail] = RL;
	data->animData[data->Adata_tail] = anim;
	data->directionData[data->Ddata_tail] = direction;

	data->Pdata_tail++;
	data->Rdata_tail++;
	data->Adata_tail++;
	data->Ddata_tail++;

}

D3DXVECTOR2 deq_Positiondata(DataStorage* data)
{
	D3DXVECTOR2 tmp;
	if (data->Pdata_tail == 0)
	{
		return data->positionData[0];
	}

	tmp = data->positionData[0];

	for (int i = 0; i < data->Pdata_tail - 1; i++)
	{
		data->positionData[i] = data->positionData[i + 1];
	}
	data->positionData[data->Pdata_tail - 1] = D3DXVECTOR2(0.0f, 0.0f);

	data->Pdata_tail--;
	return tmp;
}

D3DXVECTOR2 pop_Positiondata(DataStorage* data)
{
	D3DXVECTOR2 ret;

	if (data->Pdata_tail == 0)
	{
		return data->positionData[data->Pdata_tail];
	}

	ret = data->positionData[data->Pdata_tail - 1];

	data->Pdata_tail--;

	return ret;
}

bool deq_RLdata(DataStorage* data)
{
	bool tmp;
	if (data->Rdata_tail == 0)
	{
		return data->rlData[0];
	}

	tmp = data->rlData[0];

	for (int i = 0; i < data->Rdata_tail - 1; i++)
	{
		data->rlData[i] = data->rlData[i + 1];
	}

	data->Rdata_tail--;

	return tmp;
}

bool pop_RLdata(DataStorage* data)
{
	bool ret;

	if (data->Rdata_tail == 0)
	{
		return data->rlData[data->Rdata_tail];
	}

	ret = data->rlData[data->Rdata_tail - 1];

	data->Rdata_tail--;

	return ret;
}

int deq_Animdata(DataStorage* data)
{
	int tmp;
	if (data->Adata_tail == 0)
	{
		return data->animData[0];
	}

	tmp = data->animData[0];

	for (int i = 0; i < data->Adata_tail - 1; i++)
	{
		data->animData[i] = data->animData[i + 1];
	}

	data->Adata_tail--;

	return tmp;
}

int pop_Animdata(DataStorage* data)
{
	int ret;

	if (data->Adata_tail == 0)
	{
		return data->animData[data->Adata_tail];
	}

	ret = data->animData[data->Adata_tail - 1];

	data->Adata_tail--;
	return ret;
}

float deq_Directiondata(DataStorage* data)
{
	float tmp;
	if (data->Ddata_tail == 0)
	{
		return data->directionData[0];
	}

	tmp = data->directionData[0];

	for (int i = 0; i < data->Ddata_tail - 1; i++)
	{
		data->directionData[i] = data->directionData[i + 1];
	}

	data->Ddata_tail--;
	return tmp;
}

float pop_Directiondata(DataStorage* data)
{
	float ret;

	if (data->Ddata_tail == 0)
	{
		return data->directionData[data->Ddata_tail];
	}

	ret = data->directionData[data->Ddata_tail - 1];

	data->Ddata_tail--;

	return ret;
}