/*******************************************************************************
* 文档: comm.h
* 作者: 曾毓
*
* 描述: STM32F4串口通信DMA接收空闲中断底层驱动源文件
*		
* 时间：2021/5/13
*
*	转载使用时请注明出处
*******************************************************************************/
#include "comm.h"

uint8_t rx1_dma_buff[MAX_RECV_LEN] = {0};
uint8_t recv1_buff[MAX_RECV_LEN] = {0};
uint32_t recv1_len = 0; 									// 接收数据长度

extern DMA_HandleTypeDef hdma_usart1_rx;

int fputc(int ch, FILE *f) //支持printf打印到串口助手
{ 
	// 向串口 1 发送一个字符 
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 100); 
	return 0;
}

void USendStr(UART_HandleTypeDef *UartHandle, uint8_t *str, uint32_t len)//指定向某一串口发送数据，可发送指定长度数组
{
	HAL_UART_Transmit(UartHandle, str, len, 0xFFFF); 
}

void USendCMD(UART_HandleTypeDef *UartHandle, char *cmd)//发送AT指令
{
	printf("--> %s", cmd);
	osDelay(10);
	HAL_UART_Transmit(UartHandle, (uint8_t *)cmd, strlen(cmd), 0xFFFF); 
}

void Uart1IdleCallback(UART_HandleTypeDef *huart)//串口接收空闲中断回调函数
{
	if( __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) != RESET)
  {
		__HAL_UART_CLEAR_IDLEFLAG(huart);		// 清除中断标志
		if (huart->Instance == USART1)	// 如果是串口1的空闲中断
		{
			HAL_UART_DMAStop(huart);						// 暂停DMA接收数据
			recv1_len = MAX_RECV_LEN - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);	// 计算当前接收数据长度
			if (recv1_len < MAX_RECV_LEN - 1 && recv1_len > 0)
			{
				memcpy(recv1_buff, rx1_dma_buff, recv1_len);	// 复制dma缓冲数据到串口数据缓冲
				recv1_buff[recv1_len] = '\0';							// 字符串末尾结束符
			}
			else
				recv1_len = 0;		// 无效数据
			__HAL_UNLOCK(huart);											// 解锁串口
			HAL_UART_Receive_DMA(huart, rx1_dma_buff, MAX_RECV_LEN);	//打开DMA接收，数据存入dma_buff数组中。
		}
  }
}

void StartRecvUart1(void)//串口1初始化
{
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);        				//使能idle中断
  HAL_UART_Receive_DMA(&huart1, rx1_dma_buff, MAX_RECV_LEN);	//打开DMA接收，数据存入recv_buff数组中。
}
