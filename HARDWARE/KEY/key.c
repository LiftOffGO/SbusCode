#include "key.h"
#include "delay.h"
u8 lock_state = 0;
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTCʱ��

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;//PA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0
	
} 

u8 KEY_Scan(void)
{	 
	if(0==KEY0&&0==KEY1&&0==KEY2)
	{    
		return 3;
	}else if(1==KEY0&&1==KEY1&&1==KEY2)
	{
		return 0;
	}else	
		return 1;
}
