################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adxl345_FSM.c \
../Src/main.c 

OBJS += \
./Src/adxl345_FSM.o \
./Src/main.o 

C_DEPS += \
./Src/adxl345_FSM.d \
./Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Inc -I"/mnt/Disco_D/UBA_CESE/CURSOS/03_PdM/GitHub_Cods/PdM_workspace/TrabajoPracticoFinal_PdM/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/mnt/Disco_D/UBA_CESE/CURSOS/03_PdM/GitHub_Cods/PdM_workspace/TrabajoPracticoFinal_PdM/Drivers/CMSIS/Include" -I"/mnt/Disco_D/UBA_CESE/CURSOS/03_PdM/GitHub_Cods/PdM_workspace/TrabajoPracticoFinal_PdM/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/mnt/Disco_D/UBA_CESE/CURSOS/03_PdM/GitHub_Cods/PdM_workspace/TrabajoPracticoFinal_PdM/Drivers/BSP/STM32F4xx_Nucleo_144" -I"/mnt/Disco_D/UBA_CESE/CURSOS/03_PdM/GitHub_Cods/PdM_workspace/TrabajoPracticoFinal_PdM/Drivers/Core/Inc" -I"/mnt/Disco_D/UBA_CESE/CURSOS/03_PdM/GitHub_Cods/PdM_workspace/TrabajoPracticoFinal_PdM/Drivers/API/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adxl345_FSM.d ./Src/adxl345_FSM.o ./Src/adxl345_FSM.su ./Src/main.d ./Src/main.o ./Src/main.su

.PHONY: clean-Src

