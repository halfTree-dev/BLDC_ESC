#include "feedback.h"

static volatile uint32_t feedback_data_cache[ADC1_IN_CNT] = {0};

void Feedback_Service_Init(ADC_HandleTypeDef *hadc1) {
    // 启动 ADC 的 DMA 模式，采集 ADC1_IN_CNT 个通道的数据到 feedback_data_cache 中
    HAL_ADC_Start_DMA(hadc1, (uint32_t*)feedback_data_cache, ADC1_IN_CNT);
}

void Update_Feedback_Data(feedback_data_t* data) {
    data->SHA_shunt_voltage = feedback_data_cache[0];
    data->SHB_shunt_voltage = feedback_data_cache[1];
    data->SHC_shunt_voltage = feedback_data_cache[2];
    data->SOA = feedback_data_cache[3];
    data->SOB = feedback_data_cache[4];
    data->SOC = feedback_data_cache[5];
}