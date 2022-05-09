#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "NVIC.h"
#include "NVIC_cfg.h"





typedef struct
{
	uint32_t NVIC_ISER[8];
	uint32_t res0[24];
	uint32_t NVIC_ICER[8];
	uint32_t res1[24];
	uint32_t NVIC_ISPR[8];
	uint32_t res2[24];
	uint32_t NVIC_ICPR[8];
	uint32_t res3[24];
	uint32_t NVIC_IABR[8];
	uint32_t res4[56];
	uint32_t NVIC_IPR[60];
}NVICReg_t;

/*--RCC base address---*/
#define NVIC_BASE		                ((volatile NVICReg_t *) 0xE000E100u)
#define ONE_BIT_MASK					1u

#define EIGHT_BIT_MASK					0xffu


/******************************************************************************
** Function:    NVIC_EnableIRQ
** Description: Enables an interrupt or exception
** Parameter: 	IRQn
** Return:      NVIC_tenumErrorStatus
******************************************************************************/

NVIC_tenumErrorStatus NVIC_vidEnableIRQ(IRQ_t Copy_IRQ)
{
	NVIC_tenumErrorStatus Loc_ErrorStatus = NVIC_enumOK;
	if(Copy_IRQ>240)
	{
		Loc_ErrorStatus =NVIC_enumIRQnumerror;
	}
	else
	{
		NVIC_BASE->NVIC_ISER[Copy_IRQ/32] = ONE_BIT_MASK<<(Copy_IRQ%32);
	}

	return Loc_ErrorStatus;
}


/******************************************************************************
** Function:    NVIC_vidDisableIRQ
** Description: Disables an interrupt or exception
** Parameter: 	Copy_IRQ
** Return:      NVIC_tenumErrorStatus
******************************************************************************/
NVIC_tenumErrorStatus NVIC_vidDisableIRQ(IRQ_t Copy_IRQ)
{
	NVIC_tenumErrorStatus Loc_ErrorStatus = NVIC_enumOK;
	if(Copy_IRQ>240)
	{
		Loc_ErrorStatus =NVIC_enumIRQnumerror;
	}
	else
	{
		NVIC_BASE->NVIC_ICER[Copy_IRQ/32] = ONE_BIT_MASK<<(Copy_IRQ%32);
	}
	return Loc_ErrorStatus;
}


/******************************************************************************
** Function:    NVIC_vidSetPendingIRQ
** Description: Sets the pending status of interrupt or exception to 1
** Parameter: 	Copy_IRQ
** Return:      NVIC_tenumErrorStatus
******************************************************************************/
NVIC_tenumErrorStatus NVIC_vidSetPendingIRQ(IRQ_t Copy_IRQ)
{
	NVIC_tenumErrorStatus Loc_ErrorStatus = NVIC_enumOK;
	if(Copy_IRQ>240)
	{
		Loc_ErrorStatus =NVIC_enumIRQnumerror;
	}
	else
	{
		NVIC_BASE->NVIC_ISPR[Copy_IRQ/32] = ONE_BIT_MASK<<(Copy_IRQ%32);
	}
	return Loc_ErrorStatus;
}

/******************************************************************************
** Function:    NVIC_vidClearPendingIRQ
** Description: Clears the pending status of interrupt or exception to 0
** Parameter: 	Copy_IRQ
** Return:      NVIC_tenumErrorStatus
******************************************************************************/
NVIC_tenumErrorStatus NVIC_vidClearPendingIRQ(IRQ_t Copy_IRQ)
{
	NVIC_tenumErrorStatus Loc_ErrorStatus = NVIC_enumOK;
	if(Copy_IRQ>240)
	{
		Loc_ErrorStatus =NVIC_enumIRQnumerror;
	}
	else
	{
		NVIC_BASE->NVIC_ICPR[Copy_IRQ/32] = ONE_BIT_MASK<<(Copy_IRQ%32);
	}
	return Loc_ErrorStatus;
}

/******************************************************************************
** Function:    NVIC_u32GetPendingIRQ
** Description: Reads the pending status of interrupt or exception.
** 				This function put nonzero value  in Add_PendingStatus if the pending status is set to 1.
** Parameter: 	Copy_IRQ,Add_PendingStatus
** Return:      NVIC_tenumErrorStatus
******************************************************************************/
NVIC_tenumErrorStatus NVIC_u32GetPendingIRQ(IRQ_t Copy_IRQ ,uint32_t*  Add_PendingStatus)
{
	NVIC_tenumErrorStatus Loc_ErrorStatus = NVIC_enumOK;
	if(Copy_IRQ>240)
	{
		Loc_ErrorStatus = NVIC_enumIRQnumerror;
	}
	else if(Add_PendingStatus == NULL)
	{
		Loc_ErrorStatus = NVIC_enumNULLPtrerror;
	}
	else
	{
		*Add_PendingStatus = NVIC_BASE->NVIC_ISPR[Copy_IRQ/32] & ONE_BIT_MASK<<(Copy_IRQ%32);
	}
	return Loc_ErrorStatus;
}

/******************************************************************************
** Function:    NVIC_u32GetPendingIRQ
** Description: Sets the priority of an interrupt or exception with configurable priority level to 1
** Parameter: 	Copy_IRQ,Add_PendingStatus
** Return:      NVIC_tenumErrorStatus
******************************************************************************/
NVIC_tenumErrorStatus NVIC_vidSetPriority(IRQ_t Copy_IRQ, uint32_t priority)
{
	NVIC_tenumErrorStatus Loc_ErrorStatus = NVIC_enumOK;
	uint32_t Loc_IPRTemp;
	if(Copy_IRQ>240)
	{
		Loc_ErrorStatus = NVIC_enumIRQnumerror;
	}
	else if( priority > NVIC_LEVEL15)
	{
		Loc_ErrorStatus = NVIC_enumPeriortyerror;
	}
	else
	{
		Loc_IPRTemp = NVIC_BASE->NVIC_IPR[Copy_IRQ/4];
		/*Clear Priority*/
	    Loc_IPRTemp &=~ (EIGHT_BIT_MASK<<(Copy_IRQ%4)*8);
		/*Set Priority*/
	    Loc_IPRTemp |= (priority<<(Copy_IRQ%4)*8);
		NVIC_BASE->NVIC_IPR[Copy_IRQ/4] = Loc_IPRTemp;
	}
	return Loc_ErrorStatus;
}





