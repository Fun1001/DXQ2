
/*******************************************/
//
//描述：移植ZLG_GUI后将以前的3D显示移植一下，
//			改为使用ZLG_GUI的绘图函数来显示
//
//备注：本3D转换与显示函数为以前学习和改编
//			具体来源请看详细文档描述


//作者：	执念执战
//时间：2017/2/5  	21：50
//******************************************/


#ifndef _Display_3D_H
#define _Display_3D_H

#include "stm32f4xx_hal.h"
#include "GUI.h"

#define OLED_X_MAX 128
#define OLED_Y_MAX 64



///************************************************
//					坐标结构体
//					用于2D 和3D坐标
//*************************************************/
typedef struct{
	unsigned int  x;
	unsigned int  y;
}_2Dzuobiao ;				//不能直接用数字揩开头来做结构体的名称，所以前面加个—

typedef struct
{
	float x;
	float y;
	float z;
}_3Dzuobiao;

/*****************************************************/
//3D-transform.c 部分
//“变换算法”和“投影算法”
/****************************************************/
void MATRIX_copy(float sourceMAT[4][4],float targetMAT[4][4]);//矩阵拷贝
void MATRIX_multiply(float MAT1[4][4],float MAT2[4][4],float newMAT[4][4]);//矩阵相乘
_3Dzuobiao vector_matrix_MULTIPLY(_3Dzuobiao Source,float MAT[4][4]);//矢量与矩阵相乘
void structure_3D(float MAT[4][4]);//构造单位矩阵
void Translate3D(float MAT[4][4],int16_t tx,int16_t ty,int16_t tz);//平移变换矩阵
void  Scale_3D(float MAT[4][4],float sx,float sy,float sz);//比例变换矩阵
void Rotate_3D(float MAT[4][4],float ax,float ay,float az);//旋转变换矩阵


/*****************************************************/
//3D-transform.c部分
//		投影算法	三维转二维的相关函数		
/****************************************************/
_2Dzuobiao OrtProject(_3Dzuobiao Space);//正射投影（Orthographic projection）
_2Dzuobiao	PerProject(_3Dzuobiao Space,int16_t  XO,int16_t  YO);//透视投影（Perspective projection?

/*****************************************************/
//3D_Rotateapplitation.c 部分
//“变换矩阵算法”和“投影算法”的应用
/****************************************************/
void RateCube(float x,float y,float z,GUI_COLOR color,uint16_t XO,uint16_t YO);//透视投影
void RotatePic32X32(unsigned char *dp,float ax,float ay,float az,GUI_COLOR color,uint16_t XO,uint16_t YO,uint16_t ZO);//在三维空间中旋转一个32x32的字符或图形
#endif
