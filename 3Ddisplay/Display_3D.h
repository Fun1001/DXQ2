
/*******************************************/
//
//��������ֲZLG_GUI����ǰ��3D��ʾ��ֲһ�£�
//			��Ϊʹ��ZLG_GUI�Ļ�ͼ��������ʾ
//
//��ע����3Dת������ʾ����Ϊ��ǰѧϰ�͸ı�
//			������Դ�뿴��ϸ�ĵ�����


//���ߣ�	ִ��ִս
//ʱ�䣺2017/2/5  	21��50
//******************************************/


#ifndef _Display_3D_H
#define _Display_3D_H

#include "stm32f10x.h"



///************************************************
//					����ṹ��
//					����2D ��3D����
//*************************************************/
typedef struct{
	unsigned int  x;
	unsigned int  y;
}_2Dzuobiao ;				//����ֱ�������ֿ���ͷ�����ṹ������ƣ�����ǰ��Ӹ����_

typedef struct
{
	float x;
	float y;
	float z;
}_3Dzuobiao;

/*****************************************************/
//3D-transform.c ����
//���任�㷨���͡�ͶӰ�㷨��
/****************************************************/
void MATRIX_copy(float sourceMAT[4][4],float targetMAT[4][4]);//���󿽱�
void MATRIX_multiply(float MAT1[4][4],float MAT2[4][4],float newMAT[4][4]);//�������
_3Dzuobiao vector_matrix_MULTIPLY(_3Dzuobiao Source,float MAT[4][4]);//ʸ����������
void structure_3D(float MAT[4][4]);//���쵥λ����
void Translate3D(float MAT[4][4],int16_t tx,int16_t ty,int16_t tz);//ƽ�Ʊ任����
void  Scale_3D(float MAT[4][4],float sx,float sy,float sz);//�����任����
void Rotate_3D(float MAT[4][4],float ax,float ay,float az);//��ת�任����


/*****************************************************/
//3D-transform.c����
//		ͶӰ�㷨	��άת��ά����غ���		
/****************************************************/
_2Dzuobiao OrtProject(_3Dzuobiao Space);//����ͶӰ��Orthographic projection��
_2Dzuobiao	PerProject(_3Dzuobiao Space,int16_t  XO,int16_t  YO);//͸��ͶӰ��Perspective projection�

/*****************************************************/
//3D_Rotateapplitation.c ����
//���任�����㷨���͡�ͶӰ�㷨����Ӧ��
/****************************************************/
void Rotate_cube(float ax,float ay,float az);//��ת��������
void RateCube(float x,float y,float z,u16 color,uint16_t XO,uint16_t YO);//͸��ͶӰ
void RateCube_all(float x,float y,float z,float mx,float my,float mz,float bx,float by,float bz,
											int16_t XO,int16_t YO,u16 color);
void RotatePic32X32(unsigned char *dp,float ax,float ay,float az,
												u16 color,uint16_t XO,uint16_t YO);//����ά�ռ�����תһ��32x32���ַ���ͼ��
void Rotatecircle(float ax,float ay,float az,u16 r,u16 color,uint16_t XO,uint16_t YO);//����ά�ռ�����תһ��Բ��
#endif
