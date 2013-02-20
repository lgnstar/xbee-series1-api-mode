################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
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
tip_up_detector.lss \

FLASH_IMAGE += \
tip_up_detector.hex \

EEPROM_IMAGE += \
tip_up_detector.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: tip_up_detector.elf secondary-outputs

# Tool invocations
tip_up_detector.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,tip_up_detector.map -mmcu=attiny2313 -o "tip_up_detector.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

tip_up_detector.lss: tip_up_detector.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S tip_up_detector.elf  >"tip_up_detector.lss"
	@echo 'Finished building: $@'
	@echo ' '

tip_up_detector.hex: tip_up_detector.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex tip_up_detector.elf  "tip_up_detector.hex"
	@echo 'Finished building: $@'
	@echo ' '

tip_up_detector.eep: tip_up_detector.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex tip_up_detector.elf  "tip_up_detector.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: tip_up_detector.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny2313 tip_up_detector.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) tip_up_detector.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
