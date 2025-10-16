/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ******************************************************************************
  * UNIVERSITAT OBERTA DE CATALUNYA
  *
  * EMBEDDED SYSTEMS - PAC1
  *
  * SISTEMAS EMPOTRADOS - PAC1
  *
  * SISTEMES ENCASTATS - PAC1
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "memorymap.h"
#include "tim.h"
#include "gpio.h"
#include <stddef.h>

typedef enum
{
  LED_MODE_NORMAL = 0U,
  LED_MODE_FORCE_ON,
  LED_MODE_FORCE_OFF
} LedMode;

static GPIO_TypeDef *const s_led_ports[] = {
  LED_0_GPIO_Port,
  LED_1_GPIO_Port,
  LED_2_GPIO_Port,
  LED_3_GPIO_Port,
  LED_4_GPIO_Port,
  LED_5_GPIO_Port
};

static const uint16_t s_led_pins[] = {
  LED_0_Pin,
  LED_1_Pin,
  LED_2_Pin,
  LED_3_Pin,
  LED_4_Pin,
  LED_5_Pin
};

static const size_t s_led_count = sizeof(s_led_pins) / sizeof(s_led_pins[0]);

static volatile LedMode s_led_mode = LED_MODE_NORMAL;

static void leds_write_all(GPIO_PinState state);

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

static void leds_write_all(GPIO_PinState state)
{
  for (size_t i = 0; i < s_led_count; ++i)
  {
    HAL_GPIO_WritePin(s_led_ports[i], s_led_pins[i], state);
  }
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

	//To analyze
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals - TO MODIFY */
	UOC_GPIO_Init();
	UOC_TIM6_Init();

	HAL_TIM_Base_Start_IT(&htim6);

  /* Turn off LED_0 (negative logic) */
  HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_SET);
  leds_write_all(GPIO_PIN_SET);

  LedMode previous_mode = s_led_mode;

  /* Infinite loop */
  while (1)
  {
    LedMode mode = LED_MODE_NORMAL;

    if (HAL_GPIO_ReadPin(BUTTON_UP_GPIO_Port, BUTTON_UP_Pin) == GPIO_PIN_RESET)
    {
      mode = LED_MODE_FORCE_ON;
    }
    else if (HAL_GPIO_ReadPin(BUTTON_DOWN_GPIO_Port, BUTTON_DOWN_Pin) == GPIO_PIN_RESET)
    {
      mode = LED_MODE_FORCE_OFF;
    }

    s_led_mode = mode;

    if (mode != previous_mode)
    {
      switch (mode)
      {
      case LED_MODE_FORCE_ON:
        leds_write_all(GPIO_PIN_RESET);
        break;

      case LED_MODE_FORCE_OFF:
        leds_write_all(GPIO_PIN_SET);
        break;

      case LED_MODE_NORMAL:
      default:
        leds_write_all(HAL_GPIO_ReadPin(LED_0_GPIO_Port, LED_0_Pin));
        break;
      }

      previous_mode = mode;
    }
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE4) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* Interrupt handling function */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance != TIM6)
  {
    return;
  }

  switch (s_led_mode)
  {
  case LED_MODE_FORCE_ON:
    leds_write_all(GPIO_PIN_RESET);
    break;

  case LED_MODE_FORCE_OFF:
    leds_write_all(GPIO_PIN_SET);
    break;

  case LED_MODE_NORMAL:
  default:
    HAL_GPIO_TogglePin(LED_0_GPIO_Port, LED_0_Pin);
    leds_write_all(HAL_GPIO_ReadPin(LED_0_GPIO_Port, LED_0_Pin));
    break;
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
