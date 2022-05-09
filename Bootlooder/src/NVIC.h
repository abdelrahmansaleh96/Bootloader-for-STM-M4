#ifndef NVIC_H_
#define NVIC_H_



typedef enum
{
	NVIC_enumNULLPtrerror,
	NVIC_enumIRQnumerror,
	NVIC_enumPeriortyerror,
	NVIC_enumOK
}NVIC_tenumErrorStatus;

typedef enum
{
    IRQ_enuWWDG_IRQHandler,                   // Window WatchDog
    IRQ_enuPVD_IRQHandler,                    // PVD through EXTI Line detection
    IRQ_enuTAMP_STAMP_IRQHandler,             // Tamper and TimeStamps through the EXTI line
    IRQ_enuRTC_WKUP_IRQHandler,               // RTC Wakeup through the EXTI line
    IRQ_enuFLASH_IRQHandler,                  // FLASH
    IRQ_enuRCC_IRQHandler,                    // RCC
    IRQ_enuEXTI0_IRQHandler,                  // EXTI Line0
    IRQ_enuEXTI1_IRQHandler,                  // EXTI Line1
    IRQ_enuEXTI2_IRQHandler,                  // EXTI Line2
    IRQ_enuEXTI3_IRQHandler,                  // EXTI Line3
    IRQ_enuEXTI4_IRQHandler,                  // EXTI Line4
    IRQ_enuDMA1_Stream0_IRQHandler,           // DMA1 Stream 0
    IRQ_enuDMA1_Stream1_IRQHandler,           // DMA1 Stream 1
    IRQ_enuDMA1_Stream2_IRQHandler,           // DMA1 Stream 2
    IRQ_enuDMA1_Stream3_IRQHandler,           // DMA1 Stream 3
    IRQ_enuDMA1_Stream4_IRQHandler,           // DMA1 Stream 4
    IRQ_enuDMA1_Stream5_IRQHandler,           // DMA1 Stream 5
    IRQ_enuDMA1_Stream6_IRQHandler,           // DMA1 Stream 6
    IRQ_enuADC_IRQHandler,                    // ADC1, ADC2 and ADC3s
    IRQ_enuReserved,
    IRQ_enuReserved0,
    IRQ_enuReserved1,
	IRQ_enuReserved2,
    IRQ_enuEXTI9_5_IRQHandler,                // External Line[9:5]s
    IRQ_enuTIM1_BRK_TIM9_IRQHandler,          // TIM1 Break and TIM9
    IRQ_enuTIM1_UP_TIM10_IRQHandler,          // TIM1 Update and TIM10
    IRQ_enuTIM1_TRG_COM_TIM11_IRQHandler,     // TIM1 Trigger and Commutation and TIM11
    IRQ_enuTIM1_CC_IRQHandler,                // TIM1 Capture Compare
    IRQ_enuTIM2_IRQHandler,                   // TIM2
    IRQ_enuTIM3_IRQHandler,                   // TIM3
    IRQ_enuTIM4_IRQHandler,                   // TIM4
    IRQ_enuI2C1_EV_IRQHandler,                // I2C1 Event
    IRQ_enuI2C1_ER_IRQHandler,                // I2C1 Error
    IRQ_enuI2C2_EV_IRQHandler,                // I2C2 Event
    IRQ_enuI2C2_ER_IRQHandler,                // I2C2 Error
    IRQ_enuSPI1_IRQHandler,                   // SPI1
    IRQ_enuSPI2_IRQHandler,                   // SPI2
    IRQ_enuUSART1_IRQHandler,                 // USART1
    IRQ_enuUSART2_IRQHandler,                 // USART2
    IRQ_enuReserved3,
    IRQ_enuEXTI15_10_IRQHandler,              // External Line[15:10]s
    IRQ_enuRTC_Alarm_IRQHandler,              // RTC Alarm (A and B) through EXTI Line
    IRQ_enuOTG_FS_WKUP_IRQHandler,            // USB OTG FS Wakeup through EXTI line
    IRQ_enuReserved4,
    IRQ_enuReserved5,
    IRQ_enuReserved6,
    IRQ_enuReserved7,
    IRQ_enuDMA1_Stream7_IRQHandler,           // DMA1 Stream7
    IRQ_enuReserved9,
    IRQ_enuSDIO_IRQHandler,                   // SDIO
    IRQ_enuTIM5_IRQHandler,                   // TIM5
    IRQ_enuSPI3_IRQHandler,                   // SPI3
    IRQ_enuReserved10,
    IRQ_enuReserved12,
    IRQ_enuReserved13,
    IRQ_enuReserved14,
    IRQ_enuDMA2_Stream0_IRQHandler,           // DMA2 Stream 0
    IRQ_enuDMA2_Stream1_IRQHandler,           // DMA2 Stream 1
    IRQ_enuDMA2_Stream2_IRQHandler,           // DMA2 Stream 2
    IRQ_enuDMA2_Stream3_IRQHandler,           // DMA2 Stream 3
    IRQ_enuDMA2_Stream4_IRQHandler,           // DMA2 Stream 4
    IRQ_enuReserved15,
    IRQ_enuReserved16,
    IRQ_enuReserved17,
    IRQ_enuReserved18,
    IRQ_enuReserved19,
    IRQ_enuReserved20,
    IRQ_enuOTG_FS_IRQHandler,                 // USB OTG FS
    IRQ_enuDMA2_Stream5_IRQHandler,           // DMA2 Stream 5
    IRQ_enuDMA2_Stream6_IRQHandler,           // DMA2 Stream 6
    IRQ_enuDMA2_Stream7_IRQHandler,           // DMA2 Stream 7
    IRQ_enuUSART6_IRQHandler,                 // USART6
    IRQ_enuI2C3_EV_IRQHandler,                // I2C3 event
    IRQ_enuI2C3_ER_IRQHandler,                // I2C3 error
    IRQ_enuReserved21,
    IRQ_enuReserved22,
    IRQ_enuReserved23,
    IRQ_enuReserved24,
    IRQ_enuReserved25,
    IRQ_enuReserved26,
    IRQ_enuReserved27,
    IRQ_enuFPU_IRQHandler,                    // FPU
    IRQ_enuReserved28,
    IRQ_enuReserved29,
    IRQ_enuSPI4_IRQHandler,                   // SPI4
}IRQ_t;




#define NVIC_LEVEL1					0x10u
#define NVIC_LEVEL2					0x20u
#define NVIC_LEVEL3                 0x40u
#define NVIC_LEVEL4                 0x60u
#define NVIC_LEVEL5                 0x80u
#define NVIC_LEVEL6                 0xA0u
#define NVIC_LEVEL7                 0xC0u
#define NVIC_LEVEL8                 0xE0u
#define NVIC_LEVEL9                 0x30u
#define NVIC_LEVEL10                0x50u
#define NVIC_LEVEL11                0x70u
#define NVIC_LEVEL12                0x90u
#define NVIC_LEVEL13                0xB0u
#define NVIC_LEVEL14                0xD0u
#define NVIC_LEVEL15                0xF0u







/******************************************************************************
** Function:    NVIC_EnableIRQ
** Description: Enables an interrupt or exception
** Parameter: 	Copy_IRQ
** Return:      NVIC_tenumErrorStatus
******************************************************************************/

NVIC_tenumErrorStatus NVIC_vidEnableIRQ(IRQ_t Copy_IRQ);

/******************************************************************************
** Function:    NVIC_vidDisableIRQ
** Description: Disables an interrupt or exception
** Parameter: 	Copy_IRQ
** Return:      NVIC_tenumErrorStatus
******************************************************************************/
NVIC_tenumErrorStatus NVIC_vidDisableIRQ(IRQ_t Copy_IRQ);


/******************************************************************************
** Function:    NVIC_vidSetPendingIRQ
** Description: Sets the pending status of interrupt or exception to 1
** Parameter: 	Copy_IRQ
** Return:      NVIC_tenumErrorStatus
******************************************************************************/
NVIC_tenumErrorStatus NVIC_vidSetPendingIRQ(IRQ_t Copy_IRQ);

/******************************************************************************
** Function:    NVIC_vidClearPendingIRQ
** Description: Clears the pending status of interrupt or exception to 0
** Parameter: 	Copy_IRQ
** Return:      NVIC_tenumErrorStatus
******************************************************************************/
NVIC_tenumErrorStatus NVIC_vidClearPendingIRQ(IRQ_t Copy_IRQ);



/******************************************************************************
** Function:    NVIC_u32GetPendingIRQ
** Description: Reads the pending status of interrupt or exception.
** 				This function put nonzero value  in Add_PendingStatus if the pending status is set to 1.
** Parameter: 	Copy_IRQ,Add_PendingStatus
** Return:      NVIC_tenumErrorStatus
******************************************************************************/
NVIC_tenumErrorStatus NVIC_u32GetPendingIRQ(IRQ_t Copy_IRQ ,uint32_t*  Add_PendingStatus);


/* Sets the priority of an interrupt or
 * exception with configurable priority level to 1.
 * */

/******************************************************************************
** Function:    NVIC_u32GetPendingIRQ
** Description: Sets the priority of an interrupt or exception with configurable priority level to 1
** Parameter: 	Copy_IRQ,Add_PendingStatus
** Return:      NVIC_tenumErrorStatus
******************************************************************************/
NVIC_tenumErrorStatus NVIC_vidSetPriority(IRQ_t Copy_IRQ, uint32_t priority);

/* Reads the priority of an interrupt or
 * exception with configurable priority level.
 * This function return the current priority level.
 * */
uint32_t NVIC_u32GetPriority(IRQ_t Copy_IRQ);

#endif

