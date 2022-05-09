/*===========================================================================*/
/* Project:  WeAct Black Pill V1.2 board Sample Software                     */
/* Module :  RCC.c                                                           */
/* Version:  V1.00                                                           */
/*===========================================================================*/
/* History:                                                                  */
/*              V1.00: Initial version                                       */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
/* Source code for the clock configurations                                  */
/*                                                                           */
/*===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "RCC.h"



/*---- structure for RCC Registers  --------------------*/
typedef struct
{
	uint32_t RCC_CR;
	uint32_t RCC_PLLCFGR;
	uint32_t RCC_CFGR;
	uint32_t RCC_CIR;
	uint32_t RCC_AHB1RSTR;
	uint32_t RCC_AHB2RSTR;
	uint32_t RCC_RESERV1;
	uint32_t RCC_RESERV2;
	uint32_t RCC_APB1RSTR;
	uint32_t RCC_APB2RSTR;
	uint32_t RCC_RESERV3;
	uint32_t RCC_RESERV4;
	uint32_t RCC_AHB1ENR;
	uint32_t RCC_AHB2ENR;
	uint32_t RCC_RESERV5;
	uint32_t RCC_RESERV6;
	uint32_t RCC_APB1ENR;
	uint32_t RCC_APB2ENR;
	uint32_t RCC_RESERV7;
	uint32_t RCC_RESERV8;
	uint32_t RCC_AHB1LPENR;
	uint32_t RCC_AHB2LPENR;
	uint32_t RCC_RESERV9;
    uint32_t RCC_RESERV10;
    uint32_t RCC_APB1LPENR;
    uint32_t RCC_APB2LPENR;
	uint32_t RCC_RESERV11;
	uint32_t RCC_RESERV12;
	uint32_t RCC_BDCR;
	uint32_t RCC_CSR;
	uint32_t RCC_RESERV13;
	uint32_t RCC_RESERV14;
	uint32_t RCC_SSCGR;
    uint32_t RCC_PLLI2SCFGR;
    uint32_t RCC_RESERV15;
	uint32_t RCC_DCKCFGR;
}RCCReg_t;





/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/

/*--RCC base address---*/
#define RCC_BASE		                ((volatile RCCReg_t *) 0x40023800u)

/*Function Masks:    RCC_SelectSysClk*/
#define RCC_CFGR_SW_CLR_M     			0x00000003u
#define RCC_CFGR_SWS_GET_M				0x0000000Cu

/*Function Masks:    RCC_ControlHSIOn*/
#define RCC_CR_PLLON_SET_M   	 		0x01000000u
#define RCC_CR_PLLRDY_SET_M				0x02000000u

/*Function Masks:    RCC_ControlHSEOn*/
#define RCC_CR_HSION_SET_M   			0x00000001u
#define RCC_CR_HSIRDY_GET_M   			0x00000002u

/*Function Masks:    RCC_ControlPLLOn*/
#define RCC_CR_HSEON_SET_M				0x00010000u
#define RCC_CR_HSERDY_GET_M				0x00020000u


#define RCC_PLLCFGR_CLR_M				0xF0FC8000u


#define RCC_PLLCFGR_SCR_GET_M			0x00400000u


#define RCC_CSR_RMVF					(uint32_t)0x1000000u


/******************************************************************************
** Function:    RCC_SelectSysClk
** Description: this function select SysClk
** Parameter: 	Copy_u8SysClk
** Return:      RCC_tenumErrorStatus
******************************************************************************/
RCC_tenumErrorStatus RCC_SelectSysClk(uint8_t Copy_u8SysClk)
{

	uint32_t Loc_var;
	volatile uint32_t 	Loc_ReadyRead;


	uint16_t 	Loc_timer = 2500;
	RCC_tenumErrorStatus Loc_ErrorStatus = RCC_enumSWSerror;

	/*Read RCC_CFGR register*/
	Loc_var = RCC_BASE->RCC_CFGR;
	/*check if the system clock is selected*/
	if((Loc_var & RCC_CFGR_SWS_GET_M) == ((uint32_t)Copy_u8SysClk << 2))
	{
		Loc_ErrorStatus = RCC_enumis_selectederror;
	}
	else
	{
		/*clear first two bits*/

		Loc_var &=~ (RCC_CFGR_SW_CLR_M);

		Loc_var |= Copy_u8SysClk;
		RCC_BASE->RCC_CFGR = Loc_var;
		Loc_ReadyRead = (RCC_BASE->RCC_CFGR & RCC_CFGR_SWS_GET_M);
		while(Loc_timer && ! Loc_ReadyRead )
		{
			-- Loc_timer;
			Loc_ReadyRead = (RCC_BASE->RCC_CFGR & RCC_CFGR_SWS_GET_M);
		}
		if(Loc_ReadyRead)
		{
			Loc_ErrorStatus = RCC_enumOK;
		}
	}
	return Loc_ErrorStatus;
}


/******************************************************************************
** Function:    RCC_ControlHSIOn
** Description: this function turn HSI clk ON
** Parameter: 	void
** Return:      RCC_tenumErrorStatus
******************************************************************************/
RCC_tenumErrorStatus RCC_ControlHSIOn(void)
{
	RCC_tenumErrorStatus Loc_ErrorStatus = RCC_enumHSIRDYerror;
	uint8_t 	Loc_timer = 50;
	volatile uint32_t 	Loc_ReadyRead;

	/*set HSION bit in  RCC_CR reg*/
	RCC_BASE->RCC_CR |= RCC_CR_HSION_SET_M;

	/*Read bit in RCC_CR*/
	Loc_ReadyRead = (RCC_BASE->RCC_CR & RCC_CR_HSIRDY_GET_M);

	/*if Loc_timer = 0 or Loc_Ready = 1 -> break */
	while(Loc_timer && !Loc_ReadyRead )
	{
		-- Loc_timer;
		Loc_ReadyRead = (RCC_BASE->RCC_CR & RCC_CR_HSIRDY_GET_M);
	}
	if(Loc_ReadyRead)
	{
		Loc_ErrorStatus = RCC_enumOK;
	}
	return Loc_ErrorStatus;
}
/******************************************************************************
** Function:    RCC_ControlHSEOn
** Description: this function turn HSE clk ON
** Parameter: 	void
** Return:      RCC_tenumErrorStatus
******************************************************************************/
RCC_tenumErrorStatus RCC_ControlHSEOn(void)
{
	RCC_tenumErrorStatus Loc_ErrorStatus = RCC_enumHSIRDYerror;
	uint8_t 	Loc_timer = 50;
	volatile uint32_t 	Loc_ReadyRead;

	/*set HSEON bit in  RCC_CR reg*/
	RCC_BASE->RCC_CR |= RCC_CR_HSEON_SET_M;

	/*Read bit in RCC_CR*/
	Loc_ReadyRead = (RCC_BASE->RCC_CR & RCC_CR_HSEON_SET_M);

	/*if Loc_timer = 0 or Loc_Ready = 1 -> break */
	while(Loc_timer && !Loc_ReadyRead )
	{
		-- Loc_timer;
		Loc_ReadyRead = (RCC_BASE->RCC_CR & RCC_CR_HSEON_SET_M);
	}
	if(Loc_ReadyRead)
	{
		Loc_ErrorStatus = RCC_enumOK;
	}
	return Loc_ErrorStatus;
}
/******************************************************************************
** Function:    RCC_ControlPLLOn
** Description: this function turn PLL clk ON
** Parameter: 	void
** Return:      RCC_tenumErrorStatus
******************************************************************************/
RCC_tenumErrorStatus RCC_ControlPLLOn(void)
{
	RCC_tenumErrorStatus Loc_ErrorStatus = RCC_enumPLLRDYerror;
	uint8_t 	Loc_timer = 50;
	volatile uint32_t 	Loc_ReadyRead;

	/*set RCC_PLLON bit in RCC_CR reg*/
	RCC_BASE->RCC_CR |= RCC_CR_PLLON_SET_M;

	/*Read bit in RCC_CR*/
	Loc_ReadyRead = (RCC_BASE->RCC_CR & RCC_CR_PLLRDY_SET_M);

	/*if Loc_timer = 0 or Loc_Ready = 1 -> break*/
	while(Loc_timer && !Loc_ReadyRead )
	{
		-- Loc_timer;
		Loc_ReadyRead = (RCC_BASE->RCC_CR & RCC_CR_PLLRDY_SET_M);
	}
	if(Loc_ReadyRead)
	{
		Loc_ErrorStatus = RCC_enumOK;
	}
	return Loc_ErrorStatus;
}
/******************************************************************************
** Function:    RCC_ControlHSIOff
** Description: this function turn HSI clk OFF
** Parameter: 	void
** Return:      RCC_tenumErrorStatus
******************************************************************************/

RCC_tenumErrorStatus RCC_ControlHSIOff(void)
{
	RCC_tenumErrorStatus Loc_ErrorStatus = RCC_enumOK;

	/*check if the system clock is selected*/
	if((RCC_BASE->RCC_CFGR & RCC_CFGR_SWS_GET_M) == (RCC_Sysclk_HSI << 2))
	{
		Loc_ErrorStatus = RCC_enumSelectSysClkerror;
	}
	/*chech if HSI is sourcs clk for PLL*/
	else if((RCC_BASE->RCC_CFGR & RCC_CFGR_SWS_GET_M) == (RCC_Sysclk_PLL << 2))
	{
		if(!(RCC_BASE->RCC_PLLCFGR & RCC_PLLCFGR_SCR_GET_M))
		{
			Loc_ErrorStatus = RCC_enumSelectSysClkerror;
		}
	}
	else
	{
		RCC_BASE->RCC_CR &= ~RCC_CR_HSION_SET_M;
	}
	return Loc_ErrorStatus;
}
/******************************************************************************
** Function:    RCC_ControlHSEOn
** Description: this function turn HSE clk OFF
** Parameter: 	void
** Return:      RCC_tenumErrorStatus
******************************************************************************/

RCC_tenumErrorStatus RCC_ControlHSEOff(void)
{
	RCC_tenumErrorStatus Loc_ErrorStatus = RCC_enumOK;

	/*check if the system clock is selected*/
	if((RCC_BASE->RCC_CFGR & RCC_CFGR_SWS_GET_M) == (RCC_Sysclk_HSE << 2))
	{
		Loc_ErrorStatus = RCC_enumSelectSysClkerror;
	}
	/*chech if HSI is sourcs clk for PLL*/
	else if((RCC_BASE->RCC_CFGR & RCC_CFGR_SWS_GET_M) == (RCC_Sysclk_PLL << 2))
	{
		Loc_ErrorStatus = RCC_enumSelectSysClkerror;
		if(RCC_BASE->RCC_PLLCFGR & RCC_PLLCFGR_SCR_GET_M)
		{
			Loc_ErrorStatus = RCC_enumSelectSysClkerror;
		}
	}
	else
	{
		RCC_BASE->RCC_CR &= ~RCC_CR_HSEON_SET_M;
	}
	return Loc_ErrorStatus;
}
/******************************************************************************
** Function:    RCC_ControlPLLOn
** Description: this function turn PLL clk ON
** Parameter: 	void
** Return:      RCC_tenumErrorStatus
******************************************************************************/
RCC_tenumErrorStatus RCC_ControlPLLOff(void)
{
	RCC_tenumErrorStatus Loc_ErrorStatus = RCC_enumOK;

	/*check if the system clock is selected*/
	if((RCC_BASE->RCC_CFGR & RCC_CFGR_SWS_GET_M) == (RCC_Sysclk_PLL << 2))
	{
		Loc_ErrorStatus = RCC_enumSelectSysClkerror;
	}
	else
	{
		RCC_BASE->RCC_CR &= ~RCC_CR_PLLON_SET_M;
	}
	return Loc_ErrorStatus;
}
/******************************************************************************
** Function:    RCC_PLLConfigration
** Description: this function Configure the PLL clock outputs according to the formulas
** Parameter: 	Copy_PLLM
**              Copy_PLLN
**              Copy_PLLP
**              Copy_PLLQ
**              Copy_PLLRC
** Return:      RCC_tenumErrorStatus
******************************************************************************/

RCC_tenumErrorStatus RCC_PLLConfiguration(	uint8_t  	Copy_PLLM,
											uint16_t 	Copy_PLLN,
											uint8_t  	Copy_PLLP,
											uint8_t  	Copy_PLLQ,
											uint8_t  	Copy_PLLSRC)
{
	/*Create Return Error status initialize it with OK status  */
	RCC_tenumErrorStatus Loc_enuErrorStatus = RCC_enumOK;

	uint32_t Loc_clock;
	uint16_t Loc_VcoInput , Loc_VcoOutput , Loc_MainSystemClock , Loc_USBOTGFSClock;

	uint32_t Loc_var;
	Loc_var = RCC_BASE->RCC_CFGR;
	if((Loc_var & RCC_CFGR_SWS_GET_M) == (RCC_Sysclk_PLL << 2))
	{
		Loc_enuErrorStatus = RCC_enumSelectSysClkerror;
	}
	else
	{
		/*Calculate VCO input frequency after "PLLM" division factor*/
		Loc_VcoInput = RCC_PLL_SRC / Copy_PLLM;

		/*Calculate  VCO output frequency after "PLLN" multiplication factor*/
		Loc_VcoOutput = (uint16_t)(Loc_VcoInput * Copy_PLLN);

		/*Calculate the frequency of the general PLL output clock after "PLLP" division factor*/
		Loc_MainSystemClock =(uint16_t) Loc_VcoOutput / (uint16_t)(Copy_PLLP*2+2);

		/*Calculate division factor for USB OTG FS, SDIO and random number generator clocks*/
		Loc_USBOTGFSClock =(uint16_t) (Loc_VcoOutput / Copy_PLLQ);

		/*Ensure that VCO input frequency ranges from 1 to 2 MHz
		 *Ensure that PLLM not equal (0,1)
		 * */
		if( Loc_VcoInput < 2
		   || Copy_PLLM  < 1)
		{
			Loc_enuErrorStatus = RCC_enumPLLMerror;
		}

		/*Ensure that VCO output frequency is between 192 and 432 MHz
		 *Ensure that PLLN not equal (0,1,433-511)
		 * */
		else if(   Loc_VcoOutput < 192
				|| Loc_VcoOutput > 432
				|| Copy_PLLN <	2
				|| Copy_PLLN > 433)
		{
			Loc_enuErrorStatus = RCC_enumPLLNerror;
		}
		/*Ensure that the general PLL output clock after "PLLP" division factor
		 *not to exceed 84 MHz
		 * */
		else if( Loc_MainSystemClock > 84)
		{
			Loc_enuErrorStatus = RCC_enumPLLPerror;
		}
		/*The USB OTG FS requires a 48 MHz clock to work correctly. The SDIO and the
		 *random number generator need a frequency lower than or equal to 48 MHz to work
		 *correctly.
		 *****/
		else if(Loc_USBOTGFSClock > 48 )
		{
			Loc_enuErrorStatus = RCC_enumPLLQerror;
		}
		else if( Copy_PLLSRC > RCC_Sysclk_HSE)
		{
			Loc_enuErrorStatus = RCC_enumPLLSRCerror;
		}
		/*set the configuration in the RCC_PLLCFGR */
		else
		{
				Loc_clock = RCC_BASE->RCC_PLLCFGR;
				Loc_clock &= (RCC_PLLCFGR_CLR_M);/*clear all configuration bits in RCC_PLLCFGR*/
				/*set all the configuration in  Local*/
				Loc_clock |=  (uint32_t) Copy_PLLM
							 |(uint32_t) Copy_PLLN   << 6
							 |(uint32_t) Copy_PLLP   << 16
							 |(uint32_t) Copy_PLLSRC << 22
							 |(uint32_t) Copy_PLLQ   << 24;
				/*Set the configuration in RCC_PLLCFGR*/
				RCC_BASE->RCC_PLLCFGR = Loc_clock;
		}
	}
	return Loc_enuErrorStatus;
}
/******************************************************************************
** Function:    RCC_EnablePriphralsinRCC_AHB1ENR
** Description: this function enables peripherals Clock
** Parameter: 	Copy_PriphralMask
** Return:      RCC_tenumErrorStatus
******************************************************************************/
RCC_tenumErrorStatus RCC_EnablePriphralCLK(uint32_t Copy_PriphralMask)
{

	RCC_tenumErrorStatus Loc_enuErrorStatus = RCC_enumOK;

	uint32_t Loc_var = Copy_PriphralMask & RCC_PERIPHERAL_GET_M;
	/*Clear the magic number*/
	Copy_PriphralMask &= ~RCC_PERIPHERAL_GET_M;

	if(Loc_var == RCC_AHB1ENR_GET_M )
	{
		RCC_BASE->RCC_AHB1ENR |= Copy_PriphralMask;
	}
	else if(Loc_var == RCC_AHB2ENR_GET_M )
	{
		RCC_BASE->RCC_AHB2ENR |= Copy_PriphralMask;
	}
	else if(Loc_var == RCC_APB1ENR_GET_M)
	{
		RCC_BASE->RCC_APB1ENR |= Copy_PriphralMask;
	}
	else if(Loc_var == RCC_APB2ENR_GET_M)
	{
		RCC_BASE->RCC_APB2ENR |= Copy_PriphralMask;
	}
	else
	{
		 Loc_enuErrorStatus = RCC_enumWrongPriphralerror;
	}
	return Loc_enuErrorStatus;
}



void RCC_RemoveResetFlag(void)
{
	RCC_BASE->RCC_CSR |= RCC_CSR_RMVF;
}
