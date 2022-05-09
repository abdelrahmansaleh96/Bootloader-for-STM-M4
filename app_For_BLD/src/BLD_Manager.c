#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "RCC.h"
#include "GPIO.h"
#include "NVIC.h"
#include "Usart.h"
#include "Flash.h"
#include "SCB.h"

#include "BLD_Manger.h"

typedef enum
{
	SessionControl    		= 0x10,
	RequestDowenload   		= 0x34,
	TransfareData         	= 0x36,
	RequestTransfareExit	= 0x37
}FlashingSec_t;



static uint8_t AppArr_buff[5];
static USARTHandel_t Loc_uart;
App_t St_App;

void RXBuffCblt(void)
{
	if(AppArr_buff[0] == 0x10 )
	{
		trace_printf("Update Req \n");
		Flash_SectorErase(1);
		Flash_Program(FLASH_PROGRAM_SIZE_x32 , MARK_ADD + 12  , 0x55555555);
		SCB_RestSys();
	}
	else
	{

	}
}

void BLDManger_UartInit(void)
{
	/*---Enable clock for UART1,GPIOA---*/
	RCC_EnablePriphralCLK(RCC_APB2ENR_USART1EN);
	RCC_EnablePriphralCLK(RCC_AHB1ENR_GPIOAEN);

	/*---Configure pin 9  TX_UART1---*/
	GpioPincfg_t UARTTX;
	UARTTX.mode  = MODE_ALT_FUNC_PUSH_PULL;
	UARTTX.port  = GPIOA;
	UARTTX.pin   = 9;
	UARTTX.speed = SPEED_MEDIUM;
	Gpio_enuinitPinCfg(&UARTTX);

	Gpio_enuSetAF(GPIOA,9,GPIO_AF7);

	/*---Configure pin 10 RX_UART1---*/
	GpioPincfg_t UARTRX;
	UARTRX.mode  = MODE_ALT_FUNC_PUSH_PULL;
	UARTRX.port  = GPIOA;
	UARTRX.pin   = 10;
	UARTRX.speed = SPEED_MEDIUM;
	Gpio_enuinitPinCfg(&UARTRX);

	Gpio_enuSetAF(GPIOA,10,GPIO_AF7);
	/*---Configure Uart1---*/

	Loc_uart.BaudRate           = 9600;
	Loc_uart.Channel_BaseAdress = USART1;
	Loc_uart.Mode               = MODE_TX_RX;
	Loc_uart.Parity 			= PARITY_DISABLE;
	Loc_uart.Stop_bits			= STOP_BITS_ONE;
	Loc_uart.WordLength			= WORD_LENGHT_8B;
	Loc_uart.state				= ready;
	Uart_Init(&Loc_uart);

	/*---Enable Interrupt form NVIC---*/
	NVIC_vidEnableIRQ(IRQ_enuUSART1_IRQHandler);
	/*---Register CpfForRx---*/
	Uart_RegisterCpfRxComplet(&Loc_uart,RXBuffCblt);
	Uart_RXBuffer(&Loc_uart , AppArr_buff , 1);
}


