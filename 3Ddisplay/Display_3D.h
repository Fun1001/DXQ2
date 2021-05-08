
/*******************************************/
//
//ÃèÊö£ºÒÆÖ²ZLG_GUIºó½«ÒÔÇ°µÄ3DÏÔÊ¾ÒÆÖ²Ò»ÏÂ£¬
//			¸ÄÎªÊ¹ÓÃZLG_GUIµÄ»æÍ¼º¯ÊıÀ´ÏÔÊ¾
//
//±¸×¢£º±¾3D×ª»»ÓëÏÔÊ¾º¯ÊıÎªÒÔÇ°Ñ§Ï°ºÍ¸Ä±à
//			¾ßÌåÀ´Ô´Çë¿´ÏêÏ¸ÎÄµµÃèÊö


//×÷Õß£º	Ö´ÄîÖ´Õ½
//Ê±¼ä£º2017/2/5  	21£º50
//******************************************/


#ifndef _Display_3D_H
#define _Display_3D_H

#include "stm32f10x.h"



///************************************************
//					×ø±ê½á¹¹Ìå
//					ÓÃÓÚ2D ºÍ3D×ø±ê
//*************************************************/
typedef struct{
	unsigned int  x;
	unsigned int  y;
}_2Dzuobiao ;				//²»ÄÜÖ±½ÓÓÃÊı×Ö¿«¿ªÍ·À´×ö½á¹¹ÌåµÄÃû³Æ£¬ËùÒÔÇ°Ãæ¼Ó¸ö¡ª¡_

typedef struct
{
	float x;
	float y;
	float z;
}_3Dzuobiao;

/*****************************************************/
//3D-transform.c ²¿·Ö
//¡°±ä»»Ëã·¨¡±ºÍ¡°Í¶Ó°Ëã·¨¡±
/****************************************************/
void MATRIX_copy(float sourceMAT[4][4],float targetMAT[4][4]);//¾ØÕó¿½±´
void MATRIX_multiply(float MAT1[4][4],float MAT2[4][4],float newMAT[4][4]);//¾ØÕóÏà³Ë
_3Dzuobiao vector_matrix_MULTIPLY(_3Dzuobiao Source,float MAT[4][4]);//Ê¸Á¿Óë¾ØÕóÏà³Ë
void structure_3D(float MAT[4][4]);//¹¹Ôìµ¥Î»¾ØÕó
void Translate3D(float MAT[4][4],int16_t tx,int16_t ty,int16_t tz);//Æ½ÒÆ±ä»»¾ØÕó
void  Scale_3D(float MAT[4][4],float sx,float sy,float sz);//±ÈÀı±ä»»¾ØÕó
void Rotate_3D(float MAT[4][4],float ax,float ay,float az);//Ğı×ª±ä»»¾ØÕó


/*****************************************************/
//3D-transform.c²¿·Ö
//		Í¶Ó°Ëã·¨	ÈıÎ¬×ª¶şÎ¬µÄÏà¹Øº¯Êı		
/****************************************************/
_2Dzuobiao OrtProject(_3Dzuobiao Space);//ÕıÉäÍ¶Ó°£¨Orthographic projection£©
_2Dzuobiao	PerProject(_3Dzuobiao Space,int16_t  XO,int16_t  YO);//Í¸ÊÓÍ¶Ó°£¨Perspective projection£

/*****************************************************/
//3D_Rotateapplitation.c ²¿·Ö
//¡°±ä»»¾ØÕóËã·¨¡±ºÍ¡°Í¶Ó°Ëã·¨¡±µÄÓ¦ÓÃ
/****************************************************/
void Rotate_cube(float ax,float ay,float az);//Ğı×ªµÄÁ¢·½Ìå
void RateCube(float x,float y,float z,u16 color,uint16_t XO,uint16_t YO);//Í¸ÊÓÍ¶Ó°
void RateCube_all(float x,float y,float z,float mx,float my,float mz,float bx,float by,float bz,
											int16_t XO,int16_t YO,u16 color);
void RotatePic32X32(unsigned char *dp,float ax,float ay,float az,
												u16 color,uint16_t XO,uint16_t YO);//ÔÚÈıÎ¬¿Õ¼äÖĞĞı×ªÒ»¸ö32x32µÄ×Ö·û»òÍ¼ĞÎ
void Rotatecircle(float ax,float ay,float az,u16 r,u16 color,uint16_t XO,uint16_t YO);//ÔÚÈıÎ¬¿Õ¼äÖĞĞı×ªÒ»¸öÔ²ĞÎ
#endif
