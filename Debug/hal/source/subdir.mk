################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/source/flash.c \
../hal/source/gpio_driver.c \
../hal/source/uart2_driver.c 

OBJS += \
./hal/source/flash.o \
./hal/source/gpio_driver.o \
./hal/source/uart2_driver.o 

C_DEPS += \
./hal/source/flash.d \
./hal/source/gpio_driver.d \
./hal/source/uart2_driver.d 


# Each subdirectory must supply rules for building sources it contributes
hal/source/%.o hal/source/%.su hal/source/%.cyclo: ../hal/source/%.c hal/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"C:/Users/niral/STM32CubeIDE/workspace_1.16.0/device_driver/hal/public" -I"C:/Users/niral/STM32CubeIDE/workspace_1.16.0/device_driver/app" -I"C:/Users/niral/STM32CubeIDE/workspace_1.16.0/device_driver/app/public" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-hal-2f-source

clean-hal-2f-source:
	-$(RM) ./hal/source/flash.cyclo ./hal/source/flash.d ./hal/source/flash.o ./hal/source/flash.su ./hal/source/gpio_driver.cyclo ./hal/source/gpio_driver.d ./hal/source/gpio_driver.o ./hal/source/gpio_driver.su ./hal/source/uart2_driver.cyclo ./hal/source/uart2_driver.d ./hal/source/uart2_driver.o ./hal/source/uart2_driver.su

.PHONY: clean-hal-2f-source

