/*=======================================================================================

	 データ制御[data_control.cpp]
												author:mgc
												date:2020/11/19
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#include"data_control.h"


 //データの記録
 //
 //ゲームobjectのデータを記録する
 //
 //引数：(DataStorage*) data....... データを格納する構造体
 //				
 //			vec2Data... vector2型データ
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

//データの記録
//
//ゲームobjectのデータを記録する
//
//引数：(DataStorage*) data....... データを格納する構造体
//				
//			  aData.... アルファデータ
//
void DataRecord(DataStorage* data, int aData)
{
	if (data->Adata_tail > RECORDFRAME_MAX)
	{
		return;
	}
	data->aData[data->Adata_tail] = aData;

	data->Adata_tail++;
}

//データの記録
//
//ゲームobjectのデータを記録する
//
//引数：(DataStorage*) data....... データを格納する構造体
//
//			vec2Data... vector2型データ
//			  aData.... アルファデータ
//		DecimalData.... flaot型データ
//
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data, int aData, float DecimalData)
{
	if (data->Vdata_tail > RECORDFRAME_MAX ||
		data->Adata_tail > RECORDFRAME_MAX ||
		data->Fdata_tail > RECORDFRAME_MAX)
	{
		return;
	}

	data->vec2Data[data->Vdata_tail] = Vec2Data;
	data->aData[data->Adata_tail] = aData;
	data->decimalData[data->Fdata_tail] = DecimalData;

	data->Vdata_tail++;
	data->Adata_tail++;
	data->Fdata_tail++;
}

//データの記録
//
//ゲームobjectのデータを記録する
//
//引数：(DataStorage*) data....... データを格納する構造体
//
 //			vec2Data... vector2型データ
//			NumData.... int型データ
//			  aData.... アルファデータ
//			TFData..... bool型データ
//
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data, int NumData, int aData, bool TFData)
{
	if (data->Vdata_tail > RECORDFRAME_MAX ||
		data->Idata_tail > RECORDFRAME_MAX ||
		data->Adata_tail > RECORDFRAME_MAX ||
		data->Bdata_tail > RECORDFRAME_MAX)
	{
		return;
	}

	data->vec2Data[data->Vdata_tail] = Vec2Data;
	data->numData[data->Idata_tail] = NumData;
	data->aData[data->Adata_tail] = aData;
	data->tfData[data->Bdata_tail] = TFData;

	data->Vdata_tail++;
	data->Idata_tail++;
	data->Adata_tail++;
	data->Bdata_tail++;
}


//データの記録
//
//ゲームobjectのデータを記録する
//
//引数：(DataStorage*) data....... データを格納する構造体
//				
//			vec2Data...... vector2型データ
//			TFData........ bool型データ
//			DecimalData... flaot型データ
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


//データの記録
//
//ゲームobjectのデータを記録する
//
//引数：(DataStorage*) data....... データを格納する構造体
//				
//			vec2Data...... vector2型データ
//			TFData........ bool型データ
//			NumData....... int型データ
//			DecimalData... flaot型データ
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

//vector2型のデータ配列の <先頭> からデータを取り出す
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

//vector2型のデータ配列の <末尾> からデータを取り出す
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

//bool型のデータ配列の <先頭> からデータを取り出す
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

//bool型のデータ配列の <末尾> からデータを取り出す
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

//int型のデータ配列の <先頭> からデータを取り出す
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

//int型のデータ配列の <末尾> からデータを取り出す
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

//アルファデータ配列の <先頭> からデータを取り出す
int deq_aData(DataStorage* data)
{
	int tmp;
	if (data->Adata_tail == 0)
	{
		return data->aData[0];
	}

	tmp = data->aData[0];

	for (int i = 0; i < data->Adata_tail - 1; i++)
	{
		data->aData[i] = data->aData[i + 1];
	}

	data->Adata_tail--;

	return tmp;
}

//アルファデータ配列の <末尾> からデータを取り出す
int pop_aData(DataStorage* data)
{
	int ret;

	if (data->Adata_tail == 0)
	{
		return data->aData[data->Adata_tail];
	}

	ret = data->aData[data->Adata_tail - 1];

	data->Adata_tail--;
	return ret;
}

//float型のデータ配列の <先頭> からデータを取り出す
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

//float型のデータ配列の <末尾> からデータを取り出す
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