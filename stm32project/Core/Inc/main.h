/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern TIM_HandleTypeDef htim3;
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
#define A0_PD_BT_Pin GPIO_PIN_0
#define A0_PD_BT_GPIO_Port GPIOA
#define A1_BT1_Pin GPIO_PIN_1
#define A1_BT1_GPIO_Port GPIOA
#define A2_BT2_Pin GPIO_PIN_4
#define A2_BT2_GPIO_Port GPIOA
#define PD_BUZZER_Pin GPIO_PIN_6
#define PD_BUZZER_GPIO_Port GPIOA
#define A3_BT3_Pin GPIO_PIN_0
#define A3_BT3_GPIO_Port GPIOB
#define D6_PDL_LED1_Pin GPIO_PIN_10
#define D6_PDL_LED1_GPIO_Port GPIOB
#define D7_PDL_LED2_Pin GPIO_PIN_8
#define D7_PDL_LED2_GPIO_Port GPIOA
#define D2_TF1_LED1_Pin GPIO_PIN_10
#define D2_TF1_LED1_GPIO_Port GPIOA
#define D3_TF1_LED2_Pin GPIO_PIN_3
#define D3_TF1_LED2_GPIO_Port GPIOB
#define D5_TF2_LED2_Pin GPIO_PIN_4
#define D5_TF2_LED2_GPIO_Port GPIOB
#define D4_TF2_LED1_Pin GPIO_PIN_5
#define D4_TF2_LED1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
