#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "main.h"

#define ADC1_IN_CNT 6

typedef struct {
    uint32_t SHA_shunt_voltage;
    uint32_t SHB_shunt_voltage;
    uint32_t SHC_shunt_voltage;
    uint32_t SOA;
    uint32_t SOB;
    uint32_t SOC;
} feedback_data_t;

void Feedback_Service_Init(ADC_HandleTypeDef* hadc1);
void Update_Feedback_Data(feedback_data_t* data);

#endif // FEEDBACK_H
