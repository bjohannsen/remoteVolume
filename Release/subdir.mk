################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../adc.c \
../irmp.c \
../irmpextlog.c \
../leds.c \
../motorpot.c \
../pga.c \
../receiver.c \
../relays.c \
../spi.c \
../volumeRemote.c 

OBJS += \
./adc.o \
./irmp.o \
./irmpextlog.o \
./leds.o \
./motorpot.o \
./pga.o \
./receiver.o \
./relays.o \
./spi.o \
./volumeRemote.o 

C_DEPS += \
./adc.d \
./irmp.d \
./irmpextlog.d \
./leds.d \
./motorpot.d \
./pga.d \
./receiver.d \
./relays.d \
./spi.d \
./volumeRemote.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega168 -DF_CPU=20000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


