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
/* Source code for the General purpose Input output configurations           */
/*                                                                           */
/*===========================================================================*/

//#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "GPIO.h"


typedef struct
{
	uint32_t MODER;		//0
	uint32_t OTYPER;	//4
	uint32_t OSPEEDR;	//8
	uint32_t PUPDR;		//c
	uint32_t IDR;		//10
	uint32_t ODR;		//14
	uint32_t BSRR;		//18
	uint32_t LCKR;		//1c
	uint32_t AFRL;		//20
	uint32_t AFRH;		//24
}GPIOReg_t;


/*
#define GPIO_MODER_GET_M		0b00011

#define GPIO_OTYPER_GET_M		0b00001

#define GPIO_PUPDR_GET_M		0b00011

#define GPIO_OSPEEDR_CLR_M		0b00011*/

#define GPIO_TWO_BIT_M			0b00011u
#define GPIO_FOUR_BIT_M			0b001111u

#define GPIO_ONE_BIT_M			0b00001u


#define GPIO_GET_BIT_0											0x00000001u
#define GPIO_GET_BIT_1			                                0x00000002u
#define GPIO_GET_BIT_2			                                0x00000004u
#define GPIO_GET_BIT_3			                                0x00000008u
#define GPIO_GET_BIT_4 		                                	0x00000010u
#define GPIO_GET_BIT_5			                                0x00000020u
#define GPIO_GET_BIT_6			                                0x00000040u
#define GPIO_GET_BIT_7			                                0x00000080u
#define GPIO_GET_BIT_8			                                0x00000100u
#define GPIO_GET_BIT_9                                          0x00000200u
#define GPIO_GET_BIT_10                                       	0x00000400u
#define GPIO_GET_BIT_11                                        	0x00000800u
#define GPIO_GET_BIT_12                                         0x00001000u
#define GPIO_GET_BIT_13                                         0x00002000u
#define GPIO_GET_BIT_14                                         0x00004000u
#define GPIO_GET_BIT_15                                         0x00008000u



//0b00011
GPIO_tenumErrorStatus Gpio_enuinitPinCfg(GpioPincfg_t* Add_pin)
{
	GPIO_tenumErrorStatus  Loc_enuErrorStatus = GPIO_enumOK;
	if(Add_pin == NULL)
	{
		Loc_enuErrorStatus = GPIO_NULLptr;
	}
	else
	{
		/*---------MODER----------*/
		uint32_t Loc_TempREG = ((volatile GPIOReg_t *) (Add_pin->port))->MODER;

		Loc_TempREG &=  ~(GPIO_TWO_BIT_M << (Add_pin->pin * 2));
		Loc_TempREG |= (GPIO_TWO_BIT_M   &  Add_pin->mode) << (Add_pin->pin * 2);

		((volatile GPIOReg_t *) (Add_pin->port))->MODER  = Loc_TempREG;

		/*----------OTYPER---------*/
		 Loc_TempREG = ((volatile GPIOReg_t *) (Add_pin->port))->OTYPER;

		Loc_TempREG &=  ~(GPIO_ONE_BIT_M << (Add_pin->pin ));
		Loc_TempREG |=  (GPIO_ONE_BIT_M   &  Add_pin->mode>>2) << (Add_pin->pin );

		((volatile GPIOReg_t *) (Add_pin->port))->OTYPER |= Loc_TempREG;

		/*----------PUPDR----------*/
		Loc_TempREG = ((volatile GPIOReg_t *) (Add_pin->port))->PUPDR;

		Loc_TempREG &=  ~(GPIO_TWO_BIT_M << (Add_pin->pin *2));
		Loc_TempREG |= (GPIO_TWO_BIT_M   &  (Add_pin->mode>>3)) << (Add_pin->pin*2);

		((volatile GPIOReg_t *) (Add_pin->port))->PUPDR  = Loc_TempREG;


		/*--------OSPEEDR----------*/
		Loc_TempREG = ((volatile GPIOReg_t *) (Add_pin->port))->OSPEEDR;

		Loc_TempREG &=  ~(GPIO_TWO_BIT_M << (Add_pin->pin *2));
		Loc_TempREG |=  (uint32_t)(Add_pin->speed << (Add_pin->pin*2));

		((volatile GPIOReg_t *) (Add_pin->port))->OSPEEDR = Loc_TempREG;
	}
	return Loc_enuErrorStatus;
}

/*
GPIO_tenumErrorStatus Gpio_enuSetPintValue(GpioPincfg_t* Add_pin,uint32_t value)
{
	GPIO_tenumErrorStatus  Loc_enuErrorStatus = GPIO_enumOK;
	((volatile GPIOReg_t *) (Add_pin->port))->BSRR = value;
	return Loc_enuErrorStatus;
}
*/
GPIO_tenumErrorStatus Gpio_enuSetPintValue(void * port,uint8_t pin,uint8_t value)
{
	GPIO_tenumErrorStatus  Loc_enuErrorStatus = GPIO_enumOK;
	if(port == NULL)
	{
		Loc_enuErrorStatus = GPIO_NULLptr;
	}
	else if(pin > 15)
	{
		Loc_enuErrorStatus = GPIO_enumPinModeError;
	}
	else if(value> 1)
	{
		Loc_enuErrorStatus = GPIO_enumValueError;
	}
	else
	{
		switch(value)
		{
		 case GPIO_HIGH:
			 ((volatile GPIOReg_t *) port)->BSRR = 1u << pin;
			 break;
		 case GPIO_LOW:
			 ((volatile GPIOReg_t *) port)->BSRR = 1u << (pin+16u);
			 break;
		}
	}
	return Loc_enuErrorStatus;
}


GPIO_tenumErrorStatus Gpio_enuGetPinValue(void * port,uint8_t pin,uint8_t* value)
{
	GPIO_tenumErrorStatus  Loc_enuErrorStatus = GPIO_enumOK;
	if(port == NULL || value == NULL )
	{
		Loc_enuErrorStatus = GPIO_NULLptr;
	}
	else if(pin > 15)
	{
		Loc_enuErrorStatus = GPIO_enumPinModeError;
	}
	else
	{
		*value = ((((volatile GPIOReg_t *) (port))->IDR) >> (pin)) & 1u;
	}
	return Loc_enuErrorStatus;
}

GPIO_tenumErrorStatus Gpio_enuSetAF(void * port,uint8_t pin, uint8_t AF_Value)
{
	GPIO_tenumErrorStatus  Loc_enuErrorStatus = GPIO_enumOK;
	uint32_t Loc_TempREG;
	if(pin > 15)
	{
		Loc_enuErrorStatus = GPIO_enumPinModeError;
	}
	else if(pin <= 7)
	{
		Loc_TempREG = ((volatile GPIOReg_t *) port)->AFRL;

		Loc_TempREG &=  ~(GPIO_FOUR_BIT_M << (pin * 4));
		Loc_TempREG |=  (uint32_t)(AF_Value << (pin * 4));

		((volatile GPIOReg_t *) (port))->AFRL  = Loc_TempREG;
	}
	else
	{
		Loc_TempREG = ((volatile GPIOReg_t *) port)->AFRH;

		Loc_TempREG &=  ~(GPIO_FOUR_BIT_M << ((pin-8) * 4));
		Loc_TempREG |=   (uint32_t)(AF_Value << ((pin-8) * 4));

		((volatile GPIOReg_t *) (port))->AFRH  = Loc_TempREG;
	}

	return Loc_enuErrorStatus;
}







