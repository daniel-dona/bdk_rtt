#include <stdint.h>
#ifndef _TUYA_PWM_H_
#define _TUYA_PWM_H_

#define TPWM_DEBUG
#undef TPWM_DEBUG

#ifdef TPWM_DEBUG
#define TPWM_PRT      os_printf
#define TPWM_WARN     warning_prf
#define TPWM_FATAL    fatal_prf
#else
#define TPWM_PRT      null_prf
#define TPWM_WARN     null_prf
#define TPWM_FATAL    null_prf
#endif


extern uint32_t tuya_pwm_init(uint8_t channel_num, uint32_t end_value, uint32_t duty_cycle);

extern void tuya_pwm_set_duty_cycle(uint8_t channel_num, uint32_t duty_cycle);
extern void tuya_pwm_set_end_value(uint8_t channel_num, uint32_t end_value);

extern void tuya_pwm_stop(uint8_t channel_num_1, uint8_t channel_num_2);

extern void tuya_pwm_reset_duty_cycle(uint8_t channel_num_1, uint8_t channel_num_2,
                                           uint32_t duty_cycle_1, uint32_t duty_cycle_2,
                                           uint32_t end_value, uint32_t dead_band_1);

#endif


