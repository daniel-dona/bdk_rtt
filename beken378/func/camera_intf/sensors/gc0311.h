#define GC0311_DEV              (0xFFF01)
#define GC0311_DEV_ID           (0x33)
#define GC0311_DEV_CHIPID       (0xBB)

#include "drv_model_pub.h"
#include "camera_intf_pub.h"

// Sensor control functions
uint8_t gc0311_sensor_detect(void);
void gc0311_sensor_init(DD_HANDLE i2c_hdl, DD_HANDLE ejpeg_hdl,  camera_sensor_t * sensor);

void gc0311_camera_inf_cfg_ppi(UINT32 ppi_type);
void gc0311_camera_inf_cfg_fps(UINT32 fps_type);

// Register tables
const UINT8 gc0311_init_talbe[522][2];
const UINT8 gc0311_5pfs_talbe[9][2];
const UINT8 gc0311_10pfs_talbe[9][2];
const UINT8 gc0311_20pfs_talbe[9][2];
const UINT8 gc0311_QVGA_320_240_talbe[12][2];
const UINT8 gc0311_VGA_640_480_talbe[10][2];

