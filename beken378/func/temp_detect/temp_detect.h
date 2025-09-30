#include <stdint.h>
#ifndef __TEMP_DETECT_H__
#define __TEMP_DETECT_H__

typedef  struct temp_detect_config_st
{
    uint16_t last_detect_val;
    uint16_t detect_intval;   
    uint16_t detect_thre;
    uint16_t inital_data;
    uint16_t dist_inital;
    uint16_t last_xtal_val;
	#if (CFG_SOC_NAME != SOC_BK7231)
    uint16_t xtal_thre_val;
    uint16_t xtal_init_val; 
	#endif  
    uint32_t detect_intval_change;    
    beken_timer_t detect_timer;
} TEMP_DETECT_CONFIG_ST, TEMP_DETECT_CONFIG_PTR;

#endif
// eof

