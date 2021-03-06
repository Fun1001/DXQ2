/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gpio.h"
#include "GUI.h"
#include	<stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "tim.h"
#include "DS_18B20.h"
#include "MPU6050.h"
#include "Display_3D.h"
#include "COMM.h"
#include "ESP01.h"
//#include "Display_3D.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern GUI_FLASH const GUI_FONT GUI_FontHZ_KaiTi_20;
extern GUI_FLASH const GUI_FONT GUI_FontHZ_nameKaiTi_16;
extern GUI_FLASH const GUI_FONT GUI_FontHZ_KaiTi_16;
extern GUI_CONST_STORAGE GUI_BITMAP bmFunJC;
extern GUI_CONST_STORAGE GUI_BITMAP bmSunHR;
extern GUI_FLASH const GUI_FONT GUI_FontHZ_SimSun_12;


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
#define WS_LOGO 0		//??????????
#define WS_GUI1 1
#define WS_GUI2 2
#define WS_GUI3 3
#define WS_GUI4 4

//??????????????????????????????
#define MAX_DATA_LEN 77 //????????
uint8_t g_fax_data[MAX_DATA_LEN];
uint8_t g_fay_data[MAX_DATA_LEN];
uint8_t g_faz_data[MAX_DATA_LEN];
uint8_t g_temp_data[MAX_DATA_LEN];

#define LINE_temp 0
#define LINE_FAX  1
#define LINE_FAY	2
#define LINE_FAZ	3
#define LINE_3D 	4
uint8_t g_line_idx=LINE_temp;

int g_ws = WS_LOGO;
uint32_t intick = 0;

volatile float temp=0;

uint32_t beeptick=0;

uint8_t mpuwarn =0;//????????
uint8_t tempwarn=0;
uint8_t keyflag=0;//??????????0  ??????1
uint8_t pageidx=0;//????

uint32_t warntick=0;//??????????
uint32_t keytick=0; //??????????

uint32_t scantime=50;//????????????
 
float temp_alarm_max=32;	//????????????
uint16_t g_upstep=100;		//????????????
uint8_t g_mpustep=7;			//??????????
uint8_t g_warntime=30;		//????????
uint8_t init8266=1;	 //????wifi??????????????
uint8_t g_bUping=0;//???????????? 
uint8_t onenet=0;	 //??????onenet??????????
uint8_t g_paridx=0;//??????????????????????????????????
/* USER CODE END Variables */
/* Definitions for MainTask */
osThreadId_t MainTaskHandle;
const osThreadAttr_t MainTask_attributes = {
  .name = "MainTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for KeyTask */
osThreadId_t KeyTaskHandle;
const osThreadAttr_t KeyTask_attributes = {
  .name = "KeyTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for UartTask */
osThreadId_t UartTaskHandle;
const osThreadAttr_t UartTask_attributes = {
  .name = "UartTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for GUITask */
osThreadId_t GUITaskHandle;
const osThreadAttr_t GUITask_attributes = {
  .name = "GUITask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for DataTask */
osThreadId_t DataTaskHandle;
const osThreadAttr_t DataTask_attributes = {
  .name = "DataTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void WSLogo(void);
void DrawLogo(void);
void DrawGUI1(void);
void DrawGUI2(void);
void DrawGUI3(void);
void DrawGUI4(void);
void Beep(int time,int tune);
void DispSeg(uint8_t num[4],uint8_t dot);
void BeepDone(void);
int InitESP8266(void);

/* USER CODE END FunctionPrototypes */

void StartMainTask(void *argument);
void StartKeyTask(void *argument);
void StartUartTask(void *argument);
void StartGUITask(void *argument);
void StartDataTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of MainTask */
  MainTaskHandle = osThreadNew(StartMainTask, NULL, &MainTask_attributes);

  /* creation of KeyTask */
  KeyTaskHandle = osThreadNew(StartKeyTask, NULL, &KeyTask_attributes);

  /* creation of UartTask */
  UartTaskHandle = osThreadNew(StartUartTask, NULL, &UartTask_attributes);

  /* creation of GUITask */
  GUITaskHandle = osThreadNew(StartGUITask, NULL, &GUITask_attributes);

  /* creation of DataTask */
  DataTaskHandle = osThreadNew(StartDataTask, NULL, &DataTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartMainTask */
/**
  * @brief  Function implementing the MainTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartMainTask */
void StartMainTask(void *argument)
{
  /* USER CODE BEGIN StartMainTask */
	uint8_t num[4]={0};
	
  /* Infinite loop */
  for(;;)
  {
		switch(g_ws)
		{
			case WS_LOGO:
					WSLogo();
			  break;
			default:
				SetLeds(0);//??LOGO????LED????
				break;
		}
		
		//??????????
		if((tempwarn||mpuwarn)&&g_warntime>0)
		{
			if(0==warntick)
				warntick=osKernelGetTickCount();
			else if(osKernelGetTickCount()>=warntick+1000*g_warntime)//????????30s
			{	
				tempwarn=mpuwarn=0;
				warntick=0;
				keyflag=0;		//????????
			}
			else			
			{
				keyflag=1;		//????????
				uint32_t tic=warntick+1000*g_warntime-osKernelGetTickCount();
				num[0]=(tic/10000)%10;
				num[1]=(tic/1000)%10;
				num[2]=(tic/100)%10;
				num[3]=(tic/10)%10;
				
				//??????????
				if(tempwarn==1)
				{
					if(num[2]==1||num[2]==4||num[2]==7)//????????????
					Beep(100,num[2]);
				} 
				if(mpuwarn==1)
				{
					if(num[2]==2||num[2]==5||num[2]==1)//????????????
					Beep(150,num[2]);
				}
			}
				
		}
		else
			num[0]=num[1]=num[2]=num[3]=' ';
		
		DispSeg(num,2);
		BeepDone();

		osDelay(1);
  }
  /* USER CODE END StartMainTask */
}

/* USER CODE BEGIN Header_StartKeyTask */
/**
* @brief Function implementing the KeyTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartKeyTask */
void StartKeyTask(void *argument)
{
  /* USER CODE BEGIN StartKeyTask */
  /* Infinite loop */
	
  for(;;)
  {	
		uint8_t key=KeyScan();
		if(keyflag)				//????????????????????
		{
			if(key==0x0f)
			{
				if(0==keytick)
					keytick = osKernelGetTickCount();
				else if(osKernelGetTickCount()>=keytick+3000)		//??????3s
				{
					tempwarn = mpuwarn = 0;
					warntick=0;
					keyflag=0;
					keytick=0;
				}
			}
			osDelay(1);
		}
		if(keyflag==0)		//????????
		{
				
				if(key>0)
					printf("%02X\n",key);//??????????
				
				switch(g_ws)
				{
					case WS_LOGO :
						if(KEY5==key)
						{
							g_ws=WS_GUI1;
							intick=0;
						}
						break;
					case WS_GUI1:
						if(KEY1==key)
							g_ws=WS_GUI4;
						else if(KEY4==key)
							g_ws=WS_GUI2;
						
						else if(KEY2==key) //????????
						{
							if(pageidx>0)
								--pageidx;
							else if(pageidx==0)
								pageidx=2;
						}
						else if(KEY3==key)
						{
							if(pageidx<2)
								++pageidx;
							else if(pageidx==2)
								pageidx=0;
						}
						//????Logo
						else if(KEY6==key)
							g_ws=WS_LOGO;
						break;
					case WS_GUI2:
						if(KEY1==key)
							g_ws=WS_GUI1;
						else if(KEY4==key)
						{
							g_ws=WS_GUI3;
//							if(init8266==1 && esp8266.bconn==0)	//??????????????
//							{
								init8266=InitESP8266();
//							}					
						} 
						else if(KEY3==key)
						{	
						if(g_line_idx<LINE_3D)
								++g_line_idx;
						}
						else if(KEY2==key)
						{	
						if(g_line_idx>LINE_temp)
								--g_line_idx;
						}
						else if(KEY6==key)
							g_ws=WS_LOGO;
						else if(KEY5==key)
						{
							if(scantime==50)
								scantime=1000;
							else
								scantime=50;
						}
						break; 
					case WS_GUI3:
						if(KEY1==key)
							g_ws=WS_GUI2;
						else if(KEY2==key)
							g_bUping=1;
						else if(KEY3==key)
							g_bUping=0;
						else if(KEY4==key)
							g_ws=WS_GUI4;
						else if(KEY6==key)
							g_ws=WS_LOGO;
						else if(KEY5==key)
						{
							if(0==pageidx)
							{
								//??????ESP8266????????
//							if(init8266==1 && esp8266.bconn==0)	//??????????????
//							{
								init8266=InitESP8266();
//							}
							}
						}
						break;
					case WS_GUI4:
						if(KEY1==key)
						{
							g_ws=WS_GUI3;	
//							if(init8266==1)	//??????????????
//							{
								init8266=InitESP8266();
//							}
						}
						else if(KEY4==key)
							g_ws=WS_GUI1;
						else if(KEY2==key)
						{
							if(0==g_paridx)
							{
								if(temp_alarm_max>0)
									temp_alarm_max-=1;
							}
							if(1==g_paridx)
							{
								if(g_mpustep>0)
									--g_mpustep;
							}
							if(2==g_paridx)
							{
								if(g_warntime>0)
									--g_warntime;
							}
							if(3==g_paridx)
							{
								if(g_upstep>100)
									g_upstep-=100;
							}
						}
						else if(KEY3==key)
						{
							if(0==g_paridx)
							{
								if(temp_alarm_max<90)
									temp_alarm_max+=1;
							}
							if(1==g_paridx)
							{
								if(g_mpustep<9)
									++g_mpustep;
							}
							if(2==g_paridx)
							{
								if(g_warntime<60)
									++g_warntime;
							}
							if(3==g_paridx)
							{
								if(g_upstep<10000)
									g_upstep+=100;
							}
						}
						else if(KEY6==key)
							g_ws=WS_LOGO;
						else if(KEY5==key)
						{
							++g_paridx;
							g_paridx%=4;
						}
						break;
					default:
						if(KEY6==key)
							g_ws=WS_LOGO;
						break;
				}
				
				osDelay(1);
			}
		}
  /* USER CODE END StartKeyTask */
}

/* USER CODE BEGIN Header_StartUartTask */
/**
* @brief Function implementing the UartTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartUartTask */
void StartUartTask(void *argument)
{
  /* USER CODE BEGIN StartUartTask */
	StartRecvUart1();
	ESP_Init();
  /* Infinite loop */
  for(;;)
  {
		//????1????????
		if(recv1_len>0)
		{
			printf("%s",recv1_buff);
			recv1_len=0;
		}
		
		//ESP????????????
		ESP_Proc();
		if(esp8266.recv_len>0)
		{
			printf("%s",esp8266.recv_data);
			
			char *pb = (char *)esp8266.recv_data;
			char buf[40];
			if('Q' == pb[0] && 'P' == pb[1] && 'A' == pb[2] && 'R' == pb[3])
			{
				//??????????????
				sprintf(buf,"P1:%.0f, P2:%d, P3:%d, P4:%d\n",temp_alarm_max,g_mpustep,g_warntime,g_upstep);
				USendStr(&huart6, (uint8_t *)buf,strlen(buf));
			}				
			else if('P' == pb[0] && '1' == pb[1] && ':' == pb[2])
			{
				//????????
				temp_alarm_max = atof(pb+3);
				pb = strstr(pb,"P2:");
				if(pb)
				{
					g_mpustep = atoi(pb+3);
					
					pb = strstr(pb,"P3:");
					if(pb)
					{
						g_warntime = atoi(pb+3);
						
						pb = strstr(pb,"P4:");
						if(pb)
						{
							g_upstep = atoi(pb+3);
							USendStr(&huart6,(uint8_t)("OK\n"),3);	//????????????
						}

					}
				}
			}
			else if('s' == pb[0] && 't' == pb[1] && 'o' == pb[2] && 'p' == pb[3])	//????????
			{
				g_bUping=0;
			}
			else if('s' == pb[0] && 't' == pb[1] && 'a' == pb[2] && 'r' == pb[3] && 't' == pb[4])	//????????
			{
				g_bUping=1;
			}
			else if('t' == pb[0] && 'e' == pb[1] && 'm' == pb[2] && 'p' == pb[3] )	//????????
			{
				temp_alarm_max = atof(pb+4);
			}
			else if('m' == pb[0] && 'p' == pb[1] && 'u' == pb[2] && 's' == pb[3] )	//????????????
			{
				g_mpustep = atof(pb+4);
			}
			else if('w' == pb[0] && 'a' == pb[1] && 'n' == pb[2] && 't' == pb[3] )	//????????????
			{
				g_warntime = atof(pb+4);
			}
			else if('u' == pb[0] && 'p' == pb[1] && 't' == pb[2] && 'm' == pb[3] )	//????????????
			{
				g_upstep = atof(pb+4)*100;
			}
			esp8266.recv_len=0;
		}
		
    osDelay(1);
  }
  /* USER CODE END StartUartTask */
}

/* USER CODE BEGIN Header_StartGUITask */
/**
* @brief Function implementing the GUITask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGUITask */
void StartGUITask(void *argument)
{
  /* USER CODE BEGIN StartGUITask */
	GUI_Init();//??????

  /* Infinite loop */
  for(;;)
  {
		switch(g_ws)
		{
			case WS_LOGO:
					DrawLogo();
				break;			
			case WS_GUI1:
					DrawGUI1();
				break;	
			case WS_GUI2:
					DrawGUI2();
				break;
			case WS_GUI3:
					DrawGUI3();
				break;
			case WS_GUI4:
					DrawGUI4();
				break;
			default:
				break;
		}
		
    osDelay(100);
  }
  /* USER CODE END StartGUITask */
}

/* USER CODE BEGIN Header_StartDataTask */
/**
* @brief Function implementing the DataTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDataTask */
void StartDataTask(void *argument)
{
  /* USER CODE BEGIN StartDataTask */
	osDelay(1000);
	ds18b20_init();
	
	uint8_t idx=0;//????????
	uint8_t temp_idx=0;//????????????
	

	
	uint8_t mpuok=MPU_init();
	uint8_t cnt=0;
	uint32_t dstick=0;
	uint32_t newdstick=0;
	uint32_t mputick=0;
	uint32_t uptick=0;
	int warncnt=0;
	float ft = 0;
	
	while(cnt++<3&&!mpuok)
	{
		osDelay(500);
		mpuok=MPU_init();
	}
	
  /* Infinite loop */
  for(;;)
  {
		
		if(osKernelGetTickCount()>=dstick+500)
		{
			dstick=osKernelGetTickCount();
			ft = ds18b20_read();
		}			
		if(ft<125)
		{
			temp=ft;
			if(osKernelGetTickCount()>=newdstick+scantime)
			{
				newdstick=osKernelGetTickCount();
				g_temp_data[temp_idx]=32-(temp-30)*20/10;
				++temp_idx;
			
				if(temp_idx>=MAX_DATA_LEN)
				{
					memcpy(g_temp_data,g_temp_data+1,MAX_DATA_LEN-1);//????????
					
					temp_idx=MAX_DATA_LEN-1;//??????????????????????????????
				}
				
				
				if(temp>=temp_alarm_max)
				{
					tempwarn=1;
					printf("temp:%.1f\r\n",temp);//????????????
				}
			}
		}
		
		if(mpuok)
		{
			//????????
			if(osKernelGetTickCount()>=mputick+50)
			{
				MPU_getdata();//????MPU6050????????????
			}
			if(osKernelGetTickCount()>=mputick+scantime)
			{			
				mputick=osKernelGetTickCount();
				g_fax_data[idx]=32-fAX*20/90;//??????????90??????????32??????
				g_fay_data[idx]=32-fAY*20/180;//??????????180??
				g_faz_data[idx]=32-fAZ*20/180;
				++idx;
				if(idx>=MAX_DATA_LEN)
				{
					memcpy(g_fax_data,g_fax_data+1,MAX_DATA_LEN-1);//????????
					memcpy(g_fay_data,g_fay_data+1,MAX_DATA_LEN-1);
					memcpy(g_faz_data,g_faz_data+1,MAX_DATA_LEN-1);
					
					idx=MAX_DATA_LEN-1;//??????????????????????????????
				}
								
				if(g_mpustep>0&&(gx*gx+gy*gy+gz*gz>20000*(10-g_mpustep)))//??????????????
				{
					if(++warncnt>=8)
					{
						mpuwarn=1;
						printf("axyz:%6d %6d %6d,gxyz:%6d %6d %6d\r\n",ax,ay,az,gx,gy,gz);//????????
					}
				}
				else
				warncnt=0;
			}
		}		
			
		if(g_bUping && esp8266.bconn)
		{
			if(onenet==0)
			{
				if(osKernelGetTickCount()>=uptick+g_upstep)
				{
					uptick=osKernelGetTickCount();
					
					char buf[100];
					sprintf(buf,"T:%4.1f, A:%6d,%6d,%6d, G:%6d,%6d,%6d, F:%5.1f,%5.1f,%5.1f, W:%d\n",
					temp,ax,ay,az,gx,gy,gz,fAX,fAY,fAZ,(tempwarn?1:0)+(mpuwarn?2:0));
					USendStr(&huart6,(uint8_t*)buf,strlen(buf));
				}
			}
			else
			{
				if(osKernelGetTickCount()>=uptick+g_upstep)
				{
					uptick=osKernelGetTickCount();
					
					char buf1[120];
					//#24#000000#000000#000000#000000#000000#000000#10000#10000#10000#0#
					sprintf(buf1,"#%2.0f#%6d#%6d#%6d#%6d#%6d#%6d#%5.0f#%5.0f#%5.0f#%d#",
					temp,ax,ay,az,gx,gy,gz,fAX,fAY,fAZ,(tempwarn?1:0)+(mpuwarn?2:0));
//					printf("%s",buf1);
					USendStr(&huart6,(uint8_t*)buf1,strlen(buf1));
				}
			}
		}
    osDelay(1);
  }
  /* USER CODE END StartDataTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void WSLogo(void)
{
	static uint32_t tick = 0;
	static uint8_t  led_sta = 0x00;
	
	if(0 == intick)
	 {
		intick = osKernelGetTickCount();
	 }
	else
	 {
		 if(osKernelGetTickCount()>=intick +8000)
		 {
			 intick =0;
//			 led_sta=0;//????????????LED????
			 g_ws = WS_GUI1;//??????????
			 Beep(100,3);//????????????????????
		 }
	 }
	 //LED????
	SetLeds(led_sta);
	if(osKernelGetTickCount() >= tick + 500)
	{
		led_sta = ~led_sta;
		tick = osKernelGetTickCount();
	}
}

void DrawLogo(void)
{
	static uint32_t tick = 0;
	
	if(0 == intick)
	 {
		intick = osKernelGetTickCount();
	 }
	else
	 {
		 if(osKernelGetTickCount()<=intick +2000)
		 {
				GUI_Clear();
			 	GUI_SetFont(&GUI_FontHZ_KaiTi_20);
				GUI_DispStringHCenterAt("????????????\n????????????", 64 , 12);
				GUI_Update();
		 }
		 else if(osKernelGetTickCount()<=intick +5000)
		 {
				GUI_Clear();
			 	GUI_SetFont(&GUI_FontHZ_KaiTi_16);
				GUI_DispStringAt("????1????????\n       18041820\n????2????????\n       18041811", 0 , 0);
				GUI_Update();
		 }
		 else if(osKernelGetTickCount()<=intick +8000)//??????????????
		 {
			 	GUI_Clear();
				GUI_DrawBitmap(&bmFunJC,0,0);
				GUI_DrawBitmap(&bmSunHR,64,0);				
				GUI_Update();
		 }
		 else
			 intick=0;
	 }
}

void DrawGUI1(void)
{
	GUI_Clear();
	GUI_SetFont(&GUI_FontHZ_SimSun_12);
	
	GUI_SetColor(GUI_COLOR_BLACK);//????????
	GUI_DispStringAt("????????",0,0);
	GUI_SetColor(GUI_COLOR_WHITE);//????????
	GUI_DispStringAt("????????",0,14);
	GUI_DispStringAt("????????", 0 , 26);
	GUI_DispStringAt("????????", 0 , 39);
	GUI_DispStringAt("K1?? K2?? K3?? K4??", 0 , 52);
	//????
	GUI_DrawHLine(52,0,128);
	GUI_DrawVLine(48,0,52);
	
	
	char buf[20];
	
	//????????????
	if(0==pageidx)
	{
		GUI_DispStringAt("??????????",50,0);
		GUI_DispStringAt("??????????",50,26);
		sprintf(buf,"%.1f??",temp);//????????
		GUI_DispStringAt(buf,90,13);
		GUI_DispStringAt(mpuwarn ? "??":"??",90,39);//????????????
	}
	else if(1==pageidx)
	{
		sprintf(buf,"ax:%6d",ax);
		GUI_DispStringAt(buf,50,0);
		if(ax>0)
			GUI_FillRect(90,13,90+ax*55/32768,16);
		else if(ax<0)
			GUI_DrawRect(90,13,90-ax*55/32768,16);
		
		sprintf(buf,"ay:%6d",ay);
		GUI_DispStringAt(buf,50,17);
		if(ay>0)
			GUI_FillRect(90,30,90+ay*55/32768,33);
		else if(ay<0)
			GUI_DrawRect(90,30,90-ay*55/32768,33);
		
		sprintf(buf,"az:%6d",az);
		GUI_DispStringAt(buf,50,34);
		if(az>0)
			GUI_FillRect(90,47,90+az*55/32768,50);
		else if(az<0)
			GUI_DrawRect(90,47,90-az*55/32768,50);
	}
	else if(2==pageidx)
	{
		sprintf(buf,"gx:%6d",gx);
		GUI_DispStringAt(buf,50,0);
		if(gx>0)
			GUI_FillRect(90,13,90+gx*55/32768,16);
		else if(gx<0)
			GUI_DrawRect(90,13,90-gx*55/32768,16);
		
		sprintf(buf,"gy:%6d",gy);
		GUI_DispStringAt(buf,50,17);
		if(gy>0)
			GUI_FillRect(90,30,90+gy*55/32768,33);
		else if(gy<0)
			GUI_DrawRect(90,30,90-gy*55/32768,33);
		
		sprintf(buf,"gz:%6d",gz);
		GUI_DispStringAt(buf,50,34);
		if(gz>0)
			GUI_FillRect(90,47,90+gz*55/32768,50);
		else if(gz<0)
			GUI_DrawRect(90,47,90-gz*55/32768,50);
	}
	
	GUI_Update();
}

void DrawGUI2(void)
{
	float temp_min=20;
	float temp_max=40;//??????????????????????????????????????
	//????????????????
	int tt=(((int)(temp)+2)/5)*5;
	temp_min=tt-10;
	temp_max=tt+10;
	
	float temp_alarm_max_height=32-(temp_alarm_max-30)*20/10;//??????????????
	char str[30];//??????????????
	int ox=48;//????
	int oy=63;
		
	GUI_Clear();
	GUI_SetFont(&GUI_FontHZ_SimSun_12);
	
	GUI_DispStringAt("????????",0,0);
	GUI_SetColor(GUI_COLOR_BLACK);//????????
	GUI_DispStringAt("????????",0,13);
	GUI_SetColor(GUI_COLOR_WHITE);//????????
	GUI_DispStringAt("????????", 0 , 26);
	GUI_DispStringAt("????????", 0 , 39);
	GUI_DispStringAt("K1?? K2?? K3?? K4??", 0 , 52);
	//????
	GUI_DrawHLine(52,0,128);
	GUI_DrawVLine(48,0,52);
	
	
	
	uint8_t i;
	uint8_t j;
	switch(g_line_idx)
	{
		default:
			GUI_DrawHLine(32,51,128);//????X??
			sprintf(str,"????:%.1f??",temp);
			if(temp_alarm_max>=temp_min&&temp_alarm_max<=temp_max)
			{
				for(j=48;j<128;j+=2)
				{
					GUI_DrawPixel(j,temp_alarm_max_height);
				}
			}
			for(i=0;i<MAX_DATA_LEN-1;++i)
			{
				GUI_DrawLine(51+i,g_temp_data[i],51+i+1,g_temp_data[i+1]);
			}
			
			break;
		case LINE_FAX:
			GUI_DrawHLine(32,51,128);//????X??
			sprintf(str,"??????:%.1f??",fAX);
			for(i=0;i<MAX_DATA_LEN-1;++i)
			{
				GUI_DrawLine(51+i,g_fax_data[i],51+i+1,g_fax_data[i+1]);
			}
			break;
		case LINE_FAY:
			GUI_DrawHLine(32,51,128);//????X??
			sprintf(str,"??????:%.1f??",fAY);
			for(i=0;i<MAX_DATA_LEN-1;++i)
			{
				GUI_DrawLine(51+i,g_fay_data[i],51+i+1,g_fay_data[i+1]);
			}
			break;
		case LINE_FAZ:
			GUI_DrawHLine(32,51,128);//????X??
			sprintf(str,"??????:%.1f??",fAZ);
			for(i=0;i<MAX_DATA_LEN-1;++i)
			{
				GUI_DrawLine(51+i,g_faz_data[i],51+i+1,g_faz_data[i+1]);
			}
			break;
		case LINE_3D:
			ox=(128)/2;
			oy=(32)/2;
			RateCube(fAX,fAY,fAZ,GUI_COLOR_WHITE,ox,oy);
			break;
	}
	GUI_DispStringAt(str,51,0);
	
	GUI_Update();
}
void DrawGUI3(void)
{
	char buf[30];
	GUI_Clear();
	GUI_SetFont(&GUI_FontHZ_SimSun_12);
	

	GUI_DispStringAt("????????",0,0);
	GUI_DispStringAt("????????",0,13);	
	GUI_SetColor(GUI_COLOR_BLACK);//????????
	GUI_DispStringAt("????????", 0 , 26);
	GUI_SetColor(GUI_COLOR_WHITE);//????????
	GUI_DispStringAt("????????", 0 , 39);
	GUI_DispStringAt("K1?? K2?? K3?? K4??", 0 , 52);
	
	GUI_DispStringAt((char*)(esp8266.ssid),50,0);
	GUI_DispStringAt(TCP_SERVER,50,12);
	sprintf(buf,"????:%d",TCP_PORT);
	GUI_DispStringAt(buf,50,24);
	GUI_DispStringAt(esp8266.bconn ? "OK":"ERR",50,36);
	GUI_DispStringAt(g_bUping ? "??????":"??????",85,36);

	//????
	GUI_DrawHLine(52,0,128);
	GUI_DrawVLine(48,0,52);
	GUI_Update();
}
void DrawGUI4(void)
{
	char buf[20];
	
	GUI_Clear();
	GUI_SetFont(&GUI_FontHZ_SimSun_12);
	
	GUI_DispStringAt("????????",0,0);
	GUI_DispStringAt("????????",0,13);
	GUI_DispStringAt("????????",0,26);
	GUI_SetColor(GUI_COLOR_BLACK);//????????
	GUI_DispStringAt("????????",0,39);
	GUI_SetColor(GUI_COLOR_WHITE);//????????
	GUI_DispStringAt("K1?? K2?? K3?? K4??", 0 , 52);
	//????
	GUI_DrawHLine(52,0,128);
	GUI_DrawVLine(48,0,52);

	GUI_DispStringAt("????????:",50,0);
	GUI_DispStringAt("??????????:",50,13);
	GUI_DispStringAt("????????:",50,26);
	GUI_DispStringAt("????????:",50,39);
	//????????
	sprintf(buf,"%.0f??",temp_alarm_max);
	if(0==g_paridx)
		GUI_SetColor(GUI_COLOR_BLACK);//????????
	GUI_DispStringAt(buf,104,0);
	GUI_SetColor(GUI_COLOR_WHITE);//????????
	//??????????
	sprintf(buf,"%d",g_mpustep);
	if(1==g_paridx)
		GUI_SetColor(GUI_COLOR_BLACK);//????????
	GUI_DispStringAt(buf,116,13);
	GUI_SetColor(GUI_COLOR_WHITE);//????????
	//????????
	sprintf(buf,"%dS",g_warntime);
	if(2==g_paridx)
		GUI_SetColor(GUI_COLOR_BLACK);//????????
	GUI_DispStringAt(buf,104,26);
	GUI_SetColor(GUI_COLOR_WHITE);//????????
	//????????
	sprintf(buf,"%.1fS",g_upstep/1000.0f);
	if(3==g_paridx)
		GUI_SetColor(GUI_COLOR_BLACK);//????????
	GUI_DispStringAt(buf,104,39);
	GUI_SetColor(GUI_COLOR_WHITE);//????????
	
	GUI_Update();
}
void Beep(int time,int tune)		//??????????????
{
	static uint16_t TAB[7]={493,523,588,660,698,784,880};
	HAL_TIM_Base_Start(&htim3);
	
	if(tune>=1&&tune<=7)
	{
		int pre=1000000/TAB[tune];
		__HAL_TIM_SET_AUTORELOAD(&htim3,pre);
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,pre/2);
		
		beeptick=osKernelGetTickCount()+time;
		HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	}
}

void BeepDone(void)
{
	if(beeptick>0&& osKernelGetTickCount()>=beeptick)
	{
		beeptick=0;
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1);
	}
}

void DispSeg(uint8_t num[4],uint8_t dot)
{
	for(int i=0;i<4;i++)
	{
		Write595(i,num[i],(dot==(i+1)?1:0));
		osDelay(1);
	}
}
//ESP8266??????
int InitESP8266(void)
{
	char *id="*431023#shr#mylua*";
	
	if(onenet==0)
	{
		ESP_SetCIPMode(0);//????????????
		if(ESP_IsOK())
		{	
			ESP_SetMode(3);//station+AP????
			ESP_GetSSID();
			
			if(ESP_JoinAP(AP_NAME,AP_PSW))
			{
				ESP_GetIPAddr();
				ESP_SetTCPServer(0,0);
				ESP_SetCIPMux(0);
				printf("Station ip:%s\n",esp8266.st_addr);//????????IP????????????
				if(ESP_ClientToServer(TCP_SERVER,TCP_PORT))
				{
					ESP_SetCIPMode(1);//????????????
					printf("ESP8266 init ok!\n");
					return 0;
				}
				else return 1;
			}
		}
		}
		else if(onenet==1)
		{
					
					ESP_SetCIPMode(0);//????????????
					if(ESP_IsOK())
					{	
						ESP_SetMode(3);//station+AP????
						ESP_GetSSID();
						
						if(ESP_JoinAP(AP_NAME,AP_PSW))
						{
							ESP_GetIPAddr();
							ESP_SetTCPServer(0,0);
							ESP_SetCIPMux(0);
							printf("Station ip:%s\n",esp8266.st_addr);//????????IP????????????
							
							if(ESP_ClientToServer(onenet_TCP_SERVER,onenet_TCP_PORT))
							{
								ESP_SetCIPMode(1);//????????????
								printf("ESP8266 init ok!\n");
								//sprintf(id,"*431023#shr#mylua*");
								USendStr(&huart6,(uint8_t *)id,strlen(id));	//??????????
								printf("%s",id);
								return 0;
							}
							else return 1;
						}
					}
		}
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
