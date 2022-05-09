/*===========================================================================*/
/* Project:  WeAct Black Pill V1.2 board Sample Software                     */
/* Module :  BLD_Manager.c                                                   */
/* Version:  V1.00                                                           */
/*===========================================================================*/
/* History:                                                                  */
/*              V1.00: Initial version                                       */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
/* Source code for the Boot loader Manger 		                             */
/* Boot loader Should be flashed in the first sector                         */
/* make sure to edit mem.ld 							  					 */
/* -->FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 16K		                 */
/*===========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "RCC.h"
#include "GPIO.h"
#include "NVIC.h"
#include "Usart.h"

#include "BLD_Manger.h"
#include "Flash.h"
#include "SCB.h"

typedef enum
{
	SessionControl    		= 0x10,
	RequestDownload   		= 0x34,
	TransfareData         	= 0x36,
	RequestTransfareExit	= 0x37
}FlashingSec_t;






static uint8_t BuffRecived = 0;
static uint8_t AppArr_buff[16385];
static USARTHandel_t Loc_uart;
App_t St_App;
static void BLDManger_SendPositiveRes(void);
static void BLDManger_ConcWord(uint8_t* pu8_bytes,uint32_t* pu8_Dest);
static void BLDManger_FlashApp(void);
static void BLDManger_SendNegativeRes(void);
static void BLDManger_RaisMark(void);
static uint8_t Glop_Response=0;


/******************************************************************************
** Function:    BLDManger_UartInit
** Description: this function Init Uart1 with to TX and RX mode
** Parameter: 	void
** Return:      void
******************************************************************************/

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
}

/******************************************************************************
** Function:    BLDManger_FlashingTask
** Description: this function manage the Flashing Sequence
** Parameter: 	void
** Return:      void
******************************************************************************/
void BLDManger_FlashingTask(void)
{
	static FlashingSec_t FlashingSec = SessionControl;
	static uint8_t State = 0;

	switch(FlashingSec)
	{
	/* First step in the Flashing sequence Its a request form the bus to enter a Flashing Sequence by sending [0x10]*/

	case SessionControl:

		if(State == 0 && (APP_INFO->App_UpdateReq) == 0xFFFFFFFF)
		{
			/*Enable Rx interrupt To receive one byte*/
			Uart_RXBuffer(&Loc_uart , AppArr_buff , 1);
			State = 1;
		}
		/*Check if there a update Req */
		else if(State == 0 && (APP_INFO->App_UpdateReq) == 0x55555555)
		{
			State = 1;
			BuffRecived = 1;
			AppArr_buff[0] = SessionControl;
			Flash_SectorErase(1);
		}
		else if(State == 1 && BuffRecived == 1)
		{
			BuffRecived = 0;
			State = 0;
			if(AppArr_buff[0] == SessionControl)
			{
				Glop_Response = AppArr_buff[0];
				/*Send positive Response to the bus*/
				BLDManger_SendPositiveRes();
				FlashingSec = RequestDownload;
			}
			else
			{
				/*Send Negative Response to the bus*/
				BLDManger_SendNegativeRes();
				FlashingSec = SessionControl;
				BuffRecived = 0;
				State = 0;
			}
		}
		break;
	/*	Second step in the Flashing sequence Its a request form the bus to Download Data by sending  [0x34]
	 *  Send some info  about this Data:
	 * 								1-Application EntryPoint
	 * 								2-Application Size
	 * 								3-Application FirstAdd
	 * */
	case RequestDownload:
		if(State == 0)
		{
			Uart_RXBuffer(&Loc_uart , AppArr_buff , 1);
			State = 1;
		}
		else if(State == 1 && BuffRecived == 1)
		{
			BuffRecived = 0;
			if(AppArr_buff[0] == RequestDownload)
			{
				Glop_Response = AppArr_buff[0];
				State = 2;
				Uart_RXBuffer(&Loc_uart , AppArr_buff , 12);
			}
			else
			{
				State = 0;
				BLDManger_SendNegativeRes();
				FlashingSec = SessionControl;
			}
		}
		else if(State == 2 && BuffRecived == 1)
		{
			State = 0;
			BuffRecived = 0;
			BLDManger_ConcWord(&(AppArr_buff[0]),&St_App.AppEntryPoint);
			BLDManger_ConcWord(&(AppArr_buff[4]),&St_App.AppSize);
			BLDManger_ConcWord(&(AppArr_buff[8]),&St_App.AppFirstAdd);
			BLDManger_SendPositiveRes();
			FlashingSec = TransfareData;
		}
		break;
		/*	Third step in the Flashing sequence Its a request form the bus to Send the actual DATA  [0x36] */
	case TransfareData:
		if(State == 0)
		{
			Uart_RXBuffer(&Loc_uart , AppArr_buff , 1);
			State = 1;
		}
		else if(State == 1 && BuffRecived == 1)
		{
			BuffRecived = 0;
			if(AppArr_buff[0] == TransfareData)
			{
				Glop_Response = AppArr_buff[0];
				State = 2;
				/*Enable the Rx Interrupt to receive Buffer with size of the Application */
				Uart_RXBuffer(&Loc_uart , AppArr_buff , St_App.AppSize);
			}
			else
			{
				BLDManger_SendNegativeRes();
				FlashingSec = SessionControl;
				State = 0;
			}
		}
		else if(State == 2 && BuffRecived == 1)
		{
			BLDManger_SendPositiveRes();
			/*Flash the app in sector(2)*/
			BLDManger_FlashApp();
			/*Flash app info in sector (1)*/
			BLDManger_RaisMark();
			FlashingSec = RequestTransfareExit;
			State = 0;
			BuffRecived = 0;
		}
		break;
	case RequestTransfareExit:
		if(State == 0)
		{
			Uart_RXBuffer(&Loc_uart , AppArr_buff , 1);
			State = 1;
		}
		else if(State == 1 && BuffRecived == 1)
		{
			BuffRecived = 0;
			State = 0;
			if(AppArr_buff[0] == RequestTransfareExit)
			{
				uint32_t CountDown = 9000;
				Glop_Response = AppArr_buff[0];
				FlashingSec = RequestTransfareExit+1;
				BLDManger_SendPositiveRes();
				/*Busy wait Before reset*/
				while(CountDown != 0)
				{
					--CountDown;
				}
				SCB_RestSys();
			}
			else
			{
				BLDManger_SendNegativeRes();
				FlashingSec = SessionControl;
				BuffRecived = 0;
				State = 0;
			}
		}
		break;
	}
}
void RXBuffCblt(void)
{
	BuffRecived = 1;
}

static void BLDManger_FlashApp(void)
{
	uint32_t data;
	uint32_t index;
	Flash_SectorErase(2);
	uint32_t Loc_AppFirstAdd = St_App.AppFirstAdd;
	for(index = 0 ; index < St_App.AppSize ; index+=4)
	{
		data =  (uint64_t)((uint32_t)AppArr_buff[index] | (uint32_t)AppArr_buff[index+1]<<8 | (uint32_t)AppArr_buff[index+2] <<16 | (uint32_t)AppArr_buff[index+3]<<24);
		Flash_Program(FLASH_PROGRAM_SIZE_x32 , Loc_AppFirstAdd , data);
		Loc_AppFirstAdd+=4;
	}

}
static void BLDManger_ConcWord(uint8_t* pu8_bytes,uint32_t* pu8_Dest)
{
	*pu8_Dest = ((uint32_t)pu8_bytes[3] | (uint32_t)pu8_bytes[2]<<8 | (uint32_t)pu8_bytes[1] <<16 | (uint32_t)pu8_bytes[0]<<24);
}
static void BLDManger_SendPositiveRes(void)
{
	Uart_SendByte(&Loc_uart ,(uint8_t)((uint8_t)Glop_Response + (uint8_t)(0x10)));

}
static void BLDManger_SendNegativeRes(void)
{
	Uart_SendByte(&Loc_uart , (uint8_t)(0x7F));
}

static void BLDManger_RaisMark(void)
{
	Flash_SectorErase(1);
	Flash_Program(FLASH_PROGRAM_SIZE_x32 , MARK_ADD , St_App.AppFirstAdd);
	Flash_Program(FLASH_PROGRAM_SIZE_x32 , MARK_ADD + 4 , St_App.AppEntryPoint);
	Flash_Program(FLASH_PROGRAM_SIZE_x32 , MARK_ADD + 8 , St_App.AppSize);
}


