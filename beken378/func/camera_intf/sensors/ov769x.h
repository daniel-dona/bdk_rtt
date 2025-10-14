#include <stdint.h>
#define OV769X_DEV              (0xFFF01)
#define OV769X_DEV_ID           (0x21)

#define OV769X_DEV_IDREG1       (0x0A) //0xB310
#define OV769X_DEV_IDREG2       (0x0B) //0xB310

#define OV769X_DEV_CHIPID       (0x91) //0xB310

#include "drv_model_pub.h"
#include "camera_intf_pub.h"

// Sensor control functions
uint8_t ov769x_sensor_detect(void);
void ov769x_sensor_init(DD_HANDLE i2c_hdl, DD_HANDLE ejpeg_hdl,  camera_sensor_t * sensor);

void ov769x_camera_inf_cfg_ppi(uint32_t ppi_type);
void ov769x_camera_inf_cfg_fps(uint32_t fps_type);

// Register tables
//extern const uint8_t ov769x_init_table[287][2];
//extern const uint8_t ov769x_init_table2[288][2];
extern const uint8_t ov769x_init_table[][2];

