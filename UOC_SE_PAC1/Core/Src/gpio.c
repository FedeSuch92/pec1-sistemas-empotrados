/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * Universitat Oberta de Catalunya
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/

/** Configure pins
     PA13 (JTMS/SWDIO)   ------> DEBUG_JTMS-SWDIO
     PA14 (JTCK/SWCLK)   ------> DEBUG_JTCK-SWCLK
     PA15 (JTDI)   ------> DEBUG_JTDI
     PB3 (JTDO/TRACESWO)   ------> DEBUG_JTDO-SWO
*/
void UOC_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_RESET);

  /*Configure LED0 */
  GPIO_InitStruct.Pin = LED_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_0_GPIO_Port, &GPIO_InitStruct);

  GPIO_PinState led0_state = HAL_GPIO_ReadPin(LED_0_GPIO_Port, LED_0_Pin);

  GPIO_InitStruct.Pin = LED_1_Pin;
  HAL_GPIO_Init(LED_1_GPIO_Port, &GPIO_InitStruct);
  HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, led0_state);

  GPIO_InitStruct.Pin = LED_2_Pin;
  HAL_GPIO_Init(LED_2_GPIO_Port, &GPIO_InitStruct);
  HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, led0_state);

  GPIO_InitStruct.Pin = LED_3_Pin;
  HAL_GPIO_Init(LED_3_GPIO_Port, &GPIO_InitStruct);
  HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, led0_state);

  GPIO_InitStruct.Pin = LED_4_Pin;
  HAL_GPIO_Init(LED_4_GPIO_Port, &GPIO_InitStruct);
  HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, led0_state);

  GPIO_InitStruct.Pin = LED_5_Pin;
  HAL_GPIO_Init(LED_5_GPIO_Port, &GPIO_InitStruct);
  HAL_GPIO_WritePin(LED_5_GPIO_Port, LED_5_Pin, led0_state);

  /* Configure JOYSTICK UP Button */
  GPIO_InitStruct.Pin = BUTTON_UP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BUTTON_UP_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = BUTTON_DOWN_Pin;
  HAL_GPIO_Init(BUTTON_DOWN_GPIO_Port, &GPIO_InitStruct);
}
