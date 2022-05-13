#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Flash.h"
#include "BLD_Manger.h"
#include "SCB.h"
#include "RCC.h"





typedef void (*Notify_t)(void);


int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	trace_printf("REstart\n");
	if((APP_INFO->AppEntryPoint) == 0xffffffff)
	{
		trace_printf("Enter Flashing Sec\n");
		Flash_Init();
		BLDManger_UartInit();
		while(1)
		{
			BLDManger_FlashingTask();
		}

	}
	else
	{

		trace_printf("Run APP\n");
		Notify_t App = (Notify_t)(APP_INFO->AppEntryPoint);
		SCB_ChangeINTVECTadd(APP_INFO->AppFirstAdd);
		if(App != NULL)
		{
			App();
		}
	}
	return 0;
}
