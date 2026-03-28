#ifndef SVPWM_H
#define SVPWM_H

#include "main.h"

#define ANGLE_RESOLUTION 1024
#define VALUE_RESOLUTION 2000

#define ONE_OF_THREE_UINT32_MAX 1431655765U
#define TWO_OF_THREE_UINT32_MAX 2863311530U

// 对于计时器而言：64MHz / (2000) (Period) = 32kHz
#define TIM_HZ 32000

typedef struct motor_state {
    uint32_t current_phase;
    uint16_t current_phase_A_comp_val;
    uint16_t current_phase_B_comp_val;
    uint16_t current_phase_C_comp_val;

    uint32_t set_rotate_rpm;
    uint32_t set_delta_phase;
} motor_state_t;

uint16_t Get_SVPWM_Value(uint32_t current_phase);
void Set_Motor_RPM(uint16_t rpm, motor_state_t* state);
void Update_Motor_State(motor_state_t* state);

#endif // SVPWM_H