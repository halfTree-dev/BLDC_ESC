#ifndef __APP_H
#define __APP_H

#include "main.h"
#include "svpwm.h"

void App_Init(ADC_HandleTypeDef *hadc1, I2C_HandleTypeDef* hi2c2, SPI_HandleTypeDef* hspi1, TIM_HandleTypeDef* htim1, UART_HandleTypeDef* huart1);
void App_Loop(ADC_HandleTypeDef *hadc1, I2C_HandleTypeDef* hi2c2, SPI_HandleTypeDef* hspi1, TIM_HandleTypeDef* htim1, UART_HandleTypeDef* huart1);

#endif /* __APP_H */