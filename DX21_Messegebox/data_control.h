/*=======================================================================================

	 �f�[�^����[data_control.h]
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

//�f�[�^�̋L�^
//
//�Q�[��object�̃f�[�^���L�^����
//
//�����F(DataStorage*) data....... �f�[�^���i�[����\����
//				
//			vec2Data... vector2�^�f�[�^
//
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data);

//�f�[�^�̋L�^
//
//�Q�[��object�̃f�[�^���L�^����
//
//�����F(DataStorage*) data....... �f�[�^���i�[����\����
//
//			vec2Data... vector2�^�f�[�^
//			  aData.... �A���t�@�f�[�^
//		DecimalData.... flaot�^�f�[�^
//
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data, int aData, float DecimalData);

//�f�[�^�̋L�^
//
//�Q�[��object�̃f�[�^���L�^����
//
//�����F(DataStorage*) data....... �f�[�^���i�[����\����
//
 //			vec2Data... vector2�^�f�[�^
//			NumData.... int�^�f�[�^
//			  aData.... �A���t�@�f�[�^
//			TFData..... bool�^�f�[�^
//
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data, int NumData, int aData, bool TFData);


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
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data, bool TFData, float DecimalData);


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
void DataRecord(DataStorage* data, D3DXVECTOR2 Vec2Data, bool TFData, int NumData, float DecimalData);

//vector2�^�̃f�[�^�z��� <�擪> ����f�[�^�����o��
D3DXVECTOR2 deq_Vec2Data(DataStorage* data);

//vector2�^�̃f�[�^�z��� <����> ����f�[�^�����o��
D3DXVECTOR2 pop_Vec2Data(DataStorage* data);

//bool�^�̃f�[�^�z��� <�擪> ����f�[�^�����o��
bool deq_TFData(DataStorage* data);

//bool�^�̃f�[�^�z��� <����> ����f�[�^�����o��
bool pop_TFData(DataStorage* data);

//int�^�̃f�[�^�z��� <�擪> ����f�[�^�����o��
int deq_NumData(DataStorage* data);

//int�^�̃f�[�^�z��� <����> ����f�[�^�����o��
int pop_NumData(DataStorage* data);

//�A���t�@�f�[�^�z��� <�擪> ����f�[�^�����o��
int deq_aData(DataStorage* data);

//�A���t�@�f�[�^�z��� <����> ����f�[�^�����o��
int pop_aData(DataStorage* data);

//float�^�̃f�[�^�z��� <�擪> ����f�[�^�����o��
float deq_DecimalData(DataStorage* data);

//float�^�̃f�[�^�z��� <����> ����f�[�^�����o��
float pop_DecimalData(DataStorage* data);

#endif // !DATA_CONTROL_H_

