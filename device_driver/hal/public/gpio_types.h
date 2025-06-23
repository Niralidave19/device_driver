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

/* GPIO Ports available */
typedef enum
{
	GPIO_ID_A,
	GPIO_ID_B,
	GPIO_ID_C,
	GPIO_ID_D,
	GPIO_ID_E,
	GPIO_ID_F,
	GPIO_ID_G,
	GPIO_ID_H
}gpio_port_def_t;

/*Enable/disable to clock */
typedef enum
{
	GPIO_ENABLE,
	GPIO_DISABLE
}gpio_enable_t;
/* GPIO Port mode register */
typedef enum
{
	GPIO_MODE_IN,
	GPIO_MODE_OUT,
	GPIO_MODE_ALTFUN,
	GPIO_MODE_ANALOG
}gpio_moder_t;

/* GPIO Output type register */
typedef enum
{
	GPIO_OP_PUSH_PULL,
	GPIO_OP_OPEN_DRAIN
}gpio_otyper_t;

/* GPIO port output speed register */
typedef enum
{
	GPIO_LOW_SPEED,
	GPIO_MEDIUM_SPEED,
	GPIO_HIGH_SPEED,
	GPIO_VERY_HIGH_SPEED
}gpio_ospeedr_t;

/*GPIO Pull-up and Pull-down register */
typedef enum
{
	GPIO_NO_PULLUP_PULLDOWN,
	GPIO_PULL_UP,
	GPIO_PULL_DOWN,
	GPIO_RESERVED
}gpio_pupdr_t;

/* GPIO Alternate functionality register*/
typedef enum
{
	GPIO_AF0,
	GPIO_AF1,
	GPIO_AF2,
	GPIO_AF3,
	GPIO_AF4,
	GPIO_AF5,
	GPIO_AF6,
	GPIO_AF7,
	GPIO_AF8,
	GPIO_AF9,
	GPIO_AF10,
	GPIO_AF11,
	GPIO_AF12,
	GPIO_AF13,
	GPIO_AF14,
	GPIO_AF15
}gpio_alt_func_t;

typedef struct {
	gpio_port_def_t  port_id;
	gpio_moder_t     mode;
	gpio_otyper_t    op_type;
	gpio_ospeedr_t   op_speed;
	gpio_pupdr_t     push_pull;
	gpio_alt_func_t  alt_func;
	gpio_enable_t    enable;
	uint8_t          pin_number;
}gpio_config_t;

#endif /* PUBLIC_GPIO_TYPES_H_ */
