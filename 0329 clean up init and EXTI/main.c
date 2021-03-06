//includes
#include "stm32f4xx.h"
#include "RFM95.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//TEST tertsbjkdasjkfjsdkjfklsdag
void init(void);
void flash (void);

int count=0;

int main(void){


	init();

	RFM95_Set_Mode(RFM95_LONG_RANGE_MODE|RFM95_MODE_RXCONTINUOUS);	//Enter RX continuous mode

	while(1){
		//sit back and wait for the packets to arrive
	}


}

void init(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_SetBits(GPIOD, GPIO_Pin_12);

	initSPI2();

	//void RFM95_LoRa_Init2(double Freq, uint8_t PayloadLength, uint8_t CodingRate, uint8_t SpreadingFactor, uint8_t Bandwidth, uint8_t OutputPower);
	RFM95_LoRa_Init2(915, 0x0C, RFM95_CODING_RATE_4_5, RFM95_SPREADING_FACTOR_128CPS, RFM95_BW_500KHZ, 0);

	initUserButtonEXTI0();
	initLoRaFlagEXTI2();
	initUART2();

}

void flash (void){
	switch(count) {
		case 0:
			GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
			GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
			count++;
			break;
		case 1:
			GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
			GPIO_ToggleBits(GPIOD,GPIO_Pin_14);
			count++;
			break;
		case 2:
			GPIO_ToggleBits(GPIOD,GPIO_Pin_14);
			GPIO_ToggleBits(GPIOD,GPIO_Pin_15);
			count++;
			break;
		case 3:
			GPIO_ToggleBits(GPIOD,GPIO_Pin_15);
			GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
			count=0;
			break;
	}
}
