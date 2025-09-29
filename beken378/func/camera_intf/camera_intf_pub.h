#ifndef __CAMERA_INTF_PUB_H__
#define __CAMERA_INTF_PUB_H__

#include "drv_model_pub.h"
#include "i2c_pub.h"
#include "jpeg_encoder_pub.h"

typedef struct camera_sensor_t camera_sensor_t;

typedef void (*sensor_init_func_t)(DD_HANDLE, DD_HANDLE, camera_sensor_t*);

struct camera_sensor_t{
  char *name;
  char *i2c_bus;
  I2C_OP_ST *i2c_cfg;
  DJPEG_DESC_ST *ejpeg_cfg;
  sensor_init_func_t init;;
  void *flip;
  void *effect;

};

//void camera_flip(UINT8 n);
void camera_intfer_init(void *ejpeg_data, camera_sensor_t *sensor);
void camera_intfer_deinit(camera_sensor_t *sensor);

camera_sensor_t* camera_detect(void);

//UINT32 camera_intfer_set_video_param(UINT32 ppi_type, UINT32 pfs_type);

#endif // __CAMERA_INTF_PUB_H__

