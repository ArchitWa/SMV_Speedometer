#ifndef _SMV_SPEEDOMETER_BOARD_H
#define _SMV_SPEEDOMETER_BOARD_H

#include "main.h"

/* Digit enable macros (active LOW) */
#define D1_ON   HAL_GPIO_WritePin(Digit_1_GPIO_Port, Digit_1_Pin, GPIO_PIN_RESET)
#define D1_OFF  HAL_GPIO_WritePin(Digit_1_GPIO_Port, Digit_1_Pin, GPIO_PIN_SET)

#define D2_ON   HAL_GPIO_WritePin(Digit_2_GPIO_Port, Digit_2_Pin, GPIO_PIN_RESET)
#define D2_OFF  HAL_GPIO_WritePin(Digit_2_GPIO_Port, Digit_2_Pin, GPIO_PIN_SET)

#define D3_ON   HAL_GPIO_WritePin(Digit_3_GPIO_Port, Digit_3_Pin, GPIO_PIN_RESET)
#define D3_OFF  HAL_GPIO_WritePin(Digit_3_GPIO_Port, Digit_3_Pin, GPIO_PIN_SET)

#define D4_ON   HAL_GPIO_WritePin(Digit_4_GPIO_Port, Digit_4_Pin, GPIO_PIN_RESET)
#define D4_OFF  HAL_GPIO_WritePin(Digit_4_GPIO_Port, Digit_4_Pin, GPIO_PIN_SET)

/* Decimal point */
#define DP_ON  HAL_GPIO_WritePin(DP_GPIO_Port, DP_Pin, GPIO_PIN_SET)
#define DP_OFF   HAL_GPIO_WritePin(DP_GPIO_Port, DP_Pin, GPIO_PIN_RESET)

#endif
