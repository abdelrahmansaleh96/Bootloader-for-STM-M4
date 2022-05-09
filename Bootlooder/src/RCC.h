/*===========================================================================*/
/* Project:  WeAct Black Pill V1.2 Sample Software                           */
/* Module :  RCC.h                                                           */
/* Version:  V1.00                                                           */
/*===========================================================================*/
/* History:                                                                  */
/*              V1.00: Initial version                                       */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
/*  Header file for the RCC.c source code                                    */
/*                                                                           */
/*===========================================================================*/
#ifndef RCC_H_
#define RCC_H_



/*select  the source CLK for PLL*/
#define RCC_PLL_SRC									    16u

/*masks select System CLK*/
#define RCC_Sysclk_HSI						        	0x00000000u
#define RCC_Sysclk_HSE						        	0x00000001u
#define RCC_Sysclk_PLL						        	0x00000002u


/*GET the added magic number*/
#define RCC_PERIPHERAL_GET_M							0xc0000000u


/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/
/*masks for RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)*/
#define RCC_AHB1ENR_GPIOAEN					0x00000001u
#define RCC_AHB1ENR_GPIOBEN					0x00000002u
#define RCC_AHB1ENR_GPIOCEN					0x00000004u
#define RCC_AHB1ENR_GPIODEN					0x00000008u
#define RCC_AHB1ENR_GPIOEEN					0x00000010u
#define RCC_AHB1ENR_GPIOHEN					0x00000020u
#define RCC_AHB1ENR_CRCEN					0x00001000u
#define RCC_AHB1ENR_DMA1EN					0x00200000u
#define RCC_AHB1ENR_DMA2EN					0x00400000u

#define RCC_AHB1ENR_GET_M                               0x00000000u
/*Masks for RCC AHB2 peripheral clock enable register (RCC_AHB2ENR)*/
#define RCC_AHB2ENR_OTGFSEN								0x40000080u

#define RCC_AHB2ENR_GET_M								0x40000000u

/*Masks for RCC APB1 peripheral clock enable register (RCC_APB1ENR)*/

#define RCC_APB1ENR_TIM2EN 								0x80000001u
#define	RCC_APB1ENR_TIM3EN								0x80000002u
#define RCC_APB1ENR_TIM4EN 								0x80000004u
#define RCC_APB1ENR_TIM5EN								0x80000008u
#define RCC_APB1ENR_WWDGEN								0x80000800u
#define RCC_APB1ENR_SPI2EN								0x80004000u
#define RCC_APB1ENR_SPI3EN								0x80008000u
#define RCC_APB1ENR_USART2EN							0x80020000u
#define RCC_APB1ENR_I2C1EN								0x80200000u
#define RCC_APB1ENR_I2C2EN								0x80400000u
#define RCC_APB1ENR_I2C3EN								0x80800000u
#define	RCC_APB1ENR_PWREN								0xD0000000u


#define	RCC_APB1ENR_GET_M								0x80000000u
/*RCC APB2 peripheral clock enable register (RCC_APB2ENR)*/
#define RCC_APB2ENR_TIM1EN 								0xc0000001u
#define	RCC_APB2ENR_USART1EN							0xc0000010u
#define	RCC_APB2ENR_USART6EN							0xc0000020u
#define	RCC_APB2ENR_ADC1EN								0xc0000100u
#define	RCC_APB2ENR_SDIOEN								0xc0000800u
#define	RCC_APB2ENR_SPI1EN								0xc0001000u
#define	RCC_APB2ENR_SPI4EN								0xc0002000u
#define	RCC_APB2ENR_SYSCFGEN							0xc0004000u
#define	RCC_APB2ENR_TIM9EN								0xc0010000u
#define	RCC_APB2ENR_TIM10EN								0xc0020000u
#define	RCC_APB2ENR_TIM11EN								0xc0040000u


#define	RCC_APB2ENR_GET_M								0xc0000000u

/* ---- function return value ---- */
typedef enum
{
    RCC_enumPLLNerror,
    RCC_enumPLLMerror,
	RCC_enumPLLPerror,
	RCC_enumPLLQerror,
	RCC_enumPLLSRCerror,
	RCC_enumHSIRDYerror,
	RCC_enumHSERDYerror,
	RCC_enumPLLRDYerror,
	RCC_enumSelectSysClkerror,
	RCC_enumWrongPriphralerror,
	RCC_enumis_selectederror,
	RCC_enumSWSerror,
    RCC_enumOK
}RCC_tenumErrorStatus;


/*===========================================================================*/
/* Function defines */
/*===========================================================================*/


RCC_tenumErrorStatus RCC_SelectSysClk(uint8_t Copy_u8SysClk);
RCC_tenumErrorStatus RCC_ControlHSIOn(void);
RCC_tenumErrorStatus RCC_ControlHSEOn(void);
RCC_tenumErrorStatus RCC_ControlPLLOn(void);
RCC_tenumErrorStatus RCC_ControlHSIOff(void);
RCC_tenumErrorStatus RCC_ControlHSEOff(void);
RCC_tenumErrorStatus RCC_ControlPLLOff(void);
RCC_tenumErrorStatus RCC_EnablePriphralCLK(uint32_t Copy_PriphralMask);
RCC_tenumErrorStatus RCC_PLLConfiguration (	uint8_t  	Copy_PLLM,
											uint16_t 	Copy_PLLN,
											uint8_t  	Copy_PLLP,
											uint8_t  	Copy_PLLQ,
											uint8_t  	Copy_PLLSRC);


void RCC_RemoveResetFlag(void);



#endif /* RCC_H_ */
