/*=======================================================================================

	 �f�[�^����[data_control.cpp]
												author:mgc
												date:2020/11/19
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#include"data_control.h"


 //�f�[�^�̋L�^
 //
 //�Q�[��object�̃f�[�^���L�^����
 //
 //�����F(DataStorage*) data....... �f�[�^���i�[����\����
 //				
 //			vec2Data... vector2�^�f�[�^
 //
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data)
{
	if (data->Vdata_tail > RECORDFRAME_MAX)
	{
		return;
	}
	data->vec2Data[data->Vdata_tail] = Vec2Data;


	data->Vdata_tail++;
}


//�f�[�^�̋L�^
//
//�Q�[��object�̃f�[�^���L�^����
//
//�����F(DataStorage*) data....... �f�[�^���i�[����\����
//				
//			vec2Data...... vector2�^�f�[�^
//			TFData........ bool�^�f�[�^
//			DecimalData... flaot�^�f�[�^
//
//
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data, bool TFData, float DecimalData)
{
	if (data->Vdata_tail > RECORDFRAME_MAX ||
		data->Bdata_tail > RECORDFRAME_MAX ||
		data->Fdata_tail > RECORDFRAME_MAX)
	{
		return;
	}
	data->vec2Data[data->Vdata_tail] = Vec2Data;
	data->tfData[data->Bdata_tail] = TFData;
	data->decimalData[data->Fdata_tail] = DecimalData;

	data->Vdata_tail++;
	data->Bdata_tail++;
	data->Fdata_tail++;
}


//�f�[�^�̋L�^
//
//�Q�[��object�̃f�[�^���L�^����
//
//�����F(DataStorage*) data....... �f�[�^���i�[����\����
//				
//			vec2Data...... vector2�^�f�[�^
//			TFData........ bool�^�f�[�^
//			NumData....... int�^�f�[�^
//			DecimalData... flaot�^�f�[�^
//
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data, bool TFData, int NumData, float DecimalData)
{
	if (data->Vdata_tail > RECORDFRAME_MAX ||
		data->Bdata_tail > RECORDFRAME_MAX ||
		data->Idata_tail > RECORDFRAME_MAX ||
		data->Fdata_tail > RECORDFRAME_MAX)
	{
		return;
	}
	data->vec2Data[data->Vdata_tail] = Vec2Data;
	data->tfData[data->Bdata_tail] = TFData;
	data->numData[data->Idata_tail] = NumData;
	data->decimalData[data->Fdata_tail] = DecimalData;

	data->Vdata_tail++;
	data->Bdata_tail++;
	data->Idata_tail++;
	data->Fdata_tail++;

}

//vector2�^�̃f�[�^�z��� <�擪> ����f�[�^�����o��
D3DXVECTOR2 deq_Vec2Data(DataStorage* data)
{
	D3DXVECTOR2 tmp;
	if (data->Vdata_tail == 0)
	{
		return data->vec2Data[0];
	}

	tmp = data->vec2Data[0];

	for (int i = 0; i < data->Vdata_tail - 1; i++)
	{
		data->vec2Data[i] = data->vec2Data[i + 1];
	}
	data->vec2Data[data->Vdata_tail - 1] = D3DXVECTOR2(0.0f, 0.0f);

	data->Vdata_tail--;
	return tmp;
}

//vector2�^�̃f�[�^�z��� <����> ����f�[�^�����o��
D3DXVECTOR2 pop_Vec2Data(DataStorage* data)
{
	D3DXVECTOR2 ret;

	if (data->Vdata_tail == 0)
	{
		return data->vec2Data[data->Vdata_tail];
	}

	ret = data->vec2Data[data->Vdata_tail - 1];

	data->Vdata_tail--;

	return ret;
}

//bool�^�̃f�[�^�z��� <�擪> ����f�[�^�����o��
bool deq_TFData(DataStorage* data)
{
	bool tmp;
	if (data->Bdata_tail == 0)
	{
		return data->tfData[0];
	}

	tmp = data->tfData[0];

	for (int i = 0; i < data->Bdata_tail - 1; i++)
	{
		data->tfData[i] = data->tfData[i + 1];
	}

	data->Bdata_tail--;

	return tmp;
}

//bool�^�̃f�[�^�z��� <����> ����f�[�^�����o��
bool pop_TFData(DataStorage* data)
{
	bool ret;

	if (data->Bdata_tail == 0)
	{
		return data->tfData[data->Bdata_tail];
	}

	ret = data->tfData[data->Bdata_tail - 1];

	data->Bdata_tail--;

	return ret;
}

//int�^�̃f�[�^�z��� <�擪> ����f�[�^�����o��
int deq_NumData(DataStorage* data)
{
	int tmp;
	if (data->Idata_tail == 0)
	{
		return data->numData[0];
	}

	tmp = data->numData[0];

	for (int i = 0; i < data->Idata_tail - 1; i++)
	{
		data->numData[i] = data->numData[i + 1];
	}

	data->Idata_tail--;

	return tmp;
}

//int�^�̃f�[�^�z��� <����> ����f�[�^�����o��
int pop_NumData(DataStorage* data)
{
	int ret;

	if (data->Idata_tail == 0)
	{
		return data->numData[data->Idata_tail];
	}

	ret = data->numData[data->Idata_tail - 1];

	data->Idata_tail--;
	return ret;
}

//float�^�̃f�[�^�z��� <�擪> ����f�[�^�����o��
float deq_DecimalData(DataStorage* data)
{
	float tmp;
	if (data->Fdata_tail == 0)
	{
		return data->decimalData[0];
	}

	tmp = data->decimalData[0];

	for (int i = 0; i < data->Fdata_tail - 1; i++)
	{
		data->decimalData[i] = data->decimalData[i + 1];
	}

	data->Fdata_tail--;
	return tmp;
}

//float�^�̃f�[�^�z��� <����> ����f�[�^�����o��
float pop_DecimalData(DataStorage* data)
{
	float ret;

	if (data->Fdata_tail == 0)
	{
		return data->decimalData[data->Fdata_tail];
	}

	ret = data->decimalData[data->Fdata_tail - 1];

	data->Fdata_tail--;

	return ret;
}