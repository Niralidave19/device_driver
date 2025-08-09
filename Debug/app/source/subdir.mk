################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/source/app.c \
../app/source/app_led_blink.c \
../app/source/app_request_receive.c \
../app/source/app_uart_flash.c \
../app/source/app_uart_get_data.c 

OBJS += \
./app/source/app.o \
./app/source/app_led_blink.o \
./app/source/app_request_receive.o \
./app/source/app_uart_flash.o \
./app/source/app_uart_get_data.o 

C_DEPS += \
./app/source/app.d \
./app/source/app_led_blink.d \
./app/source/app_request_receive.d \
./app/source/app_uart_flash.d \
./app/source/app_uart_get_data.d 


# Each subdirectory must supply rules for building sources it contributes
app/source/%.o app/source/%.su app/source/%.cyclo: ../app/source/%.c app/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"C:/Users/niral/STM32CubeIDE/workspace_1.16.0/device_driver/hal/public" -I"C:/Users/niral/STM32CubeIDE/workspace_1.16.0/device_driver/app" -I"C:/Users/niral/STM32CubeIDE/workspace_1.16.0/device_driver/app/public" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-app-2f-source

clean-app-2f-source:
	-$(RM) ./app/source/app.cyclo ./app/source/app.d ./app/source/app.o ./app/source/app.su ./app/source/app_led_blink.cyclo ./app/source/app_led_blink.d ./app/source/app_led_blink.o ./app/source/app_led_blink.su ./app/source/app_request_receive.cyclo ./app/source/app_request_receive.d ./app/source/app_request_receive.o ./app/source/app_request_receive.su ./app/source/app_uart_flash.cyclo ./app/source/app_uart_flash.d ./app/source/app_uart_flash.o ./app/source/app_uart_flash.su ./app/source/app_uart_get_data.cyclo ./app/source/app_uart_get_data.d ./app/source/app_uart_get_data.o ./app/source/app_uart_get_data.su

.PHONY: clean-app-2f-source

