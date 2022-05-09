#ifndef FLASH_H_
#define FLASH_H_



typedef struct
{
	volatile uint32_t FLASH_ACR;
	volatile uint32_t FLASH_KEYR;
	volatile uint32_t FLASH_OPTKEYR;
	volatile uint32_t FLASH_SR;
	volatile uint32_t FLASH_CR;
	volatile uint32_t FLASH_OPTCR;
}FlashReg_t;

#define  FLASH_BASE  		((volatile FlashReg_t*) (0x40023C00))


/*---Bits definition for FLASH_SR register---*/
#define FLASH_SR_EOP					(uint32_t)0x1u
#define FLASH_SR_OPERR                  (uint32_t)0x2u
#define FLASH_SR_WRPERR                 (uint32_t)0x10u
#define FLASH_SR_PGAERR                 (uint32_t)0x20u
#define FLASH_SR_PGPERR                 (uint32_t)0x40u
#define FLASH_SR_PGSERR                 (uint32_t)0x80u
#define FLASH_SR_RDERR                  (uint32_t)0x100u
#define FLASH_SR_BSY                    (uint32_t)0x10000u

/*---Bits definition for FLASH_CR register---*/
#define FLASH_CR_PG					    (uint32_t)0x1u
#define FLASH_CR_SER                    (uint32_t)0x2u
#define FLASH_CR_MER					(uint32_t)0x4u
#define FLASH_CR_SNB0                   (uint32_t)0x8u
#define FLASH_CR_SNB1                   (uint32_t)0x10u
#define FLASH_CR_SNB2                   (uint32_t)0x20u
#define FLASH_CR_SNB3                   (uint32_t)0x40u
#define FLASH_CR_SNB                    (uint32_t)0x78u
#define FLASH_CR_PSIZE0                 (uint32_t)0x100u
#define FLASH_CR_PSIZE1                 (uint32_t)0x200u
#define FLASH_CR_PSIZE                  (uint32_t)0x300u
#define FLASH_CR_STRT                   (uint32_t)0x10000u
#define FLASH_CR_EOPIE                  (uint32_t)0x1000000u
#define FLASH_CR_ERRIE                  (uint32_t)0x2000000u
#define FLASH_CR_LOCK                   (uint32_t)0x80000000u


/*---DMA PriorityLevel Selection---*/
#define FLASH_PROGRAM_SIZE_x8						(uint32_t)0x0u
#define FLASH_PROGRAM_SIZE_x16					    FLASH_CR_PSIZE0
#define FLASH_PROGRAM_SIZE_x32	  					FLASH_CR_PSIZE1
#define FLASH_PROGRAM_SIZE_x64				    	(FLASH_CR_PSIZE0|FLASH_CR_PSIZE1)


typedef enum
{
	Flash_OK,
	Flash_NOK
}FlashReturn_t;

extern void Flash_Init(void);
extern void Flash_DeInit(void);


extern FlashReturn_t Flash_SectorErase(uint32_t Copy_u8SectorNum);
extern FlashReturn_t Flash_Program(uint32_t ProgramType,uint32_t Address,uint64_t Data);


#endif
