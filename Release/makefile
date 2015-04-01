################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include src/irmp/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
VolumeRemote.lss \

FLASH_IMAGE += \
VolumeRemote.hex \

EEPROM_IMAGE += \
VolumeRemote.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: VolumeRemote.elf secondary-outputs

# Tool invocations
VolumeRemote.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,VolumeRemote.map -mmcu=atmega168 -o"VolumeRemote.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

VolumeRemote.lss: VolumeRemote.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S VolumeRemote.elf  >"VolumeRemote.lss"
	@echo 'Finished building: $@'
	@echo ' '

VolumeRemote.hex: VolumeRemote.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex VolumeRemote.elf  "VolumeRemote.hex"
	@echo 'Finished building: $@'
	@echo ' '

VolumeRemote.eep: VolumeRemote.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex VolumeRemote.elf  "VolumeRemote.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: VolumeRemote.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega168 VolumeRemote.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) VolumeRemote.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
