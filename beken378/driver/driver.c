#include <stdint.h>
#include "include.h"
#include "driver_pub.h"
#include "dd_pub.h"
#include "drv_model_pub.h"

uint32_t driver_init(void)
{    
    drv_model_init();
    g_dd_init();
    
    return 0;
}

// eof
