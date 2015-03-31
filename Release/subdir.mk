################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../adc.c \
../irmp.c \
../irmpextlog.c \
../leds.c \
../main.c \
../motorpot.c \
../pga.c \
../receiver.c \
../spi.c 

OBJS += \
./adc.o \
./irmp.o \
./irmpextlog.o \
./leds.o \
./main.o \
./motorpot.o \
./pga.o \
./receiver.o \
./spi.o 

C_DEPS += \
./adc.d \
./irmp.d \
./irmpextlog.d \
./leds.d \
./main.d \
./motorpot.d \
./pga.d \
./receiver.d \
./spi.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega168 -DF_CPU=20000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


