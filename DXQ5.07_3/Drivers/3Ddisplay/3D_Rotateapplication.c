/*******************************************************************************
* �ĵ�: 3D_Rotateapplitation.c
* ����: ִ��ִս
* 
* ����:
*				1.��άͼ�α任����
*       2.3D-transform.c�������任�㷨���͡�ͶӰ�㷨��
*       
*       3.3D_Rotateapplitation�ԡ��任�����㷨���͡�ͶӰ�㷨����Ӧ��
*       4.rotation_font3D.cʵ����ά�ռ�����תͼƬ���Ż��㷨��
*       5.��3D�㷨ѧϰ�ԡ�����STC��Ƭ����12864Һ����ʾ��ת�������ͼƬ���Ż��㷨����ʵ����
*						������Wu LianWei
*				7.���ĵ�Ϊ3D_Rotateapplitation�ԡ��任�����㷨���͡�ͶӰ�㷨����Ӧ��
*				8��ע�⣺�ӵ㵽ƽ��ľ��룬����Ļ�ϵ�����ͼת��ת�����ˣ�
								��ͼ��ɫʱ���Ÿĸ��ӵ㵽����ľ���FOCAL_DISTANCE�������任��������ֵ�Ĵ�С��XO,YO �Ĵ�С
								Ҫȷ��ͼ����ת�����в��ᳬ���߽磬��Ȼ�ͻ����룬���BUG��ʱֻ����һ�ֽ���취
*******************************************************************************/



#include "math.h"
#include "Display_3D.h"
#include "GUI.h"
//void RateCube(float x,float y,float z,uint16_t color,uint16_t XO,uint16_t YO);//͸��ͶӰ
//void RotatePic32X32(unsigned char *dp,float ax,float ay,float az,uint16_t color,uint16_t XO,uint16_t YO);//����ά�ռ�����תһ��32x32���ַ���ͼ��

/**********************************************************/
//**������Retate_cube
//**���ܣ���ת������
//**˵����  1����ת���������3D��ʾ������3Dͼ�α任�㷨��ͶӰ�㷨
//				  
//					 ��ѧ��д
//**���ߣ�  ִ��ִս
///**ʱ�䣺2015-11-30 
/***********************************************************/


#define  SIZE  8

_3Dzuobiao const Cube[8]=				//const �൱��51 �е�code����ʾ�����rom����Ϊֻ��
{																	
	{0,0,0},
	{16,0,0},
	{0,16,0},
	{16,16,0},
	
	{0,0,16},
	{16,0,16},							//ֻ��������������������,�൱�������εı߳�����������һ���������޸ĳ��̣��Լ�9��ɳ����λ�������
	{0,16,16},
	{16,16,16}
	
};

_3Dzuobiao const Triangle[3]=
{
	{4,2,0},
	{2,6,0},
	{6,6,0}
};

///**********************************************************/
///**����: Rotate_cube
///**���ܣ���ת�����壬͸��ͶӰ
///**˵����x,y,z,�ֱ�Ϊ��Ӧ���ϵ���ת�Ƕ�
//					colorΪ��ɫ
//					XO,YO Ϊԭ��

//  ֻ�ܰ���Ԥ��ķ�����ת
//					 ��ѧ��д
//**���ߣ�  ִ��ִս
///**ʱ�䣺2015-11-30
//�޸�ʱ�䣺 2017/2/5   23:00
//					����ԭ�����õ��β�
///***********************************************************/

void RateCube(float x,float y,float z,GUI_COLOR color,uint16_t XO,uint16_t YO)
{
	
	
//int16_t  XO;
//int16_t  YO;
	float gMAT[4][4];
	uint8_t i;
	_3Dzuobiao temp;
	_2Dzuobiao Cube_dis[8];
	
	structure_3D(gMAT);          	//����Ϊ��λ����
	Translate3D(gMAT,-8,-8,-8); 	//ƽ�Ʊ任����,��Ϊ�߳���һ��ĵ���ʱ��ͼ�������Լ���ת����ԭ��������
	Scale_3D(gMAT,2,2,2);		 	//�����任����
	Rotate_3D(gMAT,x,y,z);			//��ת�任����
	Translate3D(gMAT,0,0,0); 		//ƽ�Ʊ任����	
	//x:���ھ������ĵ�λ�ã��൱��Point0.z
	//y:���µ���λ�ã��������ʵ���޸�
//	XO=128;			//128  ����
//	YO=64+64;		//0 ʱ��ͱ���ʾ��y=0��
	
	for(i=0;i<8;i++)
{
		temp=vector_matrix_MULTIPLY(Cube[i],gMAT);		//ʸ����������
		Cube_dis[i]=PerProject(temp,XO,YO);				//����ͶӰ
		Cube_dis[i].x+=OLED_X_MAX;
		Cube_dis[i].y+=OLED_Y_MAX;		//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
		Cube_dis[i].x%=OLED_X_MAX;
		Cube_dis[i].y%=OLED_Y_MAX;
														//������Ļ�Ŀ��Ⱦͽ���ˣ�����˵���飬�����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
														//	��Ҫע��ͼ��Ҫ�󵽳���������
}

	GUI_SetColor(color);
	GUI_DrawLine(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[1].x,Cube_dis[1].y);
	GUI_DrawLine(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[2].x,Cube_dis[2].y);
	GUI_DrawLine(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[1].x,Cube_dis[1].y);
	GUI_DrawLine(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[2].x,Cube_dis[2].y);
	
	
	GUI_DrawLine(Cube_dis[0+4].x,Cube_dis[0+4].y,Cube_dis[1+4].x,Cube_dis[1+4].y);
	GUI_DrawLine(Cube_dis[0+4].x,Cube_dis[0+4].y,Cube_dis[2+4].x,Cube_dis[2+4].y);
	GUI_DrawLine(Cube_dis[3+4].x,Cube_dis[3+4].y,Cube_dis[1+4].x,Cube_dis[1+4].y);
	GUI_DrawLine(Cube_dis[3+4].x,Cube_dis[3+4].y,Cube_dis[2+4].x,Cube_dis[2+4].y);
	
	
	GUI_DrawLine(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[0+4].x,Cube_dis[0+4].y);
	GUI_DrawLine(Cube_dis[1].x,Cube_dis[1].y,Cube_dis[1+4].x,Cube_dis[1+4].y);
	GUI_DrawLine(Cube_dis[2].x,Cube_dis[2].y,Cube_dis[2+4].x,Cube_dis[2+4].y);
	GUI_DrawLine(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[3+4].x,Cube_dis[3+4].y);
		



}
///**********************************************************/
///**����: RotatePic32x32
///**���ܣ�����ά�ռ�����תһ��32x32���ַ���ͼ��
///**˵����1�������趨�ķ�ʽ�任ÿ��ͼƬ��ÿ��������꣬����ʾ
//				 2: ��ת�Ƕ�  0~360��
//				 3��azȡ��ֵΪ˳ʱ����ת
//					 ��ѧ��д		
//**���ߣ�  ִ��ִս
///**ʱ�䣺2015-11-30
//�޸�ʱ�䣺 2017/2/5   23:00
//					����ԭ�����õ��β�
///***********************************************************/


void RotatePic32X32(unsigned char *dp,float ax,float ay,float az,GUI_COLOR color,uint16_t XO,uint16_t YO,uint16_t ZO)
{
//	int16_t  XO;
//	int16_t  YO;
	uint8_t i,j,k;
	uint16_t temp;
	float gMAT[4][4];
	_3Dzuobiao Point0;
	_3Dzuobiao Point1;
	_2Dzuobiao PointDis;
	
	structure_3D(gMAT);						//������λ����
	Translate3D(gMAT,-16,-16,-ZO); 		//ƽ�Ʊ任����
	Scale_3D(gMAT,1,1,1);		 			//�����任����
	Rotate_3D(gMAT,ax,ay,az);				//��ת�任����
	Translate3D(gMAT,16,16,ZO); 			//ƽ�Ʊ任����	
//	XO=128;
//	YO=64;
	
	for(j=0;j<32;j++)
	{
		for(i=0;i<4;i++)
		{
			for(k=0;k<8;k++)
			{
				temp=0x01<<k;				//_crol_(0x01,k);
				if(*(dp+i)&temp)
				{
					Point0.x=(i*8)+(7-k);
					Point0.y=j;
					Point0.z=0;
					
					Point1=vector_matrix_MULTIPLY(Point0,gMAT);			//ʸ����������
					PointDis=PerProject(Point1,XO,YO);					//ӳ��ͶӰ
					PointDis.x+=OLED_X_MAX;
					PointDis.y+=OLED_Y_MAX;								//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
					PointDis.x%=OLED_X_MAX;								//������Ļ�Ŀ��Ⱦͽ���ˣ�����˵���飬�����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
					PointDis.y%=OLED_Y_MAX;								//��Ҫע��ͼ��Ҫ�󵽳���������
					GUI_DrawPoint(PointDis.x,PointDis.y,color);
				}
			}
		}
		dp+=32;
	}	
}