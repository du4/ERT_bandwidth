/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "arm_math.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define CUSTOM_FLOAT_SIZE		3
#define LPC_SIZE				8
#define STEP_SIZE				8
#define ELECTRODE_COUNT			8
#define LPC_PACKET_DATA_SIZE	24
#define SECTION_PACKET_SIZE		228

#define UDP_PORT				1899

typedef struct{ // size = 24
	uint8_t data[LPC_PACKET_DATA_SIZE];
}QOneLpcCutPacket;

typedef struct{
	uint32_t cutIndex;								// size = 4
	QOneLpcCutPacket steps[STEP_SIZE];				// size = 8*24
	uint8_t currentSamples[LPC_PACKET_DATA_SIZE]; 	// size = 24
	float32_t temperature;							// size = 4
	uint32_t status;								// size = 4
}QSectionPacket;									// total size = 12 + 9*24 = 12+216 = 228

typedef struct{//There are two entities for double buffered DMA
	QSectionPacket firstSectionPacket0; // size = 228
	QSectionPacket firstSectionPacket1; // size = 228
	QSectionPacket secondSectionPacket0;// size = 228
	QSectionPacket secondSectionPacket1;// size = 228
}QFullPacket;


/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LD1_GR_Pin GPIO_PIN_0
#define LD1_GR_GPIO_Port GPIOB
#define LD3_RED_Pin GPIO_PIN_14
#define LD3_RED_GPIO_Port GPIOB
#define LD2_YEL_Pin GPIO_PIN_1
#define LD2_YEL_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
