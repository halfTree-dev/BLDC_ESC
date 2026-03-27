/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define EN_OUT_PIN_Pin GPIO_PIN_9
#define EN_OUT_PIN_GPIO_Port GPIOB
#define ADC_PA_PIN_Pin GPIO_PIN_0
#define ADC_PA_PIN_GPIO_Port GPIOA
#define ADC_PB_PIN_Pin GPIO_PIN_1
#define ADC_PB_PIN_GPIO_Port GPIOA
#define ADC_PC_PIN_Pin GPIO_PIN_2
#define ADC_PC_PIN_GPIO_Port GPIOA
#define ADC_SOA_PIN_Pin GPIO_PIN_3
#define ADC_SOA_PIN_GPIO_Port GPIOA
#define ADC_SOB_PIN_Pin GPIO_PIN_4
#define ADC_SOB_PIN_GPIO_Port GPIOA
#define ADC_SOC_PIN_Pin GPIO_PIN_5
#define ADC_SOC_PIN_GPIO_Port GPIOA
#define LED_OUT_PIN_Pin GPIO_PIN_6
#define LED_OUT_PIN_GPIO_Port GPIOA
#define NFAULT_IN_PIN_Pin GPIO_PIN_2
#define NFAULT_IN_PIN_GPIO_Port GPIOB
#define CAL_OUT_PIN_Pin GPIO_PIN_8
#define CAL_OUT_PIN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
