#include <stdint.h>
#define GC0310_DEV              (0xFFF01)
#define GC0310_DEV_ID           (0x21)
#define GC0310_DEV_CHIPID       (0xA3) //0xA310

#include "drv_model_pub.h"
#include "camera_intf_pub.h"

// Sensor control functions
uint8_t gc0310_sensor_detect(void);
void gc0310_sensor_init(DD_HANDLE i2c_hdl, DD_HANDLE ejpeg_hdl,  camera_sensor_t * sensor);

void gc0310_camera_inf_cfg_ppi(uint32_t ppi_type);
void gc0310_camera_inf_cfg_fps(uint32_t fps_type);

// Register tables
extern const uint8_t gc0310_init_table[288][2];