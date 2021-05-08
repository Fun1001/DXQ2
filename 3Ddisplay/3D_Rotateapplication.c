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


//#include "gui.h"
#include "math.h"
#include "led.h"

#include "Display_3D.h"
//#include"Transform_3D.h"
#include "lcd_drive.h"
#include "config.h"
//#include "front.h"





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
	
//	{-1,-1,-1},
//{1,-1,-1},
//{1,-1,1},
//{-1,-1,1}, 
//{-1, 1,-1},
//{1, 1,-1},
//{1, 1,1},
//{-1, 1,1}
};

_3Dzuobiao const Triangle[3]=
{
	{4,2,0},
	{2,6,0},
	{6,6,0}
};

///**********************************************************/
///**����: Rotate_cube
///**���ܣ���ת������
///**˵����

//					 ��ѧ��д
//**���ߣ�  ִ��ִս
///**ʱ�䣺2015-11-30
//�޸�ʱ�䣺 2017/2/5   23:00
//					���ԭ�����õ��β�
///***********************************************************/

void Rotate_cube(float ax,float ay,float az)   //��ת��������
{	u8 i;
		float gMAT[4][4];
	_3Dzuobiao temp;
	_2Dzuobiao Cube_dis[8];
	_2Dzuobiao Triangle_dis[3];
	
	structure_3D(gMAT);          //����Ϊ��λ����
	Translate3D(gMAT,-4,-4,-4); //ƽ�Ʊ任����
	Scale_3D(gMAT,5,5,5);		 //�����任����
	Rotate_3D(gMAT,ax,ay,az);			//��ת�任����
	Translate3D(gMAT,64,32,32); //ƽ�Ʊ任����	
	
	for(i=0;i<SIZE;i++)
	{
		temp=vector_matrix_MULTIPLY(Cube[i],gMAT);//ʸ����������,�������������뵥λ�������
		Cube_dis[i]=OrtProject(temp);//����ͶӰ
		 Cube_dis[i].x+=240;
		Cube_dis[i].y+=432;//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
											//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
											//	��Ҫע��ͼ��Ҫ�󵽳���������											
	}
	for(i=0;i<3;i++)
	{
			temp=vector_matrix_MULTIPLY(Triangle[i],gMAT);//ʸ����������
			Triangle_dis[i]=OrtProject(temp);//����ͶӰ
		 Cube_dis[i].x+=240;
		Cube_dis[i].y+=432;//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
											//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
											//	��Ҫע��ͼ��Ҫ�󵽳���������
		
	}
	
	 GUI_Line(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[1].x,Cube_dis[1].y,BLACK);
	 GUI_Line(Cube_dis[1].x,Cube_dis[1].y,Cube_dis[2].x,Cube_dis[2].y,BLACK);
	 GUI_Line(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[0].x,Cube_dis[0].y,BLACK);
	 GUI_Line(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[2].x,Cube_dis[2].y,BLACK);
	
	
	 GUI_Line(Cube_dis[0+4].x,Cube_dis[0+4].y,Cube_dis[1+4].x,Cube_dis[1+4].y,BLACK);
	 GUI_Line(Cube_dis[1+4].x,Cube_dis[1+4].y,Cube_dis[2+4].x,Cube_dis[2+4].y,BLACK);
	 GUI_Line(Cube_dis[3+4].x,Cube_dis[3+4].y,Cube_dis[0+4].x,Cube_dis[0+4].y,BLACK);
	 GUI_Line(Cube_dis[3+4].x,Cube_dis[3+4].y,Cube_dis[2+4].x,Cube_dis[2+4].y,BLACK);
	
	
	 GUI_Line(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[0+4].x,Cube_dis[0+4].y,BLACK);
	 GUI_Line(Cube_dis[1].x,Cube_dis[1].y,Cube_dis[1+4].x,Cube_dis[1+4].y,BLACK);
	 GUI_Line(Cube_dis[2].x,Cube_dis[2].y,Cube_dis[2+4].x,Cube_dis[2+4].y,BLACK);
	 GUI_Line(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[3+4].x,Cube_dis[3+4].y,BLACK);
	
	 GUI_Line(Triangle_dis[0].x,Triangle_dis[0].y,Triangle_dis[1].x,Triangle_dis[1].y,BLACK);
	 GUI_Line(Triangle_dis[0].x,Triangle_dis[0].y,Triangle_dis[2].x,Triangle_dis[2].y,BLACK);
	 GUI_Line(Triangle_dis[1].x,Triangle_dis[1].y,Triangle_dis[2].x,Triangle_dis[2].y,BLACK);
	 //GUI_Line(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[2].x,Cube_dis[2].y,BLACK);
	
}

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
//					���ԭ�����õ��β�
///***********************************************************/

void RateCube(float x,float y,float z,u16 color,uint16_t XO,uint16_t YO)
{
	
	
//int16_t  XO;
//int16_t  YO;
	float gMAT[4][4];
	u8 i;
	_3Dzuobiao temp;
	_2Dzuobiao Cube_dis[8];
	
	structure_3D(gMAT);          //����Ϊ��λ����
	Translate3D(gMAT,-8,-8,-8); //ƽ�Ʊ任����,��Ϊ�߳���һ��ĵ���ʱ��ͼ�������Լ���ת����ԭ��������
	Scale_3D(gMAT,4,4,4);		 //�����任����
	Rotate_3D(gMAT,x,y,z);			//��ת�任����
Translate3D(gMAT,8,8,8); //ƽ�Ʊ任����	
	
//	XO=128;		//128  ����
//	YO=64+64;		//0 ʱ��ͱ���ʾ��y=0��
	
	for(i=0;i<8;i++)
{
		temp=vector_matrix_MULTIPLY(Cube[i],gMAT);//ʸ����������
		Cube_dis[i]=	PerProject(temp,XO,YO);//����ͶӰ
	  Cube_dis[i].x+=240;
		Cube_dis[i].y+=432;//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
											//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
											//	��Ҫע��ͼ��Ҫ�󵽳���������
}


   GUI_Line(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[1].x,Cube_dis[1].y,color);
	 GUI_Line(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[2].x,Cube_dis[2].y,color);
	 GUI_Line(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[1].x,Cube_dis[1].y,color);
	 GUI_Line(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[2].x,Cube_dis[2].y,color);
	
	
	 GUI_Line(Cube_dis[0+4].x,Cube_dis[0+4].y,Cube_dis[1+4].x,Cube_dis[1+4].y,color);
	 GUI_Line(Cube_dis[0+4].x,Cube_dis[0+4].y,Cube_dis[2+4].x,Cube_dis[2+4].y,color);
	 GUI_Line(Cube_dis[3+4].x,Cube_dis[3+4].y,Cube_dis[1+4].x,Cube_dis[1+4].y,color);
	 GUI_Line(Cube_dis[3+4].x,Cube_dis[3+4].y,Cube_dis[2+4].x,Cube_dis[2+4].y,color);
	
	
	 GUI_Line(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[0+4].x,Cube_dis[0+4].y,color);
	 GUI_Line(Cube_dis[1].x,Cube_dis[1].y,Cube_dis[1+4].x,Cube_dis[1+4].y,color);
	 GUI_Line(Cube_dis[2].x,Cube_dis[2].y,Cube_dis[2+4].x,Cube_dis[2+4].y,color);
	 GUI_Line(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[3+4].x,Cube_dis[3+4].y,color);
		



}


///**********************************************************/
///**����: Rotate_cube_all
///**���ܣ�������ת�����壬͸��ͶӰ��
///**˵����x,y,z,�ֱ�Ϊ��Ӧ���ϵ���ת�Ƕ�
//				mx,my,mz Ϊƽ�Ƶ�λ
//				bx,by,bz Ϊ��Ӧ�ߵı任����
//				XO,YO Ϊԭ��
//					colorΪ��ɫ

//  ֻ�ܰ���Ԥ��ķ�����ת
//					 ��ѧ��д
//**���ߣ�  ִ��ִս
///**ʱ�䣺2015-11-30
//�޸�ʱ�䣺 2017/2/5   23:00
//					���ԭ�����õ��β�
///***********************************************************/
void RateCube_all(float x,float y,float z,float mx,float my,float mz,float bx,float by,float bz,
											int16_t XO,int16_t YO,u16 color)
{
	
	

	float gMAT[4][4];
	u8 i;
	_3Dzuobiao temp;
	_2Dzuobiao Cube_dis[8];
	
	structure_3D(gMAT);         //����Ϊ��λ����
	Translate3D(gMAT,mx,my,mz); //ƽ�Ʊ任����
	Scale_3D(gMAT,bx,by,bz);		 		//�����任����
	Rotate_3D(gMAT,x,y,z);			//��ת�任����
	Translate3D(gMAT,0,0,32);		//ƽ�Ʊ任����	
	
	for(i=0;i<8;i++)
{
		temp=vector_matrix_MULTIPLY(Cube[i],gMAT);//ʸ����������
		Cube_dis[i]=	PerProject(temp,XO,YO);//����ͶӰ
	  Cube_dis[i].x+=240;
		Cube_dis[i].y+=480;//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
											//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
											//	��Ҫע��ͼ��Ҫ�󵽳���������
}


   GUI_Line(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[1].x,Cube_dis[1].y,color);
	 GUI_Line(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[2].x,Cube_dis[2].y,color);
	 GUI_Line(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[1].x,Cube_dis[1].y,color);
	 GUI_Line(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[2].x,Cube_dis[2].y,color);
	
	
	 GUI_Line(Cube_dis[0+4].x,Cube_dis[0+4].y,Cube_dis[1+4].x,Cube_dis[1+4].y,color);
	 GUI_Line(Cube_dis[0+4].x,Cube_dis[0+4].y,Cube_dis[2+4].x,Cube_dis[2+4].y,color);
	 GUI_Line(Cube_dis[3+4].x,Cube_dis[3+4].y,Cube_dis[1+4].x,Cube_dis[1+4].y,color);
	 GUI_Line(Cube_dis[3+4].x,Cube_dis[3+4].y,Cube_dis[2+4].x,Cube_dis[2+4].y,color);
	
	
	 GUI_Line(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[0+4].x,Cube_dis[0+4].y,color);
	 GUI_Line(Cube_dis[1].x,Cube_dis[1].y,Cube_dis[1+4].x,Cube_dis[1+4].y,color);
	 GUI_Line(Cube_dis[2].x,Cube_dis[2].y,Cube_dis[2+4].x,Cube_dis[2+4].y,color);
	 GUI_Line(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[3+4].x,Cube_dis[3+4].y,color);
		



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
//					���ԭ�����õ��β�
///***********************************************************/


void RotatePic32X32(unsigned char *dp,float ax,float ay,float az,u16 color,uint16_t XO,uint16_t YO)
{
//	int16_t  XO;
//	int16_t  YO;
	u8 i,j,k;
	u16 temp;
	float gMAT[4][4];
	_3Dzuobiao Point0;
	_3Dzuobiao Point1;
	_2Dzuobiao PointDis;
	
	structure_3D(gMAT);						//������λ����
	Translate3D(gMAT,-30,-30,0); 	//ƽ�Ʊ任����
	//Scale_3D(gMAT,1,1,1);		 		//�����任����
	Rotate_3D(gMAT,ax,ay,az);			//��ת�任����
	Translate3D(gMAT,0,0,32); 	//ƽ�Ʊ任����	
//	XO=128;
//	YO=64;
	
	for(i=0;i<4;i++)
	{
		for(k=0;k<8;k++)
		{
			temp=0x01<<k;//_crol_(0x01,k);
			for(j=0;j<32;j++)
			{
				if(*(dp+j)&temp)
				{
					Point0.x=j;
					Point0.y=(i*8)+k;
					Point0.z=-24;
					
					Point1=vector_matrix_MULTIPLY(Point0,gMAT);	//ʸ����������
					PointDis=PerProject(Point1,XO,YO);					//ӳ��ͶӰ
					  PointDis.x+=240;
						PointDis.y+=480;//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
											//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
											//	��Ҫע��ͼ��Ҫ�󵽳���������
					GUI_Point(PointDis.x,PointDis.y,color);
				}
			}
		}
		dp+=32;
	}
	
	
	
}



///**********************************************************/
///**����: Rotatecircle
///**���ܣ�����ά�ռ�����תһ��Բ��
///**˵����1�������趨�ķ�ʽ�任ÿ��ͼƬ��ÿ��������꣬����ʾ
//				 2: ��ת�Ƕ�  0~360��
//				 3��azȡ��ֵΪ˳ʱ����ת
//					 ��ѧ��д		
//**���ߣ�  ִ��ִս
///**ʱ�䣺2015-11-30
//�޸�ʱ�䣺 2017/2/5   23:00
//					���ԭ�����õ��β�
///***********************************************************/

void Rotatecircle(float ax,float ay,float az,u16 r,u16 color,uint16_t XO,uint16_t YO)
{   
//	int16_t  XO;
//	int16_t  YO;
	u8 i,j,k;
	u16 temp;
	float gMAT[4][4];
	_3Dzuobiao Point0;
	_3Dzuobiao Point3;
	
	_3Dzuobiao Point1;
	_2Dzuobiao PointDis;
	
	structure_3D(gMAT);							//���쵥λ����
	Translate3D(gMAT,-60,-60,-60); 	//ƽ�Ʊ任����
	//Scale_3D(gMAT,1,1,1);				 	//�����任����
	Rotate_3D(gMAT,ax,ay,az);				//��ת�任����
	Translate3D(gMAT,30,30,30);			//ƽ�Ʊ任����	
//	XO=120;													//��������
//	YO=150 ;
	
	
	
	
  
        for(i=0;i<	r+r+1;i++)
        {
					
					
					Point0.x=i;
					Point0.y=r-sqrt(r*r-(r-i)*(r-i));
					Point0.z=0;
					Point3.x=i;
					Point3.y=r+sqrt(r*r-(r-i)*(r-i));
					Point3.z=0;
					
					Point1=vector_matrix_MULTIPLY(Point0,gMAT);	//ʸ����������
					//	Translate3D(gMAT,30,30,60); //ƽ�Ʊ任����	
					
					PointDis=PerProject(Point1,XO,YO);					//ӳ��ͶӰ
					 //PointDis=OrtProject(Point1);
					PointDis.x+=240;
					PointDis.y+=432;//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
											//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
											//	��Ҫע��ͼ��Ҫ�󵽳���������
					GUI_Point(PointDis.x,PointDis.y,color);
					
					Point1=vector_matrix_MULTIPLY(Point3,gMAT);	//ʸ����������
						//Translate3D(gMAT,30,30,60); //ƽ�Ʊ任����	
					PointDis=PerProject(Point1,XO,YO);					//ӳ��ͶӰ
					 //PointDis=OrtProject(Point3);
					PointDis.x+=240;
					PointDis.y+=432;//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
											//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
											//	��Ҫע��ͼ��Ҫ�󵽳���������
						GUI_Point(PointDis.x,PointDis.y,color);
                         
        }
	
	
		
	
	
	
	
}



