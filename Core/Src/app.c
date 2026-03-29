#include "app.h"
#include "svpwm.h"
#include "feedback.h"
#include <stdio.h>

static motor_state_t motor_state = {0};
static feedback_data_t feedback_data = {0};

void App_Init(ADC_HandleTypeDef* hadc1, I2C_HandleTypeDef* hi2c2, SPI_HandleTypeDef* hspi1, TIM_HandleTypeDef* htim1, UART_HandleTypeDef* huart1) {
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

    // 校准 ADC，启动 DMA
    // 重要：同时禁用 DMA IRQ，以防止 DMA 中断被频繁触发，阻塞进程
    LL_ADC_StartCalibration(ADC1);
    while (LL_ADC_IsCalibrationOnGoing(ADC1));
    Feedback_Service_Init(hadc1);
    HAL_NVIC_DisableIRQ(DMA1_Channel1_IRQn);

    HAL_GPIO_WritePin(LED_OUT_PIN_GPIO_Port, LED_OUT_PIN_Pin, GPIO_PIN_SET);

    // 启动部分，仅有当 17秒加速 过去后，主循环才会被执行
    Set_Motor_RPM(0, &motor_state);
    for (int i = 100; i < 1800; ++i) {
        Set_Motor_RPM(i, &motor_state);
        HAL_Delay(10);
    }
}

void App_Loop(ADC_HandleTypeDef* hadc1, I2C_HandleTypeDef* hi2c2, SPI_HandleTypeDef* hspi1, TIM_HandleTypeDef* htim1, UART_HandleTypeDef* huart1) {
    // 闪灯表明主循环正常发生
    HAL_GPIO_TogglePin(LED_OUT_PIN_GPIO_Port, LED_OUT_PIN_Pin);
    HAL_Delay(100);

    uint32_t time = HAL_GetTick();
    char debug_buffer[128];
    int debug_info_length = 0;

    // 设置信息输出
    debug_info_length = snprintf(debug_buffer, sizeof(debug_buffer),
        "[Settings][%lu] RPM: %lu, DeltaPhase: %lu\n",
        time,
        motor_state.set_rotate_rpm,
        motor_state.set_delta_phase
    );
    if (debug_info_length < 0) debug_info_length = 0;
    if (debug_info_length > (int)sizeof(debug_buffer)) debug_info_length = sizeof(debug_buffer);
    HAL_UART_Transmit(huart1, (uint8_t*)debug_buffer, (uint16_t)debug_info_length, HAL_MAX_DELAY);

    // SVPWM 日志输出
    debug_info_length = snprintf(debug_buffer, sizeof(debug_buffer),
        "[SVPWM][%lu] PhaseA: %lu, PhaseB: %lu, PhaseC: %lu\n",
        time,
        motor_state.current_phase_A_comp_val,
        motor_state.current_phase_B_comp_val,
        motor_state.current_phase_C_comp_val
    );
    if (debug_info_length < 0) debug_info_length = 0;
    if (debug_info_length > (int)sizeof(debug_buffer)) debug_info_length = sizeof(debug_buffer);
    HAL_UART_Transmit(huart1, (uint8_t*)debug_buffer, (uint16_t)debug_info_length, HAL_MAX_DELAY);

    // ADC 反馈数据输出
    Update_Feedback_Data(&feedback_data);
    debug_info_length = snprintf(debug_buffer, sizeof(debug_buffer),
        "[Feedback][%lu] ShuntVoltageA: %lu, ShuntVoltageB: %lu, ShuntVoltageC: %lu, SOA: %lu, SOB: %lu, SOC: %lu\n",
        time,
        feedback_data.SHA_shunt_voltage,
        feedback_data.SHB_shunt_voltage,
        feedback_data.SHC_shunt_voltage,
        feedback_data.SOA,
        feedback_data.SOB,
        feedback_data.SOC
    );
    if (debug_info_length < 0) debug_info_length = 0;
    if (debug_info_length > (int)sizeof(debug_buffer)) debug_info_length = sizeof(debug_buffer);
    HAL_UART_Transmit(huart1, (uint8_t*)debug_buffer, (uint16_t)debug_info_length, HAL_MAX_DELAY);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM1) {
        Update_Motor_State(&motor_state);
        __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, motor_state.current_phase_A_comp_val);
        __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_2, motor_state.current_phase_B_comp_val);
        __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_3, motor_state.current_phase_C_comp_val);
    }
}
