#include <stdint.h>
#include "include.h"
#include "arm_arch.h"
#include "drv_model_pub.h"
#include "jpeg_encoder_pub.h"
#include "video_transfer.h"
#include "i2c_pub.h"
#include "camera_intf.h"
#include "camera_intf_pub.h"

#include "gc0329.h"

uint8_t gc0329_sensor_detect(void){

    // This enables detection

    uint8_t trigger_reg = 0xFC;
    uint8_t trigger_val = 0x16;

    camera_intf_sccb_write2(GC0329_DEV_ID, (uint8_t) trigger_reg, (uint8_t *) &trigger_val, 1);

    uint8_t data = 0x00;
    uint8_t addr = 0x00;

    camera_intf_sccb_read2(GC0329_DEV_ID, addr, &data, 1);

    uint8_t found = (data == GC0329_DEV_CHIPID);

    if(found){
        os_printf("Found sensor GC0329! %02X at %02X\r\n", data, addr);
    }else{
        os_printf("NOT found sensor GC0329!\r\n");
    }

    return found;
}

void gc0329_sensor_init(DD_HANDLE i2c_hdl, DD_HANDLE ejpeg_hdl, camera_sensor_t * sensor){

    os_printf("Intializing GC0329 sensor.\r\n");

    uint32_t i, size;
    uint8_t addr, data;
    //I2C_OP_ST i2c_operater;
    //DJPEG_DESC_ST ejpeg_cfg;

    sensor->i2c_cfg->salve_id = GC0329_DEV_ID;

    size = sizeof(gc0329_init_table) / 2;

    os_printf("Writing %d registers\r\n", size);

    for (i = 0; i < size; i++){

        addr = gc0329_init_table[i][0];
        data = gc0329_init_table[i][1];
        camera_intf_sccb_write2(GC0329_DEV_ID, addr, &data, 1);

        //os_printf("%d 0x%02X 0x%02X\r\n", i, addr, data);
    }

    gc0329_camera_inf_cfg_ppi(CMPARAM_GET_PPI(sensor->ejpeg_cfg->sener_cfg));
    gc0329_camera_inf_cfg_fps(CMPARAM_GET_FPS(sensor->ejpeg_cfg->sener_cfg));

    os_printf("GC0329 initialization finished.\r\n");


}

void gc0329_camera_inf_cfg_ppi(uint32_t ppi_type){


    os_printf("Setting PPI: %d\r\n", ppi_type);

    // NOP
  
}

void gc0329_camera_inf_cfg_fps(uint32_t fps_type){


    os_printf("Setting FPS: %d\r\n", fps_type);

    // NOP
}
