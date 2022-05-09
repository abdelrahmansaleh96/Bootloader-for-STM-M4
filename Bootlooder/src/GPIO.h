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
/*  Header file for the GPIO.c source code                                   */
/*                                                                           */
/*===========================================================================*/

#ifndef GPIO_H_
#define GPIO_H_

#define GPIO_LOW												0u
#define GPIO_HIGH												1u



#define GPIOA													 (void*)0x40020000u
#define GPIOB		                				             (void*)0x40020400u
#define GPIOC		                				             (void*)0x40020800u
#define GPIOD		                				             (void*)0x40020C00u
#define GPIOE		                				             (void*)0x40021000u
#define GPIOH													 (void*)0x40021C00u


#define GPIO_PIN_0								 	             0u
#define GPIO_PIN_1                                               1u
#define GPIO_PIN_2                                               2u
#define GPIO_PIN_3                                               3u
#define GPIO_PIN_4                                  			 4u
#define GPIO_PIN_5                                  			 5u
#define GPIO_PIN_6												 6u
#define GPIO_PIN_7                     				             7u
#define GPIO_PIN_8                     	        			     8u
#define GPIO_PIN_9                         			             9u
#define GPIO_PIN_10              			                    10u
#define GPIO_PIN_11                 			                11u
#define GPIO_PIN_12                              			    12u
#define GPIO_PIN_13                     		    	        13u
#define GPIO_PIN_14                 			                14u
#define GPIO_PIN_15                   	        		        15u
														//0bPUPDR[4,3]OTYPER[2]Moder[1,0]
		/*---input---*/
#define MODE_INPUT_FLOATING										0b00000u
#define MODE_INPUT_PULL_UP										0b01000u
#define MODE_INPUT_PULL_DOWN									0b10000u
/*---output---*/
#define MODE_OUTPUT_PUSH_PULL									0b00001u
#define MODE_OUTPUT_PUSH_PULL_PULL_UP							0b01001u
#define MODE_OUTPUT_PUSH_PULL_PULL_DOWN							0b10001u

#define MODE_OUTPUT_OPEN_DRAIN									0b00101u
#define MODE_OUTPUT_OPEN_DRAIN_PULL_UP							0b01101u
#define	MODE_OUTPUT_OPEN_DRAIN_PULL_DOWN						0b10101u
/*---ALT---*/
#define MODE_ALT_FUNC_PUSH_PULL					    			0b00010u
#define MODE_ALT_FUNC_PUSH_PULL_UP								0b01010u
#define MODE_ALT_FUNC_PUSH_PULL_DOWN							0b10010u

#define MODE_ALT_FUNC_OPEN_DRAIN								0b00110u
#define MODE_ALT_FUNC_OPEN_DRAIN_PULL_UP						0b01110u
#define	MODE_ALT_FUNC_OPEN_DRAIN_PULL_DOWN						0b10110u

/*---Analog---*/
#define MODE_ANALOG												0b00011u

/*---Speed ---*/
#define SPEED_LOW												0b00u
#define SPEED_MEDIUM											0b01u
#define SPEED_HIGH												0b10u
#define SPEED_VERY_HIGH											0b11u


#define GPIO_BIT_HIGH_0											0x00000001u
#define GPIO_BIT_HIGH_1			                                0x00000002u
#define GPIO_BIT_HIGH_2			                                0x00000004u
#define GPIO_BIT_HIGH_3			                                0x00000008u
#define GPIO_BIT_HIGH_4 		                                0x00000010u
#define GPIO_BIT_HIGH_5			                                0x00000020u
#define GPIO_BIT_HIGH_6			                                0x00000040u
#define GPIO_BIT_HIGH_7			                                0x00000080u
#define GPIO_BIT_HIGH_8			                                0x00000100u
#define GPIO_BIT_HIGH_9                                         0x00000200u
#define GPIO_BIT_HIGH_10                                        0x00000400u
#define GPIO_BIT_HIGH_11                                        0x00000800u
#define GPIO_BIT_HIGH_12                                        0x00001000u
#define GPIO_BIT_HIGH_13                                        0x00002000u
#define GPIO_BIT_HIGH_14                                        0x00004000u
#define GPIO_BIT_HIGH_15                                        0x00008000u

#define GPIO_BIT_LOW_0        	                                0x00010000u
#define GPIO_BIT_LOW_1        	                                0x00020000u
#define GPIO_BIT_LOW_2        	                                0x00040000u
#define GPIO_BIT_LOW_3        	                                0x00080000u
#define GPIO_BIT_LOW_4        	                                0x00100000u
#define GPIO_BIT_LOW_5        	                                0x00200000u
#define GPIO_BIT_LOW_6        	                                0x00400000u
#define GPIO_BIT_LOW_7        	                                0x00800000u
#define GPIO_BIT_LOW_8        	                                0x01000000u
#define GPIO_BIT_LOW_9        	                                0x02000000u
#define GPIO_BIT_LOW_10       	                                0x04000000u
#define GPIO_BIT_LOW_11      	                                0x08000000u
#define GPIO_BIT_LOW_12       	                                0x10000000u
#define GPIO_BIT_LOW_13       	                                0x20000000u
#define GPIO_BIT_LOW_14       	                                0x40000000u
#define GPIO_BIT_LOW_15       	                                0x80000000u


#define	GPIO_AF0 													(uint8_t)0b0000u
#define	GPIO_AF1 													(uint8_t)0b0001u
#define	GPIO_AF2 													(uint8_t)0b0010u
#define	GPIO_AF3 													(uint8_t)0b0011u
#define	GPIO_AF4 													(uint8_t)0b0100u
#define	GPIO_AF5 													(uint8_t)0b0101u
#define	GPIO_AF6 													(uint8_t)0b0110u
#define	GPIO_AF7 													(uint8_t)0b0111u
#define	GPIO_AF8 													(uint8_t)0b1000u
#define	GPIO_AF9 													(uint8_t)0b1001u
#define	GPIO_AF10													(uint8_t)0b1010u
#define	GPIO_AF11													(uint8_t)0b1011u
#define	GPIO_AF12													(uint8_t)0b1100u
#define	GPIO_AF13													(uint8_t)0b1101u
#define	GPIO_AF14													(uint8_t)0b1110u
#define	GPIO_AF15													(uint8_t)0b1111u





















typedef struct
{
	void* 	    port;
	uint8_t 	mode;
	uint8_t 	speed;
	uint8_t 	pin;
	uint8_t		alt;
}GpioPincfg_t;


typedef enum
{
	GPIO_NULLptr,
	GPIO_enumPinModeError,
	GPIO_enumValueError,
    GPIO_enumOK
}GPIO_tenumErrorStatus;



extern GPIO_tenumErrorStatus Gpio_enuinitPinCfg(GpioPincfg_t* Add_pin);
//GPIO_tenumErrorStatus Gpio_enuSetPintValue(GpioPincfg_t* Add_pin,uint32_t value);
extern GPIO_tenumErrorStatus Gpio_enuSetPintValue(void * port,uint8_t pin,uint8_t value);
extern GPIO_tenumErrorStatus Gpio_enuGetPinValue(void * port,uint8_t pin,uint8_t* value);
extern GPIO_tenumErrorStatus Gpio_enuSetAF(void * port,uint8_t pin, uint8_t AF_Value);

#endif
