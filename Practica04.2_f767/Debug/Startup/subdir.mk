################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f767zitx.s 

OBJS += \
./Startup/startup_stm32f767zitx.o 

S_DEPS += \
./Startup/startup_stm32f767zitx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -I"/mnt/Disco_D/UBA_CESE/CURSOS/03_PdM/GitHub_Cods/PdM_workspace/Practica04.2_f767/Drivers/BSP/STM32F7xx_Nucleo_144" -I"/mnt/Disco_D/UBA_CESE/CURSOS/03_PdM/GitHub_Cods/PdM_workspace/Practica04.2_f767/Drivers/API/Inc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32f767zitx.d ./Startup/startup_stm32f767zitx.o

.PHONY: clean-Startup

