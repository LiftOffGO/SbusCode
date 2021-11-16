//*************LiftOffGO************//
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "crsf.h"

uint16_t CH[18];  
uint8_t  rc_flag = 0;
uint8_t  sendBuf[12];


void Sbus_Data_Count(u8 *buf);
void Sbus_Send_Buf(u8 *buf);

 int main(void)
 {	

	sendBuf[0]=0xfe;//帧头
	sendBuf[10]=0xef;//帧尾
	sendBuf[11]='\n';//帧尾
	 
	delay_init();	    	 
	LED_Init();		  	 
	//KEY_Init();          
	delay_ms(10);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_ms(10);
	uart_init(9600);	 //串口初始化为9600
	delay_ms(10);
	SBUS_Configuration();
	 
	while(1)
	{	
		
		Sbus_Data_Count(USART2_RX_BUF);
		printf("\r\n CH0= %d  CH1= %d  CH2= %d  CH3= %d  \r\n", CH[0],CH[1],CH[2],CH[3]);	
		
//		Sbus_Send_Buf(USART2_RX_BUF);
		
		delay_ms(100);
		LED0=!LED0;
	}	 
	
}


void Sbus_Data_Count(u8 *buf)
{
	CH[ 0] = ((int16_t)buf[ 2] >> 0 | ((int16_t)buf[ 3] << 8 )) & 0x07FF;
	CH[ 1] = ((int16_t)buf[ 3] >> 3 | ((int16_t)buf[ 4] << 5 )) & 0x07FF;
	CH[ 2] = ((int16_t)buf[ 4] >> 6 | ((int16_t)buf[ 5] << 2 )  | (int16_t)buf[ 6] << 10 ) & 0x07FF;
	CH[ 3] = ((int16_t)buf[ 6] >> 1 | ((int16_t)buf[ 7] << 7 )) & 0x07FF;
	CH[ 4] = ((int16_t)buf[ 7] >> 4 | ((int16_t)buf[ 8] << 4 )) & 0x07FF;
	CH[ 5] = ((int16_t)buf[ 8] >> 7 | ((int16_t)buf[ 9] << 1 )  | (int16_t)buf[10] <<  9 ) & 0x07FF;
	CH[ 6] = ((int16_t)buf[10] >> 2 | ((int16_t)buf[11] << 6 )) & 0x07FF;
	CH[ 7] = ((int16_t)buf[11] >> 5 | ((int16_t)buf[12] << 3 )) & 0x07FF;
	CH[ 8] = ((int16_t)buf[13] << 0 | ((int16_t)buf[14] << 8 )) & 0x07FF;
	CH[ 9] = ((int16_t)buf[14] >> 3 | ((int16_t)buf[15] << 5 )) & 0x07FF;
	CH[10] = ((int16_t)buf[15] >> 6 | ((int16_t)buf[16] << 2 )  | (int16_t)buf[17] << 10 ) & 0x07FF;
	CH[11] = ((int16_t)buf[17] >> 1 | ((int16_t)buf[18] << 7 )) & 0x07FF;
	CH[12] = ((int16_t)buf[18] >> 4 | ((int16_t)buf[19] << 4 )) & 0x07FF;
	CH[13] = ((int16_t)buf[19] >> 7 | ((int16_t)buf[20] << 1 )  | (int16_t)buf[21] <<  9 ) & 0x07FF;
	CH[14] = ((int16_t)buf[21] >> 2 | ((int16_t)buf[22] << 6 )) & 0x07FF;
	CH[15] = ((int16_t)buf[22] >> 5 | ((int16_t)buf[23] << 3 )) & 0x07FF;
}
void Sbus_Send_Buf(u8 *buf)
{
	u8 i;
	sendBuf[1]=buf[2];
	sendBuf[2]=buf[3];
	sendBuf[3]=buf[4];
	sendBuf[4]=buf[5];
	sendBuf[5]=buf[6];
	sendBuf[6]=buf[7];
	sendBuf[7]=buf[8];
	sendBuf[8]=buf[9];
	sendBuf[9]=buf[10];
	
	for(i = 0; i < 12; i ++)
	{
		USART1->DR = sendBuf[i];
		while((USART1->SR&0x40) == 0);
	}
	
}
