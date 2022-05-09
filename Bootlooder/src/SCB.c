#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "SCB.h"

#define SCB_VTOR 	   				*((volatile uint32_t*)0xE000ED08)
#define SCB_AIRCR 	   				*((volatile uint32_t*)0xE000ED0C)

#define SCB_AIRCR_SYSRESETREQ		(uint32_t)0x4u

#define VECTKEY						(uint32_t)0x5FA0004u
#define VECTKEY_CLEAR				(uint32_t)0xFFFF0000u

void SCB_ChangeINTVECTadd(uint32_t Add)
{
	SCB_VTOR = Add;
}
void SCB_RestSys(void)
{
	SCB_AIRCR = VECTKEY;
	//SCB_AIRCR |= SCB_AIRCR;
}
