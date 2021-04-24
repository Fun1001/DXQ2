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
#include "tim.h"
#include "DS_18B20.h"
#include "MPU6050.h"
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
#define WS_LOGO 0
#define WS_GUI1 1
#define WS_GUI2 2
#define WS_GUI3 3
#define WS_GUI4 4

int g_ws = WS_LOGO;
uint32_t intick = 0;

volatile float temp=0;

uint32_t beeptick=0;

uint8_t mpuwarn =0;//报警信号
uint8_t tempwarn=0;

uint8_t pageidx=0;//翻页

uint32_t warntick=0;//报警时间戳
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
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for UartTask */
osThreadId_t UartTaskHandle;
const osThreadAttr_t UartTask_attributes = {
  .name = "UartTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for GUITask */
osThreadId_t GUITaskHandle;
const osThreadAttr_t GUITask_attributes = {
  .name = "GUITask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for DataTask */
osThreadId_t DataTaskHandle;
const osThreadAttr_t DataTask_attributes = {
  .name = "DataTask",
  .stack_size = 128 * 4,
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
				SetLeds(0);//非LOGO状态LED灯灭
				break;
		}
		
		//报警倒计时
		if(tempwarn||mpuwarn)
		{
			if(0==warntick)
				warntick=osKernelGetTickCount();
			else if(osKernelGetTickCount()>=warntick+30000)//报警时长30s
			{	
				tempwarn=mpuwarn=0;
				warntick=0;
			}
			else
			{
				uint32_t tic=warntick+30000-osKernelGetTickCount();
				num[0]=(tic/10000)%10;
				num[1]=(tic/1000)%10;
				num[2]=(tic/100)%10;
				num[3]=(tic/10)%10;
				
				//蜂鸣器报警
				if(tempwarn==1)
				{
					if(num[2]==1||num[2]==4||num[2]==7)//蜂鸣器叫三下
					Beep(100,num[2]);
				} 
				if(mpuwarn==1)
				{
					if(num[2]==2||num[2]==5||num[2]==1)//蜂鸣器叫三下
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
		if(key>0)
			printf("%02X\n",key);//打印出按键
		
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
				//页面切换
				else if(KEY2==key)
				{
					if(pageidx>0)
						--pageidx;
				}
				else if(KEY3==key)
				{
					if(pageidx<2)
						++pageidx;
				}
				//返回Logo
				else if(KEY6==key)
					g_ws=WS_LOGO;
				break;
			case WS_GUI2:
				if(KEY1==key)
					g_ws=WS_GUI1;
				else if(KEY4==key)
					g_ws=WS_GUI3;
				else if(KEY6==key)
					g_ws=WS_LOGO;
				break; 
			case WS_GUI3:
				if(KEY1==key)
					g_ws=WS_GUI2;
				else if(KEY4==key)
					g_ws=WS_GUI4;
				else if(KEY6==key)
					g_ws=WS_LOGO;
				break;
			case WS_GUI4:
				if(KEY1==key)
					g_ws=WS_GUI3;
				else if(KEY4==key)
					g_ws=WS_GUI1;
				else if(KEY6==key)
					g_ws=WS_LOGO;
				break;
			default:
				if(KEY6==key)
					g_ws=WS_LOGO;
				break;
		}
		
    osDelay(1);
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
  /* Infinite loop */
  for(;;)
  {
		
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
	GUI_Init();//初始化

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
	
	uint8_t mpuok=MPU_init();
	uint8_t cnt=0;
	while(cnt++<3&&!mpuok)
	{
		osDelay(500);
		mpuok=MPU_init();

	}
	uint32_t dstick=0;
	uint32_t mputick=0;
	int warncnt=0;
  /* Infinite loop */
  for(;;)
  {
		
		if(osKernelGetTickCount()>=dstick+1000)
		{
			dstick=osKernelGetTickCount();
			float ft = ds18b20_read();
			if(ft<125)
			{
				temp=ft;
				printf("temp:%.1f\n",temp);//打印温度数据
				if(temp>=29)
				{
					tempwarn=1;
//					warntick=osKernelGetTickCount();
				}
			}
		}
		
		if(mpuok)
		{
				if(osKernelGetTickCount()>=mputick+50)
			{
				mputick=osKernelGetTickCount();
				MPU_getdata();
				printf("axyz:%6d %6d %6d,gxyz:%6d %6d %6d\n",ax,ay,az,gx,gy,gz);//打印数据
				
				if(gx*gx+gy*gy+gz*gz>5000)
				{
					if(++warncnt>=3)
					{
						mpuwarn=1;
//						warntick=osKernelGetTickCount();
					}
				}
				else
				mpuwarn=0;
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
//			 led_sta=0;//进入主菜单后LED熄灭
			 g_ws = WS_GUI1;//进入主菜单
			 Beep(100,3);//蜂鸣器提示进入主菜单
		 }
	 }
	 //LED灯闪
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
				GUI_DispStringHCenterAt("防火、防盗远\n程检测器设计", 64 , 12);
				GUI_Update();
		 }
		 else if(osKernelGetTickCount()<=intick +5000)
		 {
				GUI_Clear();
			 	GUI_SetFont(&GUI_FontHZ_KaiTi_16);
				GUI_DispStringAt("成员1：孙昊然\n       18041820\n成员2：方九川\n       18041811", 0 , 0);
				GUI_Update();
		 }
		 else if(osKernelGetTickCount()<=intick +8000)//显示大头照三秒
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
	
	GUI_SetColor(GUI_COLOR_BLACK);//反色显示
	GUI_DispStringAt("实时监测",0,0);
	GUI_SetColor(GUI_COLOR_WHITE);//恢复反色
	GUI_DispStringAt("数据曲线",0,14);
	GUI_DispStringAt("无线通信", 0 , 26);
	GUI_DispStringAt("参数设置", 0 , 39);
	GUI_DispStringAt("K1↑ K2← K3→ K4↓", 0 , 52);
	//画线
	GUI_DrawHLine(52,0,128);
	GUI_DrawVLine(48,0,52);
	
	
	char buf[20];
	
	//检测数据显示
	if(0==pageidx)
	{
		GUI_DispStringAt("当前温度：",50,0);
		GUI_DispStringAt("震动报警：",50,26);
		sprintf(buf,"%.1f℃",temp);//温度显示
		GUI_DispStringAt(buf,90,13);
		GUI_DispStringAt(mpuwarn ? "是":"否",90,39);//是否震动报警
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
	GUI_Clear();
	GUI_SetFont(&GUI_FontHZ_SimSun_12);
	
	GUI_DispStringAt("实时监测",0,0);
	GUI_SetColor(GUI_COLOR_BLACK);//反色显示
	GUI_DispStringAt("数据曲线",0,14);
	GUI_SetColor(GUI_COLOR_WHITE);//恢复反色
	GUI_DispStringAt("无线通信", 0 , 26);
	GUI_DispStringAt("参数设置", 0 , 39);
	GUI_DispStringAt("K1↑ K2← K3→ K4↓", 0 , 52);
	//画线
	GUI_DrawHLine(52,0,128);
	GUI_DrawVLine(48,0,52);
	
	GUI_Update();
}
void DrawGUI3(void)
{
	GUI_Clear();
	GUI_SetFont(&GUI_FontHZ_SimSun_12);
	

	GUI_DispStringAt("实时监测",0,0);
	GUI_DispStringAt("数据曲线",0,14);	
	GUI_SetColor(GUI_COLOR_BLACK);//反色显示
	GUI_DispStringAt("无线通信", 0 , 26);
	GUI_SetColor(GUI_COLOR_WHITE);//恢复反色
	GUI_DispStringAt("参数设置", 0 , 39);
	GUI_DispStringAt("K1↑ K2← K3→ K4↓", 0 , 52);
	//画线
	GUI_DrawHLine(52,0,128);
	GUI_DrawVLine(48,0,52);

	
	GUI_Update();
}
void DrawGUI4(void)
{
	GUI_Clear();
	GUI_SetFont(&GUI_FontHZ_SimSun_12);
	
	GUI_DispStringAt("实时监测",0,0);
	GUI_DispStringAt("数据曲线",0,14);
	GUI_DispStringAt("无线通信",0,26);
	GUI_SetColor(GUI_COLOR_BLACK);//反色显示
	GUI_DispStringAt("参数设置",0,39);
	GUI_SetColor(GUI_COLOR_WHITE);//恢复反色
	GUI_DispStringAt("K1↑ K2← K3→ K4↓", 0 , 52);
	//画线
	GUI_DrawHLine(52,0,128);
	GUI_DrawVLine(48,0,52);

	
	GUI_Update();
}
void Beep(int time,int tune)
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
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
