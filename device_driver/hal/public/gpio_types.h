/*
 * gpio_types.h
 *
 *  Created on: Jun 17, 2025
 *      Author: niral
 */

#ifndef PUBLIC_GPIO_TYPES_H_
#define PUBLIC_GPIO_TYPES_H_

#include <stdint.h>
//each GPIO port will have these registers (10)
typedef struct
{
	uint32_t gpio_moder;
	uint32_t gpio_otyper;
	uint32_t gpio_ospeedr;
	uint32_t gpio_pupdr;
	uint32_t gpio_idr;
	uint32_t gpio_odr;
	uint32_t gpio_bsrr;
	uint32_t gpio_lckr;
	uint32_t gpio_aflr;
	uint32_t gpio_afrh;
}GPIO_Reg_def_t;

//The RCC peripheral has a set of registers
typedef struct
{
	uint32_t rcc_cr;
	uint32_t rcc_pllcfgr;
	uint32_t rcc_cfgr;
	uint32_t rcc_cir;
	uint32_t rcc_ahb1rstr;
	uint32_t rcc_ahb2rstr;
	uint32_t rcc_ahb3rstr;
	uint32_t rcc_apb1rstr;
	uint32_t rcc_apb2rstr;
	uint32_t rcc_ahb1enr;
	uint32_t rcc_ahb2enr;
	uint32_t rcc_ahb3enr;
	uint32_t rcc_apb1enr;
	uint32_t rcc_apb2enr;
	uint32_t rcc_ahb1lpenr;
	uint32_t rcc_ahb2lpenr;
	uint32_t rcc_ahb3lpenr;
	uint32_t rcc_apb1lpenr;
	uint32_t rcc_apb2lpenr;
	uint32_t rcc_bdcr;
	uint32_t rcc_csr;
	uint32_t rcc_sscgr;
	uint32_t rcc_plli2scfgr;
	uint32_t rcc_pllsaicfgr;
	uint32_t rcc_dckcfgr;
	uint32_t rcc_ckgatenr;
	uint32_t rcc_dckcfgr2;
}RCC_Reg_def_t;

#endif /* PUBLIC_GPIO_TYPES_H_ */
