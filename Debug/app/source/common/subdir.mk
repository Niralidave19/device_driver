################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/source/common/app_request_receive.c 

OBJS += \
./app/source/common/app_request_receive.o 

C_DEPS += \
./app/source/common/app_request_receive.d 


# Each subdirectory must supply rules for building sources it contributes
app/source/common/%.o app/source/common/%.su app/source/common/%.cyclo: ../app/source/common/%.c app/source/common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"C:/Users/niral/STM32CubeIDE/workspace_1.16.0/device_driver/hal/public" -I"C:/Users/niral/STM32CubeIDE/workspace_1.16.0/device_driver/app" -I"C:/Users/niral/STM32CubeIDE/workspace_1.16.0/device_driver/app/public" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-app-2f-source-2f-common

clean-app-2f-source-2f-common:
	-$(RM) ./app/source/common/app_request_receive.cyclo ./app/source/common/app_request_receive.d ./app/source/common/app_request_receive.o ./app/source/common/app_request_receive.su

.PHONY: clean-app-2f-source-2f-common

