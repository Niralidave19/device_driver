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

void GPIO_Clock(GPIO_Reg_def_t *pGPIOx, uint8_t enordis, gpio_port_def_t GPIO_ID){
	/*enable the clock on the port*/
	if(enordis == 1){
		switch (GPIO_ID){
		case GPIO_ID_A:
			GPIOA_clock_enable();
		case GPIO_ID_B:
			GPIOB_clock_enable();
		}
	}
	else if(enordis == 0){
		switch (GPIO_ID){
		case GPIO_ID_A:
			GPIOA_clock_enable();
		case GPIO_ID_B:
			GPIOB_clock_enable();
		}
	}
}

/* Function to get the base address of GPIO port configured*/
volatile GPIO_Reg_def_t* GPIO_GetPort(gpio_port_def_t GPIO_ID){
	switch (GPIO_ID){
	case GPIO_ID_A:
		return (volatile GPIO_Reg_def_t*)GPIOA_BASE_ADDRESS;
	case GPIO_ID_B:
		return (volatile GPIO_Reg_def_t*)GPIOB_BASE_ADDRESS;
	}
}

/*To initialize the GPIO Port */
void GPIO_Init(gpio_port_def_t GPIO_ID, uint8_t GPIO_PinNumber,uint8_t GPIO_PinMode,
			   uint8_t GPIO_PinSpeed, uint8_t GPIO_pullup_down_control, uint8_t GPIO_PinOpType,
		       uint8_t GPIO_AltFunMode){
	uint32_t temp = 0;
	/* Get the GPIO register for the GPIO_ID */
	volatile GPIO_Reg_def_t *pGPIOx = GPIO_GetPort(GPIO_ID);

	/*Set the mode of the GPIO Pin - MODER REGISTER*/
	temp = temp | (GPIO_PinMode << (GPIO_PinNumber *2));
	pGPIOx->gpio_moder = ~(pGPIOx->gpio_moder | (3<<(GPIO_PinNumber * 2)));
	pGPIOx->gpio_moder = pGPIOx->gpio_moder | temp;


	/*set the output speed of the pin*/
	temp = 0;
	temp = temp | (GPIO_PinSpeed << (GPIO_PinNumber *2));
	pGPIOx->gpio_ospeedr = ~(pGPIOx->gpio_ospeedr | (3<<(GPIO_PinNumber * 2)));
	pGPIOx->gpio_ospeedr = pGPIOx->gpio_ospeedr | temp;

	/* Set if the pin needs to be treated as a pull up/pull down pin -
	 * Usually used when pin is in input mode */
	temp = 0;
	temp = temp | (GPIO_pullup_down_control << (GPIO_PinNumber *2));
	pGPIOx->gpio_pupdr = ~(pGPIOx->gpio_pupdr | (3<<(GPIO_PinNumber * 2)));
	pGPIOx->gpio_pupdr = pGPIOx->gpio_pupdr | temp;

	/*set output type register*/
	temp = 0;
	temp = temp | (GPIO_PinOpType << (GPIO_PinNumber *2));
	pGPIOx->gpio_otyper = ~(pGPIOx->gpio_otyper | (1<<(GPIO_PinNumber)));
	pGPIOx->gpio_otyper = pGPIOx->gpio_otyper | temp;

	/*set alternate functionality mode register*/
	if(GPIO_PinNumber <= 7){
		//configure alternate functionality low register
		temp = 0;
		temp = temp | (GPIO_AltFunMode << (GPIO_PinNumber *4));
		pGPIOx->gpio_aflr = ~(pGPIOx->gpio_aflr | (15<<(GPIO_PinNumber)));
		pGPIOx->gpio_aflr = pGPIOx->gpio_aflr | temp;
	}
	else if(GPIO_PinNumber > 7){
		//configure alternate functionality High register
		temp = 0;
		temp = temp | (GPIO_AltFunMode << (GPIO_PinNumber *4));
		pGPIOx->gpio_afrh = ~(pGPIOx->gpio_afrh | (15<<(GPIO_PinNumber)));
		pGPIOx->gpio_afrh = pGPIOx->gpio_afrh | temp;
	}
}
/*
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
*/
uint8_t GPIO_ReadfromInput_pin(GPIO_Reg_def_t *pGPIOx,uint8_t GPIO_PinNumber){
	uint8_t temp=0;
	temp = ((pGPIOx->gpio_idr)>>(GPIO_PinNumber))&0x00000001;
	return temp;
}
