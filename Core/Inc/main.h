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
#define COMPLEX_NUMBER_SIZE		8
#define LPC_PACKET_DATA_SIZE	24
#define SECTION_PACKET_SIZE		300

#define FIRST_SECTION_CUTS_PER_PACKET	5

#define UDP_PORT				1899

typedef struct{ // size = 28
	uint32_t cutIndex;
	uint8_t stepData[ELECTRODE_COUNT][CUSTOM_FLOAT_SIZE];
}QOneLpcCutPacket;

typedef struct{ // size = 68
	uint32_t cutIndex;
	uint8_t  stepData[ELECTRODE_COUNT][COMPLEX_NUMBER_SIZE];
}QCurrentLpcCutPacket;

typedef struct{
	QOneLpcCutPacket steps[STEP_SIZE];					// size = 8*28
	QCurrentLpcCutPacket currentSamples; 				// size = 68
	float32_t temperature;								// size = 4
	uint32_t status;									// size = 4
}QFirstSectionPacket;									// total size = 8*28 + 68 + 8 = 300

typedef struct{
	QOneLpcCutPacket steps[STEP_SIZE];					// size = 8*28
	uint32_t status;									// size = 4
}QSecondSectionPacket;									// total size = 8*28 + 4 = 228
typedef struct{//There are two entities for double buffered DMA
	ALIGN_32BYTES( QFirstSectionPacket  firstSectionPacket [2*FIRST_SECTION_CUTS_PER_PACKET] ); 			// size = 300 * 5 * 2
	ALIGN_32BYTES( QSecondSectionPacket secondSectionPacket[2*FIRST_SECTION_CUTS_PER_PACKET] );			// size = 228 *5 * 2
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
#define uSecondTimPrescaller 274
#define LD3_RED_Pin GPIO_PIN_14
#define LD3_RED_GPIO_Port GPIOB
#define LD1_GR_Pin GPIO_PIN_11
#define LD1_GR_GPIO_Port GPIOC
#define LD2_YEL_Pin GPIO_PIN_1
#define LD2_YEL_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
