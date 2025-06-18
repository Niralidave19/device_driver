/*
 * stm32f446xx.h
 *
 *  Created on: Jun 17, 2025
 *      Author: niral
 */

#ifndef PUBLIC_STM32F446XX_H_
#define PUBLIC_STM32F446XX_H_

#include <stdint.h>
#include"gpio_types.h"


//base peripheral of buses
#define AHB1_BASE_ADDRESS 0x40020000u
#define AHB2_BASE_ADDRESS 0x50000000u

//base address of the GPIO peripherals
//First check which bus are they connected to , tie the base addresses accordingly
#define GPIOA_BASE_ADDRESS AHB1_BASE_ADDRESS + (0x0000)
#define GPIOB_BASE_ADDRESS AHB1_BASE_ADDRESS + (0x0400)

//for each GPIO port, we type-cast it to this type

#define GPIOA (GPIO_Reg_def_t*)GPIOA_BASE_ADDRESS
#define GPIOB (GPIO_Reg_def_t*)GPIOA_BASE_ADDRESS

//RCC Base memory address
#define RCC_BASE_ADDRESS 0x40023800u

//The mode of the register could take the following values
#define GPIO_MODE_IN 	 0
#define GPIO_MODE_OUT    1
#define GPIO_MODE_ALTFUN 2
#define GPIO_MODE_ANALOG 3

//The different pin speeds
#define GPIO_LOW_SPEED 	     0
#define GPIO_MEDIUM_SPEED    1
#define GPIO_HIGH_SPEED      2
#define GPIO_VERY_HIGH_SPEED 3

//I/O Pull up and Pull down
#define GPIO_NO_PULLUP_PULLDOWN 0
#define GPIO_PULL_UP            1
#define GPIO_PULL_DOWN          2
#define GPIO_RESERVED           3

//output type
#define GPIO_PUSH_PIULL 0
#define GPIO_OPEN_DRAIN 1

//GPIO alternate functionality
#define GPIO_AF0 0
#define GPIO_AF1 1
#define GPIO_AF2 2
#define GPIO_AF3 3
#define GPIO_AF4 4
#define GPIO_AF5 5
#define GPIO_AF6 6
#define GPIO_AF7 7
#define GPIO_AF8 8
#define GPIO_AF9 9
#define GPIO_AF10 10
#define GPIO_AF11 11
#define GPIO_AF12 12
#define GPIO_AF13 13
#define GPIO_AF14 14
#define GPIO_AF15 15

//RCC base address type-casted to the type RCC_Reg_def_t
#define RCC ((RCC_Reg_def_t*)RCC_BASE_ADDRESS)
//GPIO A and GPIO B clock bits are in register: RCC_AHB1RSTR : Bit 0 (GPIO A) Bit 1(GPIO B) : Reset value is 0
#define gpioA_clock_enable() RCC->rcc_ahb1rstr = RCC->rcc_ahb1rstr | (1<<0)
#define gpioB_clock_enable() RCC->rcc_ahb1rstr = RCC->rcc_ahb1rstr | (1<<1)

//GPIO A and GPIO B disable the RCC bits
#define gpioA_clock_disable() RCC->rcc_ahb1rstr = ~(RCC->rcc_ahb1rstr & (1<<0))
#define gpioB_clock_disable() RCC->rcc_ahb1rstr = ~(RCC->rcc_ahb1rstr & (1<<1))


#endif /* PUBLIC_STM32F446XX_H_ */
