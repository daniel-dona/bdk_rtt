#include <stdint.h>
#include "include.h"
#include "arm_arch.h"
#include "drv_model_pub.h"
#include "jpeg_encoder_pub.h"
#include "video_transfer.h"
#include "i2c_pub.h"
#include "camera_intf.h"
#include "camera_intf_pub.h"

#include "ov769x.h"

uint8_t ov769x_sensor_detect(void){

    uint8_t data = 0x00;
    uint8_t addr = OV769X_DEV_IDREG2;

    camera_intf_sccb_read2(OV769X_DEV_ID, addr, &data, 1);

    uint8_t found = (data == OV769X_DEV_CHIPID);

    if(found){
        os_printf("Found sensor OV769X! %02X at %02X\r\n", data, addr);
    }else{
        os_printf("NOT found sensor OV769X!\r\n");
    }

    return found;
}

void ov769x_sensor_init(DD_HANDLE i2c_hdl, DD_HANDLE ejpeg_hdl, camera_sensor_t * sensor){

    os_printf("Intializing OV769X sensor.\r\n");

    uint32_t i, size;
    uint8_t addr, data;
    //I2C_OP_ST i2c_operater;
    //DJPEG_DESC_ST ejpeg_cfg;

    sensor->i2c_cfg->salve_id = OV769X_DEV_ID;

    size = sizeof(ov769x_init_table) / 2;

    os_printf("Writing %d registers\r\n", size);

    for (i = 0; i < size; i++){

        addr = ov769x_init_table[i][0];
        data = ov769x_init_table[i][1];
        camera_intf_sccb_write2(OV769X_DEV_ID, addr, &data, 1);

        //os_printf("%d 0x%02X 0x%02X\r\n", i, addr, data);
    }

    ov769x_camera_inf_cfg_ppi(CMPARAM_GET_PPI(sensor->ejpeg_cfg->sener_cfg));
    ov769x_camera_inf_cfg_fps(CMPARAM_GET_FPS(sensor->ejpeg_cfg->sener_cfg));

    os_printf("OV769X initialization finished.\r\n");


}

void ov769x_camera_inf_cfg_ppi(uint32_t ppi_type){


    os_printf("Setting PPI: %d\r\n", ppi_type);

    // NOP
  
}

void ov769x_camera_inf_cfg_fps(uint32_t fps_type){


    os_printf("Setting FPS: %d\r\n", fps_type);

    // NOP
}
