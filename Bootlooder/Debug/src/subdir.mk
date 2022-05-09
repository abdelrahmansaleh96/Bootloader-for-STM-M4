################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BLD_Manager.c \
../src/DMA.c \
../src/Flash.c \
../src/GPIO.c \
../src/NVIC.c \
../src/RCC.c \
../src/SCB.c \
../src/Usart.c \
../src/main.c 

OBJS += \
./src/BLD_Manager.o \
./src/DMA.o \
./src/Flash.o \
./src/GPIO.o \
./src/NVIC.o \
./src/RCC.o \
./src/SCB.o \
./src/Usart.o \
./src/main.o 

C_DEPS += \
./src/BLD_Manager.d \
./src/DMA.d \
./src/Flash.d \
./src/GPIO.d \
./src/NVIC.d \
./src/RCC.d \
./src/SCB.d \
./src/Usart.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Werror -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -Wmissing-prototypes -Wstrict-prototypes -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


