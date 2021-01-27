/*=======================================================================================

	 データ制御[data_control.h]
												author:mgc
												date:2020/11/19
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef DATA_CONTROL_H_
#define DATA_CONTROL_H_

#include<d3dx9.h>


#define RECORDFRAME_MAX (400)

typedef struct
{
	D3DXVECTOR2 vec2Data[RECORDFRAME_MAX];
	bool tfData[RECORDFRAME_MAX];
	int numData[RECORDFRAME_MAX];
	int aData[RECORDFRAME_MAX];
	float decimalData[RECORDFRAME_MAX];

	int Vdata_tail;
	int Bdata_tail;
	int Idata_tail;
	int Adata_tail;
	int Fdata_tail;

}DataStorage;

//データの記録
//
//ゲームobjectのデータを記録する
//
//引数：(DataStorage*) data....... データを格納する構造体
//				
//			vec2Data... vector2型データ
//
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data);

//データの記録
//
//ゲームobjectのデータを記録する
//
//引数：(DataStorage*) data....... データを格納する構造体
//				
//			  aData.... アルファデータ
//
void DataRecord(DataStorage* data, int aData);

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
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data, int aData, float DecimalData);

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
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data, int NumData, int aData, bool TFData);


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
//
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data, bool TFData, float DecimalData);


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
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data, bool TFData, int NumData, float DecimalData);

//vector2型のデータ配列の <先頭> からデータを取り出す
D3DXVECTOR2 deq_Vec2Data(DataStorage* data);

//vector2型のデータ配列の <末尾> からデータを取り出す
D3DXVECTOR2 pop_Vec2Data(DataStorage* data);

//bool型のデータ配列の <先頭> からデータを取り出す
bool deq_TFData(DataStorage* data);

//bool型のデータ配列の <末尾> からデータを取り出す
bool pop_TFData(DataStorage* data);

//int型のデータ配列の <先頭> からデータを取り出す
int deq_NumData(DataStorage* data);

//int型のデータ配列の <末尾> からデータを取り出す
int pop_NumData(DataStorage* data);

//アルファデータ配列の <先頭> からデータを取り出す
int deq_aData(DataStorage* data);

//アルファデータ配列の <末尾> からデータを取り出す
int pop_aData(DataStorage* data);

//float型のデータ配列の <先頭> からデータを取り出す
float deq_DecimalData(DataStorage* data);

//float型のデータ配列の <末尾> からデータを取り出す
float pop_DecimalData(DataStorage* data);

#endif // !DATA_CONTROL_H_

