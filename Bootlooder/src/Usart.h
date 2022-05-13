#ifndef USART_H_
#define USART_H_

#include "DMA.h"
typedef enum
{
	Ok,
	Not_Ok,
	Null_ptr,
	uartbusy,
}UART_StatusTypeDef;

typedef enum
{
	busy,
	ready
}UartStatus_t;

typedef struct
{
	void*  			Channel_BaseAdress;
	uint32_t  		Mode;
	uint32_t  		WordLength;
	uint32_t  		Stop_bits;
	uint32_t  		Parity;
	uint32_t  		BaudRate;
	uint32_t  		Tx_Size;
	uint32_t  		Rx_Size;
	uint32_t		TxIndex;
	uint32_t		RxIndex;
	uint8_t*  		Tx_Buffer;
	uint8_t*  		Rx_Buffer;
	UartStatus_t	state;
	uint8_t			res2;
	uint8_t			res3;
	uint8_t			res1;
}USARTHandel_t;



typedef void (*Notify_t)(void);


#define USART6  				 	(void*)0x40011400u
#define USART2					 	(void*)0x40004400u
#define USART1  				 	(void*)0x40011000u

/*----- Bit definition for USART_CR1 register -----*/
#define USART_CR1_SBK				0x00000001u
#define USART_CR1_RWU               0x00000002u
#define USART_CR1_RE                0x00000004u
#define USART_CR1_TE                0x00000008u
#define USART_CR1_IDLEIE            0x00000010u
#define USART_CR1_RXNEIE            0x00000020u
#define USART_CR1_TCIE              0x00000040u
#define USART_CR1_TXEIE             0x00000080u
#define USART_CR1_PEIE              0x00000100u
#define USART_CR1_PS                0x00000200u
#define USART_CR1_PCE               0x00000400u
#define USART_CR1_WAKE              0x00000800u
#define USART_CR1_M                 0x00001000u
#define USART_CR1_UE                0x00002000u
#define USART_CR1_OVER8             0x00008000u


/*-------Bit definition for USART_CR2 register----------------------------------------*/
#define USART_CR2_STOP0				0x00001000u
#define USART_CR2_STOP1				0x00002000u
#define USART_CR2_CLKEN				0x00000800u


/*-------Bit definition for USART_CR3 register----------------------------------------*/
#define USART_CR3_DMAT 			    0x00000080u



/*-------Bit definition for USART_SR register----------------------------------------*/
#define USART_SR_TC					0x00000040u
#define USART_SR_RXNE				(uint32_t)0x20u



/*-------------------Mode---------------------------*/
#define MODE_TX						(uint32_t)USART_CR1_TE
#define MODE_RX						(uint32_t)USART_CR1_RE
#define MODE_TX_RX					(uint32_t)(USART_CR1_TE|USART_CR1_RE)

/*--------------------WordLength--------------------*/
#define WORD_LENGHT_8B				(uint32_t)0x0u
#define WORD_LENGHT_9B				USART_CR1_M
/*-------------------Stop_bits----------------------*/
#define STOP_BITS_ONE				0x0u
#define STOP_BITS_TOW				USART_CR2_STOP1
/*-------------------Parity-------------------------*/
#define PARITY_DISABLE				(uint32_t)0x0u



UART_StatusTypeDef Uart_Init(USARTHandel_t * Add_uart);
UART_StatusTypeDef Uart_RegisterCpfTxComplet(USARTHandel_t* Add_uart , Notify_t Add_Cpf);
UART_StatusTypeDef Uart_SendBufferZeroCopy(USARTHandel_t* Add_uart , uint8_t * Ptr_Buff,uint32_t Size);
UART_StatusTypeDef Uart_SendBufferDMA(USARTHandel_t* Add_uart ,DMAcfg_t* psDMAcfg ,uint32_t  Ptr_Buff,uint32_t Size);
UART_StatusTypeDef Uart_RXBuffer(USARTHandel_t* Add_uart , uint8_t * Ptr_Buff,uint32_t Size);
UART_StatusTypeDef Uart_RegisterCpfRxComplet(USARTHandel_t* Add_uart , Notify_t Add_Cpf);
UART_StatusTypeDef Uart_SendByte(USARTHandel_t* Add_uart , uint8_t Data);
UART_StatusTypeDef Uart_RxByte(USARTHandel_t* Add_uart , uint8_t* Data);
void USART1_IRQHandler(void);

#endif
