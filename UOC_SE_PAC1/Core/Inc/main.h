/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);



/* Private defines -----------------------------------------------------------*/
#define LED_0_Pin 		GPIO_PIN_0
#define LED_0_GPIO_Port GPIOH

#define LED_1_Pin 		GPIO_PIN_1
#define LED_1_GPIO_Port GPIOH

#define LED_2_Pin 		GPIO_PIN_3
#define LED_2_GPIO_Port GPIOC

#define LED_3_Pin 		GPIO_PIN_0
#define LED_3_GPIO_Port GPIOA

#define LED_4_Pin 		GPIO_PIN_1
#define LED_4_GPIO_Port GPIOA

#define LED_5_Pin 		GPIO_PIN_2
#define LED_5_GPIO_Port GPIOA

#define BUTTON_UP_Pin		GPIO_PIN_3
#define BUTTON_UP_GPIO_Port	GPIOA


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
