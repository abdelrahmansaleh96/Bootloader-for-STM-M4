#ifndef DMA_H_
#define DMA_H_



typedef struct
{
	uint32_t DMA_SCR;
	uint32_t DMA_SNDTR;
	uint32_t DMA_SPAR;
	uint32_t DMA_SM0AR;
	uint32_t DMA_SM1AR;
	uint32_t DMA_SFCR;
}DMAReg_t;


typedef struct
{
  uint32_t DMA_LISR;   /*!< DMA interrupt status register */
  uint32_t DMA_HISR;
  uint32_t DMA_LIFCR;  /*!< DMA interrupt flag clear register */
  uint32_t DMA_HIFCR;

} DMA_Base_Registers_t;

typedef enum
{
	DMAOk,
	DMANot_Ok,
	DMANull_ptr,
	DMAbusy,
}DMA_StatusTypeDef;

typedef struct
{
	uint32_t BaseAddress; /*---DMA BaseAddress Selection---*/

	uint32_t StreamNum;	/*0 - 7*/

	uint32_t Channel; /*---DMA Channel Selection---*/

	uint32_t DataTransferDirection;  /*---DMA DataTransferDirection Selection---*/

	uint32_t PriorityLevel;  /*---DMA PriorityLevel Selection---*/

	uint32_t MemoryDataSize; /*---DMA MemoryDataSize Selection---*/

	uint32_t PeripheralDataSize;  /*---DMA PeripheralDataSize Selection---*/

	uint32_t MemoryIncrementMode; /*---DMA MemoryIncrementMode Selection---*/

	uint32_t PeripheralIncrementMode; /*---DMA PeripheralIncrementMode Selection---*/

	uint32_t Mode;	/*---DMA Mode Selection---*/

	uint32_t TransferCompleteInterruptEnable;  /*---DMA TransferCompleteInterruptEnable Selection---*/

	uint32_t CurrentTarget;

}DMAcfg_t;


typedef enum
{
	DMA1_Stream0Cbf = 0,
	DMA1_Stream1Cbf = 1,
	DMA1_Stream2Cbf = 2,
	DMA1_Stream3Cbf = 3,
	DMA1_Stream4Cbf = 4,
	DMA1_Stream5Cbf = 5,
	DMA1_Stream6Cbf = 6,
	DMA1_Stream7Cbf = 7,
	DMA2_Stream0Cbf = 8,
	DMA2_Stream1Cbf = 9,
	DMA2_Stream2Cbf = 10,
	DMA2_Stream3Cbf = 11,
	DMA2_Stream4Cbf = 12,
	DMA2_Stream5Cbf = 13,
	DMA2_Stream6Cbf = 14,
	DMA2_Stream7Cbf = 15,
}StramCbfNum_t;

/*---Bits definition for DMA_SxCR register---*/
#define DMA_SxCR_EN											0x1u
#define DMA_SxCR_DMEIE                                      0x2u
#define DMA_SxCR_TEIE                                       0x4u
#define DMA_SxCR_HTIE                                       0x8u
#define DMA_SxCR_TCIE                                       0x10u
#define DMA_SxCR_PFCTRL                                     0x20u
#define DMA_SxCR_DIR0                                       0x40u
#define DMA_SxCR_DIR1                                       0x80u
#define DMA_SxCR_CIRC                                       0x100u
#define DMA_SxCR_PINC                                       0x200u
#define DMA_SxCR_MINC                                       0x400u
#define DMA_SxCR_PSIZE0                                     0x800u
#define DMA_SxCR_PSIZE1                                     0x1000u
#define DMA_SxCR_MSIZE0                                     0x2000u
#define DMA_SxCR_MSIZE1                                     0x4000u
#define DMA_SxCR_PINCOS                                     0x8000u
#define DMA_SxCR_PL0                                        0x10000u
#define DMA_SxCR_PL1                                        0x20000u
#define DMA_SxCR_DBM                                        0x40000u
#define DMA_SxCR_CT                                         0x80000u
#define DMA_SxCR_PBURST0                                    0x200000u
#define DMA_SxCR_PBURST1                                    0x400000u
#define DMA_SxCR_MBURST0                                    0x800000u
#define DMA_SxCR_MBURST1                                    0x1000000u
#define DMA_SxCR_CHSEL0                                     0x2000000u
#define DMA_SxCR_CHSEL1                                     0x4000000u
#define DMA_SxCR_CHSEL2                                     0x8000000u

#define DMA_SxCR											(uint32_t)0xFEFFFFFu



/*---Macro for hardware access---*/
#define __STREAM_REG(BaseAdress,StreamNum)				((volatile DMAReg_t *) (BaseAdress+(0x10+StreamNum*0x18)))

/*---DMA BaseAddress Selection---*/
#define DMA1_BASE												0x40026000u
#define DMA2_BASE												0x40026400u


/*---DMA Channel Selection---*/
#define DMA_CH_0												0x0000000U
#define DMA_CH_1                                                0x2000000U
#define DMA_CH_2                                                0x4000000U
#define DMA_CH_3                                                0x6000000U
#define DMA_CH_4                                                0x8000000U
#define DMA_CH_5                                                0xA000000U
#define DMA_CH_6                                                0xC000000U
#define DMA_CH_7                                                0xE000000U


/*---DMA PriorityLevel Selection---*/
#define DMA_PRIORTY_LEVEL_LOW									(uint32_t)0x0u
#define DMA_PRIORTY_LEVEL_MEDIUM								(uint32_t)DMA_SxCR_PL0
#define DMA_PRIORTY_LEVEL_HIGH									(uint32_t)DMA_SxCR_PL1
#define DMA_PRIORTY_LEVEL_VERY_HIGH						    	(uint32_t)(DMA_SxCR_PL0|DMA_SxCR_PL1)


/*---DMA MemoryDataSize Selection---*/
#define DMA_MEMORY_DATA_SIZE_BYTE								(uint32_t)0x0u
#define DMA_MEMORY_DATA_SIZE_HALF_WORD							(uint32_t)DMA_SxCR_MSIZE0
#define DMA_MEMORY_DATA_SIZE_WORD								(uint32_t)DMA_SxCR_MSIZE1



/*---DMA PeripheralDataSize Selection---*/
#define DMA_PERIPHERAL_DATA_SIZE_BYTE							(uint32_t)0x0u
#define DMA_PERIPHERAL_DATA_SIZE_HALF_WORD						(uint32_t)DMA_SxCR_PSIZE0
#define DMA_PERIPHERAL_DATA_SIZE_WORD							(uint32_t)DMA_SxCR_PSIZE1


/*---DMA MemoryIncrementMode Selection---*/
#define DMA_MEMORY_INCREMENT_MODE_FIXED							(uint32_t)0x0u
#define DMA_MEMORY_INCREMENT_MODE_INCREMENTED					(uint32_t)DMA_SxCR_MINC


/*---DMA PeripheralIncrementMode Selection---*/
#define DMA_PERIPHERAL_INCREMENT_MODE_FIXED						(uint32_t)0x0u
#define DMA_PERIPHERAL_INCREMENT_MODE_INCREMENTED				(uint32_t)DMA_SxCR_PINC

/*---DMA Mode Selection---*/
#define DMA_NORMAL_MODE											(uint32_t)0x0u
#define DMA_CIRCULAR_MODE										(uint32_t)DMA_SxCR_CIRC
#define DMA_PERIPHERAL_FLOW_CONTROLLER_MODE						(uint32_t)DMA_SxCR_PFCTRL


/*---DMA DataTransferDirection Selection---*/
#define DMA_DIRECTION_PERIPHERAL_TO_MEMORY						(uint32_t)0x0u
#define DMA_DIRECTION_MEMORY_TO_PERIPHERAL						(uint32_t)DMA_SxCR_DIR0
#define DMA_DIRECTION_MEMORY_TO_MEMORY		 				    (uint32_t)DMA_SxCR_DIR1

/*---DMA TransferCompleteInterruptEnable Selection---*/
#define DMA_TCIN_DISABLED										(uint32_t)0x0u
#define DMA_TCIN_ENABLED										(uint32_t)DMA_SxCR_TCIE


extern DMA_StatusTypeDef DMA_Init(DMAcfg_t* psDMAcfg);
extern DMA_StatusTypeDef DMA_Start(DMAcfg_t* psDMAcfg,uint32_t pu32Src,uint32_t pu32Dest,uint32_t DataSize);

void DMA_StremRegisterCbf( void (*pfDmaStrCbf) (void) ,StramCbfNum_t num);
void DMA1_Stream0_IRQHandler(void);
void DMA1_Stream1_IRQHandler(void);
void DMA1_Stream2_IRQHandler(void);
void DMA1_Stream3_IRQHandler(void);
void DMA1_Stream4_IRQHandler(void);
void DMA1_Stream5_IRQHandler(void);
void DMA1_Stream6_IRQHandler(void);
void DMA1_Stream7_IRQHandler(void);

void DMA2_Stream0_IRQHandler(void);
void DMA2_Stream1_IRQHandler(void);
void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream3_IRQHandler(void);
void DMA2_Stream4_IRQHandler(void);
void DMA2_Stream5_IRQHandler(void);
void DMA2_Stream6_IRQHandler(void);
void DMA2_Stream7_IRQHandler(void);


#endif
