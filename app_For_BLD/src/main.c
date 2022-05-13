#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "RCC.h"
#include "GPIO.h"
#include "BLD_Manger.h"
#include "Flash.h"

//static uint8_t BuffRecived = 0;
int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;
	Flash_Init();
	BLDManger_UartInit();
	GpioPincfg_t stpin;
	stpin.port = GPIOA;
	stpin.pin = 0;
	stpin.mode = MODE_OUTPUT_PUSH_PULL;
	stpin.speed = SPEED_LOW;
	RCC_EnablePriphralCLK(RCC_AHB1ENR_GPIOAEN);
	Gpio_enuinitPinCfg(&stpin);
	Gpio_enuSetPintValue(GPIOA, 0,1);
	trace_printf("Hello from App\n");




    while(1)
    {

    }
}

