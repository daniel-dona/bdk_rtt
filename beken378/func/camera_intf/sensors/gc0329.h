#include <stdint.h>
#define GC0329_DEV              (0xFFF01)
#define GC0329_DEV_ID           (0x31)
#define GC0329_DEV_CHIPID       (0xC0) //0xB310

#include "drv_model_pub.h"
#include "camera_intf_pub.h"

// Sensor control functions
uint8_t gc0329_sensor_detect(void);
void gc0329_sensor_init(DD_HANDLE i2c_hdl, DD_HANDLE ejpeg_hdl,  camera_sensor_t * sensor);

void gc0329_camera_inf_cfg_ppi(uint32_t ppi_type);
void gc0329_camera_inf_cfg_fps(uint32_t fps_type);

// Register tables
//extern const uint8_t gc0329_init_table[287][2];
//extern const uint8_t gc0329_init_table2[288][2];
extern const uint8_t gc0329_init_table[270][2];