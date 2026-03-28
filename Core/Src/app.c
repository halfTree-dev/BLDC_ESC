#include "app.h"
#include <math.h>
#include <stdio.h>

static motor_state_t motor_state = {0};

void App_Init(ADC_HandleTypeDef *hadc1, I2C_HandleTypeDef* hi2c2, SPI_HandleTypeDef* hspi1, TIM_HandleTypeDef* htim1, UART_HandleTypeDef* huart1) {
    HAL_Delay(1000);
    HAL_GPIO_WritePin(EN_OUT_PIN_GPIO_Port, EN_OUT_PIN_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);

    HAL_TIM_PWM_Start(htim1, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(htim1, TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Start(htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(htim1, TIM_CHANNEL_3);
    HAL_TIMEx_PWMN_Start(htim1, TIM_CHANNEL_3);

    HAL_TIM_Base_Start_IT(htim1);

    Set_Motor_RPM(0, &motor_state);
    for (int i = 0; i < 1500; ++i) {
        Set_Motor_RPM(i, &motor_state);
        HAL_Delay(10);
    }
}

void App_Loop(ADC_HandleTypeDef *hadc1, I2C_HandleTypeDef* hi2c2, SPI_HandleTypeDef* hspi1, TIM_HandleTypeDef* htim1, UART_HandleTypeDef* huart1) {
    HAL_Delay(10);
    // 这里是调试信息输出
    char buf[128];
    int len = snprintf(buf, sizeof(buf), "phase: %lu, A: %lu, B: %lu, C: %lu, RPM: %lu\r\n", (unsigned long)motor_state.current_phase, (unsigned long)motor_state.current_phase_A_comp_val, (unsigned long)motor_state.current_phase_B_comp_val, (unsigned long)motor_state.current_phase_C_comp_val, (unsigned long)(motor_state.set_rotate_rpm));
    if (len < 0) len = 0;
    if (len > (int)sizeof(buf)) len = sizeof(buf);
    HAL_UART_Transmit(huart1, (uint8_t*)buf, (uint16_t)len, HAL_MAX_DELAY);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM1) {
        Update_Motor_State(&motor_state);
        __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, motor_state.current_phase_A_comp_val);
        __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_2, motor_state.current_phase_B_comp_val);
        __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_3, motor_state.current_phase_C_comp_val);
    }
}