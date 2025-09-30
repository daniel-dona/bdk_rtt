#include <stdint.h>
#include "include.h"
#include "arm_arch.h"

#include "target_util_pub.h"
#include "sys_ctrl_pub.h"
#include "fake_clock_pub.h"
#include "drv_model_pub.h"

/*******************************************************************************
* Function Implemantation
*******************************************************************************/
/*
	MCLK:26MHz, delay(1): about 25us
				delay(10):about 125us
				delay(100):about 850us
 */
void delay(int32_t num)
{
    volatile int32_t i, j;

    for(i = 0; i < num; i ++)
    {
        for(j = 0; j < 100; j ++)
            ;
    }
}

/*
	when parameter is 1, the return result is approximately 1 ms;
 */
void delay_ms(uint32_t ms_count)
{
    uint32_t ret;
    uint32_t div;
    uint32_t clk = 0;
    uint32_t cell;
    SYS_CTRL_U param;

    ret = sddev_control(SCTRL_DEV_NAME, CMD_GET_SCTRL_CONTROL, &param);
    ASSERT(SCTRL_SUCCESS == ret);

    div = param.bits.mclk_div;
    switch(param.bits.mclk_mux)
    {
    case MCLK_MODE_DCO:
    case MCLK_MODE_26M_XTAL:
        clk = 26000000;
        break;

    case MCLK_MODE_DPLL:
        clk = 480000000 / (2 << div);
        break;

    case MCLK_MODE_LPO:
        clk = 32000;
        break;

    default:
        break;
    }

    ASSERT(clk);

    cell = 100 * clk / 26000000;
    delay(ms_count * cell);
}

/*
	[delay offset]worst case: delay about 1 second;
 */
void delay_sec(uint32_t ms_count)
{
    uint32_t t0;
    uint32_t t1;

    t0 = fclk_get_second();
    while(1)
    {
        t1 = fclk_get_second();
        if(t1 - t0 >= 1)
        {
            break;
        }
    }
}

/*
	[delay offset]worst case: delay about 1 tick;
 */
void delay_tick(uint32_t tick_count)
{
    uint32_t t0;
    uint32_t t1;

    t0 = fclk_get_tick();
    while(1)
    {
        t1 = fclk_get_tick();
        if(t1 - t0 >= 1)
        {
            break;
        }
    }
}

// EOF

