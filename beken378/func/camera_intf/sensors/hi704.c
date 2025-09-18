#include "include.h"
#include "arm_arch.h"
#include "drv_model_pub.h"
#include "jpeg_encoder_pub.h"
#include "video_transfer.h"
#include "i2c_pub.h"
#include "camera_intf.h"
#include "camera_intf_pub.h"

#include "hi704.h"

uint8_t hi704_sensor_detect(void){
    uint8_t data;
    uint8_t addr = 0x04;

    camera_intf_sccb_read((UINT8) addr, (UINT8 *) &data);

    os_printf("Result: %d, Expected: %d", data, HI704_DEV_CHIPID);

    return (data == HI704_DEV_CHIPID);
}

void hi704_sensor_init(DD_HANDLE i2c_hdl, DD_HANDLE ejpeg_hdl, camera_sensor_t * sensor){

    os_printf("Intializing HI704 sensor.\r\n");

    UINT32 i, size;
    UINT8 addr, data;
    //I2C_OP_ST i2c_operater;
    //DJPEG_DESC_ST ejpeg_cfg;

    sensor->i2c_cfg->salve_id = HI704_DEV_ID;

    size = sizeof(hi704_sensor_init_sequence) / 2;

    for (i = 0; i < size; i++){

        addr = hi704_sensor_init_sequence[i][0];
        data = hi704_sensor_init_sequence[i][1];
        camera_intf_sccb_write(addr, data);
    }

    //hi704_camera_inf_cfg_ppi(CMPARAM_GET_PPI(sensor->ejpeg_cfg->sener_cfg));
    //hi704_camera_inf_cfg_fps(CMPARAM_GET_FPS(sensor->ejpeg_cfg->sener_cfg));

    os_printf("HI704 initialization finished.\r\n");


}