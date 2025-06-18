/*
 * gpio_driver.c
 *
 *  Created on: Jun 17, 2025
 *      Author: niral
 */

#include"stm32f446xx.h"
#include<stdint.h>
#include"gpio_types.h"

#ifndef GPIO_PROTO_H_
#define GPIO_PROTO_H_
#endif

void GPIO_Clock(GPIO_Reg_def_t *pGPIOx, uint8_t enordis)
{
	//enable the clock on the port
	if(enordis == 1)
	{
		if(pGPIOx == GPIOA)
		{
			gpioA_clock_enable();
		}
		if(pGPIOx == GPIOA)
		{
			gpioB_clock_enable();
		}
	}
	else if(enordis == 0)
	{
		if(pGPIOx == GPIOA)
		{
			gpioA_clock_disable();
		}
		if(pGPIOx == GPIOB)
		{
			gpioB_clock_disable();
		}
	}
}

void GPIO_Init(GPIO_Reg_def_t *pGPIOx, uint8_t GPIO_PinNumber,uint8_t GPIO_PinMode,
			   uint8_t GPIO_PinSpeed, uint8_t GPIO_pullup_down_control, uint8_t GPIO_PinOpType,
		       uint8_t GPIO_AltFunMode)
{
	uint32_t temp = 0;
	//set input mode
	//set the mode of ith pin of GPIO Port A - MODER REGISTER
	temp = temp | (GPIO_PinMode << (GPIO_PinNumber *2));
	//clear the current bits in register
	pGPIOx->gpio_moder = ~(pGPIOx->gpio_moder | (3<<(GPIO_PinNumber * 2)));
	pGPIOx->gpio_moder = pGPIOx->gpio_moder | temp;

	//set pin-speed for pit number 1 and pin number 2
	temp = 0;
	//set the mode of ith pin of GPIO Port A - output speed REGISTER
	temp = temp | (GPIO_PinSpeed << (GPIO_PinNumber *2));
	//clear the current bits in register
	pGPIOx->gpio_ospeedr = ~(pGPIOx->gpio_ospeedr | (3<<(GPIO_PinNumber * 2)));
	pGPIOx->gpio_ospeedr = pGPIOx->gpio_ospeedr | temp;

	//set pull up and pull down controller
	temp = 0;
	temp = temp | (GPIO_pullup_down_control << (GPIO_PinNumber *2));
	pGPIOx->gpio_pupdr = ~(pGPIOx->gpio_pupdr | (3<<(GPIO_PinNumber * 2)));
	pGPIOx->gpio_pupdr = pGPIOx->gpio_pupdr | temp;

	//set output type register
	temp = 0;
	temp = temp | (GPIO_PinOpType << (GPIO_PinNumber *2));
	pGPIOx->gpio_otyper = ~(pGPIOx->gpio_otyper | (1<<(GPIO_PinNumber)));
	pGPIOx->gpio_otyper = pGPIOx->gpio_otyper | temp;

	//set alternate functionality mode register
	if(GPIO_PinNumber <= 7)
	{
		//configure alternate functionality low register
		temp = 0;
		temp = temp | (GPIO_AltFunMode << (GPIO_PinNumber *4));
		pGPIOx->gpio_aflr = ~(pGPIOx->gpio_aflr | (15<<(GPIO_PinNumber)));
		pGPIOx->gpio_aflr = pGPIOx->gpio_aflr | temp;
	}
	else if(GPIO_PinNumber > 7)
	{
		//configure alternate functionality High register
		temp = 0;
		temp = temp | (GPIO_AltFunMode << (GPIO_PinNumber *4));
		pGPIOx->gpio_afrh = ~(pGPIOx->gpio_afrh | (15<<(GPIO_PinNumber)));
		pGPIOx->gpio_afrh = pGPIOx->gpio_afrh | temp;
	}
}
void GPIO_Deinit(GPIO_Reg_def_t *pGPIO)
{
	if(pGPIO == GPIOA)
	{
		//de-init GPIO A
		gpioA_clock_disable();
	}
	if(pGPIO == GPIOB)
	{
		//de-init GPIO B
		gpioB_clock_disable();
	}
}

uint8_t GPIO_ReadfromInput_pin(GPIO_Reg_def_t *pGPIOx,uint8_t GPIO_PinNumber)
{
	uint8_t temp=0;
	temp = ((pGPIOx->gpio_idr)>>(GPIO_PinNumber))&0x00000001;
	return temp;
}
