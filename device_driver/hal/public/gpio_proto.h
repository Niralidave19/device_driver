/*
 * gpio_proto.h
 *
 *  Created on: Jun 17, 2025
 *      Author: niral
 */

#ifndef PUBLIC_GPIO_PROTO_H_
#define PUBLIC_GPIO_PROTO_H_


#include<stdint.h>
#include"gpio_types.h"

void GPIO_Clock(GPIO_Reg_def_t *pGPIOx, uint8_t enordis);
void GPIO_Init(GPIO_Reg_def_t *pGPIOx, uint8_t GPIO_PinNumber,uint8_t GPIO_PinMode,
			   uint_8 GPIO_PinSpeed, uint8_t GPIO_pullup_down_control, uint8_t GPIO_PinOpType,
		       uint_8 GPIO_AltFunMode);
uint8_t GPIO_ReadfromInput_pin(GPIO_Reg_def_t *pGPIOx,uint8_t GPIO_PinNumber);



#endif /* PUBLIC_GPIO_PROTO_H_ */
