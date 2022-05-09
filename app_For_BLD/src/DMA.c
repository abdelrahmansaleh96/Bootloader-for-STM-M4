#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "DMA.h"


static void (*DmaStreamCbf[15]) (void);

DMA_StatusTypeDef DMA_Init(DMAcfg_t* psDMAcfg)
{
	DMA_StatusTypeDef Return_state = DMAOk;
	if(psDMAcfg == NULL)
	{
		Return_state = DMANull_ptr;
	}
	else
	{
		/*---Configuration of DMA_SxCR---*/
		uint32_t TempReg =__STREAM_REG(psDMAcfg -> BaseAddress , psDMAcfg->StreamNum)->DMA_SCR;

		TempReg &=~ DMA_SxCR;/*Clear all configuration */
		/*Set required configuration*/
		TempReg |= psDMAcfg->Channel                 | psDMAcfg->DataTransferDirection | psDMAcfg->MemoryDataSize
				|  psDMAcfg->MemoryIncrementMode     | psDMAcfg->Mode                  | psDMAcfg->PeripheralDataSize
				|  psDMAcfg->PeripheralIncrementMode | psDMAcfg->PriorityLevel         | psDMAcfg->TransferCompleteInterruptEnable;
		__STREAM_REG(psDMAcfg->BaseAddress , psDMAcfg->StreamNum)->DMA_SCR = TempReg;

		((volatile DMA_Base_Registers_t*) (psDMAcfg -> BaseAddress))->DMA_HIFCR=0xffffffff;
		((volatile DMA_Base_Registers_t*) (psDMAcfg -> BaseAddress))->DMA_LIFCR=0xffffffff;
	}
	return Return_state;
}

DMA_StatusTypeDef DMA_Start(DMAcfg_t* psDMAcfg,uint32_t pu32Src,uint32_t pu32Dest,uint32_t DataSize)
{
	DMA_StatusTypeDef Return_state = DMAOk;
	if(psDMAcfg == NULL)
	{
		Return_state = DMANull_ptr;
	}
	else
	{
		/*---Configuration of DMA_SNDTR "Stream Data Length"---*/
		__STREAM_REG(psDMAcfg->BaseAddress , psDMAcfg->StreamNum)->DMA_SNDTR = (uint32_t)(DataSize &(0xffff));
		if(psDMAcfg->DataTransferDirection == DMA_DIRECTION_MEMORY_TO_PERIPHERAL)
		{
			__STREAM_REG(psDMAcfg->BaseAddress , psDMAcfg->StreamNum)->DMA_SM0AR = pu32Src;
			__STREAM_REG(psDMAcfg->BaseAddress , psDMAcfg->StreamNum)->DMA_SPAR  = pu32Dest;
		}
		else if(psDMAcfg->DataTransferDirection == DMA_DIRECTION_PERIPHERAL_TO_MEMORY)
		{
			__STREAM_REG(psDMAcfg->BaseAddress , psDMAcfg->StreamNum)->DMA_SM0AR = pu32Dest;
			__STREAM_REG(psDMAcfg->BaseAddress , psDMAcfg->StreamNum)->DMA_SPAR  = pu32Src;
		}
		__STREAM_REG(psDMAcfg->BaseAddress , psDMAcfg->StreamNum)->DMA_SCR |= DMA_SxCR_EN;
	}
	return Return_state;
}


void DMA_StremRegisterCbf( void (*pfDmaStrCbf) (void) ,StramCbfNum_t num)
{
	if(pfDmaStrCbf != NULL)
	{
		DmaStreamCbf[num] = pfDmaStrCbf;
	}
}


/*---Interrupt Request Handler---*/
void DMA1_Stream0_IRQHandler(void)
{
    if(DmaStreamCbf[DMA1_Stream0Cbf] != NULL)
    {
       (DmaStreamCbf[DMA1_Stream0Cbf])();
    }
}
void DMA1_Stream1_IRQHandler(void)
{
    if(DmaStreamCbf[DMA1_Stream1Cbf] != NULL)
    {
       (DmaStreamCbf[DMA1_Stream1Cbf])();
    }
}
void DMA1_Stream2_IRQHandler(void)
{
    if(DmaStreamCbf[DMA1_Stream2Cbf] != NULL)
    {
       (DmaStreamCbf[DMA1_Stream2Cbf])();
    }
}
void DMA1_Stream3_IRQHandler(void)
{
    if(DmaStreamCbf[DMA1_Stream3Cbf] != NULL)
    {
       (DmaStreamCbf[DMA1_Stream3Cbf])();
    }
}
void DMA1_Stream4_IRQHandler(void)
{
    if(DmaStreamCbf[DMA1_Stream4Cbf] != NULL)
    {
       (DmaStreamCbf[DMA1_Stream4Cbf])();
    }
}
void DMA1_Stream5_IRQHandler(void)
{
    if(DmaStreamCbf[DMA1_Stream5Cbf] != NULL)
    {
       (DmaStreamCbf[DMA1_Stream5Cbf])();
    }
}
void DMA1_Stream6_IRQHandler(void)
{
    if(DmaStreamCbf[DMA1_Stream6Cbf] != NULL)
    {
       (DmaStreamCbf[DMA1_Stream6Cbf])();
    }
}
void DMA1_Stream7_IRQHandler(void)
{
    if(DmaStreamCbf[DMA1_Stream7Cbf] != NULL)
    {
       (DmaStreamCbf[DMA1_Stream7Cbf])();
    }
}

void DMA2_Stream0_IRQHandler(void)
{
    if(DmaStreamCbf[DMA2_Stream0Cbf] != NULL)
    {
       (DmaStreamCbf[DMA2_Stream0Cbf])();
    }
}
void DMA2_Stream1_IRQHandler(void)
{
    if(DmaStreamCbf[DMA2_Stream1Cbf] != NULL)
    {
       (DmaStreamCbf[DMA2_Stream1Cbf])();
    }
}
void DMA2_Stream2_IRQHandler(void)
{
    if(DmaStreamCbf[DMA2_Stream2Cbf] != NULL)
    {
       (DmaStreamCbf[DMA2_Stream2Cbf])();
    }
}
void DMA2_Stream3_IRQHandler(void)
{
    if(DmaStreamCbf[DMA2_Stream3Cbf] != NULL)
    {
       (DmaStreamCbf[DMA2_Stream3Cbf])();
    }
}
void DMA2_Stream4_IRQHandler(void)
{
    if(DmaStreamCbf[DMA2_Stream4Cbf] != NULL)
    {
       (DmaStreamCbf[DMA2_Stream4Cbf])();
    }
}
void DMA2_Stream5_IRQHandler(void)
{
    if(DmaStreamCbf[DMA2_Stream5Cbf] != NULL)
    {
       (DmaStreamCbf[DMA2_Stream5Cbf])();
    }
}
void DMA2_Stream6_IRQHandler(void)
{
    if(DmaStreamCbf[DMA2_Stream6Cbf] != NULL)
    {
       (DmaStreamCbf[DMA2_Stream6Cbf])();
    }
}
void DMA2_Stream7_IRQHandler(void)
{
    if(DmaStreamCbf[DMA2_Stream7Cbf] != NULL)
    {
       (DmaStreamCbf[DMA2_Stream7Cbf])();
    }
}
