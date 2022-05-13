#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Flash.h"


#define FLASH_KEY1			0x45670123
#define FLASH_KEY2			0xCDEF89AB

static void Flash_SetProgramSize(uint32_t ProgramType);

void Flash_Init(void)
{
	FLASH_BASE->FLASH_KEYR = FLASH_KEY1;
	FLASH_BASE->FLASH_KEYR = FLASH_KEY2;
}

void Flash_DeInit(void)
{
	FLASH_BASE->FLASH_CR |= FLASH_CR_LOCK;
}

FlashReturn_t Flash_SectorErase(uint32_t Copy_u8SectorNum)
{
	FlashReturn_t ReturnState = Flash_OK;
	uint8_t CountDown = 50;
	if(Copy_u8SectorNum > 5)
	{
		ReturnState = Flash_NOK;
	}
	else if(FLASH_BASE->FLASH_SR & FLASH_SR_BSY)/*1- Check that no Flash memory operation is going in*/
	{
		ReturnState = Flash_NOK;
	}
	else
	{
		/*2- Set the SER bit and select the sector out of the 5 sectors
		 *3- Set the STRT bit in the FLASH_CR register
		 * */
		uint32_t TempReg = FLASH_BASE->FLASH_CR;
		TempReg &=~ FLASH_CR_SNB;
		TempReg |= (Copy_u8SectorNum << 3 | FLASH_CR_STRT | FLASH_CR_SER);
		FLASH_BASE->FLASH_CR = TempReg;
		while((FLASH_BASE->FLASH_SR & FLASH_SR_BSY) && CountDown)/*4- Wait for the BSY bit to be cleared*/
		{
			--CountDown;
		}
	    if((FLASH_BASE->FLASH_SR & FLASH_SR_BSY) != 0)
		{
			ReturnState = Flash_NOK;
		}
	}
	return ReturnState;
}
static void Flash_SetProgramSize(uint32_t ProgramType)
{
	uint32_t TempReg = FLASH_BASE->FLASH_CR;
	TempReg &=~ FLASH_CR_PSIZE;
	TempReg |= (FLASH_CR_PG|ProgramType);
	FLASH_BASE ->FLASH_CR = TempReg;
}

FlashReturn_t Flash_Program(uint32_t ProgramType,uint32_t Address,uint64_t Data)
{
	FlashReturn_t ReturnState = Flash_OK;
	uint8_t CountDown = 50;
	if(Address < 0x080000000 && Address > 0x0803FFFFU)
	{
		ReturnState = Flash_NOK;
	}
	else if(FLASH_BASE->FLASH_SR & FLASH_SR_BSY)/*1- Check that no Flash memory operation is going in*/
	{
		ReturnState = Flash_NOK;
	}
	else
	{

		switch(ProgramType)
		{
		case FLASH_PROGRAM_SIZE_x8:
			Flash_SetProgramSize(ProgramType);
			*(volatile uint8_t*) Address = (uint8_t)Data;
			break;
		case FLASH_PROGRAM_SIZE_x16:
			Flash_SetProgramSize(ProgramType);
			*(volatile uint16_t*) Address = (uint16_t)Data;
			break;
		case FLASH_PROGRAM_SIZE_x32:
			Flash_SetProgramSize(ProgramType);
			*(volatile uint32_t*) Address = (uint32_t)Data;
			break;
		case FLASH_PROGRAM_SIZE_x64:
			Flash_SetProgramSize(ProgramType);
			*(volatile uint64_t*) Address = (uint64_t)Data;
			break;
		default:
			ReturnState = Flash_NOK;
		}
		while((FLASH_BASE->FLASH_SR & FLASH_SR_BSY) && CountDown)/*4- Wait for the BSY bit to be cleared*/
		{
			--CountDown;
		}
	    if((FLASH_BASE->FLASH_SR & FLASH_SR_BSY) != 0)
		{
			ReturnState = Flash_NOK;
		}
	}
	return ReturnState;
}


