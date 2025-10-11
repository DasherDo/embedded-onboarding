/**
  ******************************************************************************
  * @file    stm32f0xx_hal_gpio.c
  * @author  MCD Application Team
  * @brief   GPIO HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the General Purpose Input/Output (GPIO)
  peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
					##### GPIO Peripheral features #####
  ==============================================================================
  [..]
	(+) Each port bit of the general-purpose I/O (GPIO) ports can be
  individually configured by software in several modes:
		(++) Input mode
		(++) Analog mode
		(++) Output mode
		(++) Alternate function mode
		(++) External interrupt/event lines

	(+) During and just after reset, the alternate functions and external
  interrupt lines are not active and the I/O ports are configured in input
  floating mode.

	(+) All GPIO pins have weak internal pull-up and pull-down resistors, which
  can be activated or not.

	(+) In Output or Alternate mode, each IO can be configured on open-drain or
  push-pull type and the IO speed can be selected depending on the VDD value.

	(+) The microcontroller IO pins are connected to onboard peripherals/modules
  through a multiplexer that allows only one peripheral alternate function (AF)
  connected to an IO pin at a time. In this way, there can be no conflict
  between peripherals sharing the same IO pin.

	(+) All ports have external interrupt/event capability. To use external
  interrupt lines, the port must be configured in input mode. All available GPIO
  pins are connected to the 16 external interrupt/event lines from EXTI0 to
  EXTI15.

	(+) The external interrupt/event controller consists of up to 28 edge
  detectors (16 lines are connected to GPIO) for generating event/interrupt
  requests (each input line can be independently configured to select the type
  (interrupt or event) and the corresponding trigger event (rising or falling or
  both). Each line can also be masked independently.

			##### How to use this driver #####
  ==============================================================================
  [..]
   (#) Enable the GPIO AHB clock using the following function :
  __HAL_RCC_GPIOx_CLK_ENABLE().

   (#) Configure the GPIO pin(s) using HAL_GPIO_Init().
	   (++) Configure the IO mode using "Mode" member from GPIO_InitTypeDef
  structure
	   (++) Activate Pull-up, Pull-down resistor using "Pull" member from
  GPIO_InitTypeDef structure.
	   (++) In case of Output or alternate function mode selection: the speed is
			 configured through "Speed" member from GPIO_InitTypeDef structure.
		(++) In alternate mode is selection, the alternate function connected to
  the IO is configured through "Alternate" member from GPIO_InitTypeDef
  structure.
	   (++) Analog mode is required when a pin is to be used as ADC channel
			or DAC output.
	   (++) In case of external interrupt/event selection the "Mode" member from
			GPIO_InitTypeDef structure select the type (interrupt or event) and
			the corresponding trigger event (rising or falling or both).

   (#) In case of external interrupt/event mode selection, configure NVIC IRQ
  priority mapped to the EXTI line using HAL_NVIC_SetPriority() and enable it
  using HAL_NVIC_EnableIRQ().

   (#) HAL_GPIO_DeInit allows to set register values to their reset value. It's
  also recommended to use it to unconfigure pin which was used as an external
  interrupt or in event mode. That's the only way to reset corresponding bit in
  EXTI & SYSCFG registers.

   (#) To get the level of a pin configured in input mode use
  HAL_GPIO_ReadPin().

   (#) To set/reset the level of a pin configured in output mode use
	   HAL_GPIO_WritePin()/HAL_GPIO_TogglePin().

   (#) To lock pin configuration until next reset use HAL_GPIO_LockPin().

   (#) During and just after reset, the alternate functions are not
	   active and the GPIO pins are configured in input floating mode (except
  JTAG pins).

   (#) The LSE oscillator pins OSC32_IN and OSC32_OUT can be used as general
  purpose (PC14 and PC15, respectively) when the LSE oscillator is off. The LSE
  has priority over the GPIO function.

   (#) The HSE oscillator pins OSC_IN/OSC_OUT can be used as
		general purpose PF0 and PF1, respectively, when the HSE oscillator is
  off. The HSE has priority over the GPIO function.

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/** @addtogroup STM32F0xx_HAL_Driver
 * @{
 */

/** @defgroup GPIO GPIO
 * @brief GPIO HAL module driver
 * @{
 */

/** MISRA C:2012 deviation rule has been granted for following rules:
 * Rule-18.1_d - Medium: Array pointer `GPIOx' is accessed with index [..,..]
 * which may be out of array bounds [..,UNKNOWN] in following APIs:
 * HAL_GPIO_Init
 * HAL_GPIO_DeInit
 */

#ifdef HAL_GPIO_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/** @addtogroup GPIO_Private_Constants GPIO Private Constants
 * @{
 */
#define GPIO_NUMBER 16U
/**
 * @}
 */

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup GPIO_Exported_Functions GPIO Exported Functions
 * @{
 */

/** @defgroup GPIO_Exported_Functions_Group1 Initialization/de-initialization
functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
			  ##### Initialization and de-initialization functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
 * @brief  Initialize the GPIOx peripheral according to the specified parameters
 * in the GPIO_Init.
 * @param  GPIOx where x can be (A..F) to select the GPIO peripheral for STM32F0
 * family
 * @param  GPIO_Init pointer to a GPIO_InitTypeDef structure that contains
 *         the configuration information for the specified GPIO peripheral.
 * @retval None
//  * typedef struct
// {
//   __IO uint32_t MODER;        /*!< GPIO port mode register,                     Address offset: 0x00      */
//   __IO uint32_t OTYPER;       /*!< GPIO port output type register,              Address offset: 0x04      */
//   __IO uint32_t OSPEEDR;      /*!< GPIO port output speed register,             Address offset: 0x08      */
//   __IO uint32_t PUPDR;        /*!< GPIO port pull-up/pull-down register,        Address offset: 0x0C      */
//   __IO uint32_t IDR;          /*!< GPIO port input data register,               Address offset: 0x10      */
//   __IO uint32_t ODR;          /*!< GPIO port output data register,              Address offset: 0x14      */
//   __IO uint32_t BSRR;         /*!< GPIO port bit set/reset register,      Address offset: 0x1A */
//   __IO uint32_t LCKR;         /*!< GPIO port configuration lock register,       Address offset: 0x1C      */
//   __IO uint32_t AFR[2];       /*!< GPIO alternate function low register,  Address offset: 0x20-0x24 */
//   __IO uint32_t BRR;          /*!< GPIO bit reset register,                     Address offset: 0x28      */
// } GPIO_TypeDef;

// typedef struct
// {
//   uint32_t Pin;       /*!< Specifies the GPIO pins to be configured.
//                            This parameter can be any value of @ref GPIO_pins */

//   uint32_t Mode;      /*!< Specifies the operating mode for the selected pins.
//                            This parameter can be a value of @ref GPIO_mode */

//   uint32_t Pull;      /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
//                            This parameter can be a value of @ref GPIO_pull */

//   uint32_t Speed;     /*!< Specifies the speed for the selected pins.
//                            This parameter can be a value of @ref GPIO_speed */

//   uint32_t Alternate;  /*!< Peripheral to be connected to the selected pins
//                             This parameter can be a value of @ref GPIOEx_Alternate_function_selection */
// }GPIO_InitTypeDef;

// 16 GPIO Pins, each pin is two
void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
	// GPIO_Init->Pin is 32 bit, only lower 16 bits hold data

	for (int cur_pin = 0; cur_pin < 16; cur_pin++)
	{
		if ((GPIO_Init->Pin & (0b1 << cur_pin)))
		{
			// GPIO_MODE is a mask for the mode pins
			if (((GPIO_Init->Mode & GPIO_MODE) == MODE_OUTPUT) || ((GPIO_Init->Mode & GPIO_MODE) == MODE_AF))
			{

				// Configure speed
				uint32_t ospeedr_pins = GPIOx->OSPEEDR;

				// Clear specific pins related to speed
				ospeedr_pins &= ~(0b11 << (cur_pin * 2));

				// 2 bits for speed for each pin, get specific mask for current pin
				ospeedr_pins |= (GPIO_Init->Speed << (cur_pin * 2));
				GPIOx->OSPEEDR = ospeedr_pins;

				// Configure output type
				uint32_t otyper_pins = GPIOx->OTYPER;
				otyper_pins &= ~(0b1 << cur_pin);
				otyper_pins |= (((GPIO_Init->Mode >> 4) & 0x1) << (cur_pin));
				GPIOx->OTYPER = otyper_pins;
			}

			if ((GPIO_Init->Mode & GPIO_MODE) == MODE_ANALOG)
			{

				uint32_t pupdr_pins = GPIOx->PUPDR;
				pupdr_pins &= ~(0b11 << (cur_pin * 2));
				pupdr_pins |= GPIO_Init->Pull << (cur_pin * 2);
				GPIOx->PUPDR = pupdr_pins;
			}

			if ((GPIO_Init->Mode & GPIO_MODE) == MODE_AF)
			{

				uint32_t afr_reg;
				if (cur_pin > 7)
				{
					afr_reg = 1;
				}
				else
				{
					afr_reg = 0;
				}
				uint32_t afr_pins = GPIOx->AFR[afr_reg];
				// Selects the current pins in register, mod 8 to account for low v high afr reg, *4 because each pin corresponds to 4 afr bits
				uint32_t pins_in_reg = (cur_pin % 8) * 4;

				// Clear afr pins
				afr_pins &= ~(0b1111 << pins_in_reg);
				afr_pins |= (GPIO_Init->Alternate << pins_in_reg);
				GPIOx->AFR[afr_reg] = afr_pins;
			}

			uint32_t moder_pins = GPIOx->MODER;
			moder_pins &= ~(0b11 << (cur_pin * 2));
			moder_pins |= ((GPIO_Init->Mode & 0b11) << (cur_pin * 2));
			GPIOx->MODER = moder_pins;

			if ((GPIO_Init->Mode & EXTI_MODE) != 0x00)
			{

				__HAL_RCC_SYSCFG_CLK_ENABLE();
				// 4 exti regs responsible for 4 pins each, 4 bits / pin
				uint32_t exti_reg = cur_pin / 4;
				uint32_t pins_in_reg = 4 * (cur_pin % 4);

				// Configure icr pins
				uint32_t config_pins = SYSCFG->EXTICR[exti_reg];
				config_pins &= ~(0b1111 << (pins_in_reg));

				// Gets current gpio port as number, last 3 bits used for selecting port when configuring exti
				config_pins |= (GPIO_GET_INDEX(GPIOx) << pins_in_reg);
				SYSCFG->EXTICR[exti_reg] = config_pins;

				// Configure interrupt mask register
				config_pins = EXTI->IMR;
				config_pins &= ~(1 << cur_pin);
				if ((GPIO_Init->Mode & (0b1 << 16)) != 0)
				{
					config_pins |= (1 << cur_pin);
				}

				EXTI->IMR = config_pins;

				// Configure event mask register
				config_pins = EXTI->EMR;
				config_pins &= ~(1 << cur_pin);
				if ((GPIO_Init->Mode & (0b10 << 16)) != 0)
				{
					config_pins |= (1 << cur_pin);
				}
				EXTI->EMR = config_pins;

				// Configure rising trigger selection register
				config_pins = EXTI->RTSR;
				config_pins &= ~(1 << cur_pin);
				if ((GPIO_Init->Mode & (0b1 << 20)) != 0)
				{
					config_pins |= (1 << cur_pin);
				}
				EXTI->RTSR = config_pins;

				config_pins = EXTI->FTSR;
				config_pins &= ~(1 << cur_pin);
				if ((GPIO_Init->Mode & (0b10 << 20)) != 0)
				{
					config_pins |= (1 << cur_pin);
				}
				EXTI->FTSR = config_pins;
			}
		}
	}
}

/**
 * @brief  De-initialize the GPIOx peripheral registers to their default reset
 * values.
 * @param  GPIOx where x can be (A..F) to select the GPIO peripheral for STM32F0
 * family
 * @param  GPIO_Pin specifies the port bit to be written.
 *         This parameter can be one of GPIO_PIN_x where x can be (0..15).
 * @retval None
 */
void HAL_GPIO_DeInit(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
	uint32_t position = 0x00u;
	uint32_t iocurrent;
	uint32_t tmp;

	/* Check the parameters */
	assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_Pin));

	/* Configure the port pins */
	while ((GPIO_Pin >> position) != 0x00u)
	{
		/* Get current io position */
		iocurrent = (GPIO_Pin) & (1uL << position);

		if (iocurrent != 0x00u)
		{
			/*------------------------- EXTI Mode Configuration --------------------*/
			/* Clear the External Interrupt or Event for the current IO */

			tmp = SYSCFG->EXTICR[position >> 2u];
			tmp &= (0x0FuL << (4u * (position & 0x03u)));
			if (tmp == (GPIO_GET_INDEX(GPIOx) << (4u * (position & 0x03u))))
			{
				/* Clear EXTI line configuration */
				EXTI->IMR &= ~((uint32_t)iocurrent);
				EXTI->EMR &= ~((uint32_t)iocurrent);

				/* Clear Rising Falling edge configuration */
				EXTI->FTSR &= ~((uint32_t)iocurrent);
				EXTI->RTSR &= ~((uint32_t)iocurrent);

				/* Configure the External Interrupt or event for the current IO */
				tmp = 0x0FuL << (4u * (position & 0x03u));
				SYSCFG->EXTICR[position >> 2u] &= ~tmp;
			}

			/*------------------------- GPIO Mode Configuration --------------------*/
			/* Configure IO Direction in Input Floating Mode */
			GPIOx->MODER &= ~(GPIO_MODER_MODER0 << (position * 2u));

			/* Configure the default Alternate Function in current IO */
			GPIOx->AFR[position >> 3u] &=
				~(0xFu << ((uint32_t)(position & 0x07u) * 4u));

			/* Deactivate the Pull-up and Pull-down resistor for the current IO */
			GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << (position * 2u));

			/* Configure the default value IO Output Type */
			GPIOx->OTYPER &= ~(GPIO_OTYPER_OT_0 << position);

			/* Configure the default value for IO Speed */
			GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (position * 2u));
		}

		position++;
	}
}

/**
 * @}
 */

/** @defgroup GPIO_Exported_Functions_Group2 IO operation functions
 *  @brief GPIO Read, Write, Toggle, Lock and EXTI management functions.
 *
@verbatim
 ===============================================================================
					   ##### IO operation functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
 * @brief  Read the specified input port pin.
 * @param  GPIOx where x can be (A..F) to select the GPIO peripheral for STM32F0
 * family
 * @param  GPIO_Pin specifies the port bit to read.
 *         This parameter can be GPIO_PIN_x where x can be (0..15).
 * @retval The input port pin value.
 */
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_PinState bitstatus;

	/* Check the parameters */
	assert_param(IS_GPIO_PIN(GPIO_Pin));

	if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
	{
		bitstatus = GPIO_PIN_SET;
	}
	else
	{
		bitstatus = GPIO_PIN_RESET;
	}
	return bitstatus;
}

/**
 * @brief  Set or clear the selected data port bit.
 * @note   This function uses GPIOx_BSRR and GPIOx_BRR registers to allow atomic
 * read/modify accesses. In this way, there is no risk of an IRQ occurring
 * between the read and the modify access.
 *
 * @param  GPIOx where x can be (A..H) to select the GPIO peripheral for STM32F0
 * family
 * @param  GPIO_Pin specifies the port bit to be written.
 *          This parameter can be one of GPIO_PIN_x where x can be (0..15).
 * @param  PinState specifies the value to be written to the selected bit.
 *          This parameter can be one of the GPIO_PinState enum values:
 *            @arg GPIO_PIN_RESET: to clear the port pin
 *            @arg GPIO_PIN_SET: to set the port pin
 * @retval None
 */
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
					   GPIO_PinState PinState)
{
	// To set ODR, modify bit set/reset reg and bit reset reg
	if (PinState == GPIO_PIN_SET)
	{
		// Have to cast GPIO pin to 32 bit
		// When setting, modify lower 16 bits of BSRR
		GPIOx->BSRR = (uint32_t)GPIO_Pin;
	}
	else if (PinState == GPIO_PIN_RESET)
	{
		// When resetting, modify upper 16 bits of BSRR
		GPIOx->BSRR = (uint32_t)GPIO_Pin << 16;
	}
}

/**
 * @brief  Toggle the specified GPIO pin.
 * @param  GPIOx where x can be (A..F) to select the GPIO peripheral for STM32F0
 * family
 * @param  GPIO_Pin specifies the pin to be toggled.
 * @retval None
 */
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	uint32_t cur_pins = GPIOx->ODR;

	// Resets pins in low register by shifting to high reg
	uint32_t reset_pins = ((cur_pins & GPIO_Pin) << 16);

	// Sets pins in high reg by copying to low reg
	uint32_t set_pins = (~cur_pins) & GPIO_Pin;

	GPIOx->BSRR = reset_pins | set_pins;
}

/**
 * @brief  Locks GPIO Pins configuration registers.
 * @note   The locked registers are GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR,
 *         GPIOx_PUPDR, GPIOx_AFRL and GPIOx_AFRH.
 * @note   The configuration of the locked GPIO pins can no longer be modified
 *         until the next reset.
 * @param  GPIOx where x can be (A..F) to select the GPIO peripheral for STM32F0
 * family
 * @param  GPIO_Pin specifies the port bits to be locked.
 *         This parameter can be any combination of GPIO_PIN_x where x can be
 * (0..15).
 * @retval None
 */
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	__IO uint32_t tmp = GPIO_LCKR_LCKK;

	/* Check the parameters */
	assert_param(IS_GPIO_LOCK_INSTANCE(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_Pin));

	/* Apply lock key write sequence */
	SET_BIT(tmp, GPIO_Pin);
	/* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
	GPIOx->LCKR = tmp;
	/* Reset LCKx bit(s): LCKK='0' + LCK[15-0] */
	GPIOx->LCKR = GPIO_Pin;
	/* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
	GPIOx->LCKR = tmp;
	/* Read LCKK register. This read is mandatory to complete key lock sequence */
	tmp = GPIOx->LCKR;

	/* read again in order to confirm lock is active */
	if ((GPIOx->LCKR & GPIO_LCKR_LCKK) != 0x00u)
	{
		return HAL_OK;
	}
	else
	{
		return HAL_ERROR;
	}
}

/**
 * @brief  Handle EXTI interrupt request.
 * @param  GPIO_Pin Specifies the port pin connected to corresponding EXTI line.
 * @retval None
 */
void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
{
	/* EXTI line interrupt detected */
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
		HAL_GPIO_EXTI_Callback(GPIO_Pin);
	}
}

/**
 * @brief  EXTI line detection callback.
 * @param  GPIO_Pin Specifies the port pin connected to corresponding EXTI line.
 * @retval None
 */
__weak void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/* Prevent unused argument(s) compilation warning */
	UNUSED(GPIO_Pin);

	/* NOTE: This function should not be modified, when the callback is needed,
			  the HAL_GPIO_EXTI_Callback could be implemented in the user file
	 */
}

/**
 * @}
 */

/**
 * @}
 */

#endif /* HAL_GPIO_MODULE_ENABLED */
/**
 * @}
 */

/**
 * @}
 */
