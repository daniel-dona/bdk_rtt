#include <stdint.h>
#include "include.h"
#include "arm_arch.h"
#include "drv_model_pub.h"
#include "jpeg_encoder_pub.h"
#include "video_transfer.h"
#include "i2c_pub.h"
#include "camera_intf.h"
#include "camera_intf_pub.h"

#include "gc0311.h"

uint8_t gc0311_sensor_detect(void){

    uint8_t data = 0x00;
    uint8_t addr = 0xF0;

    camera_intf_sccb_read2(GC0311_DEV_ID, addr, &data, 1);

    uint8_t found = (data == GC0311_DEV_CHIPID);

    if(found){
        os_printf("Found sensor GC0311! %02X at %02X\r\n", data, addr);
    }else{
        os_printf("NOT found sensor GC0311!\r\n");
    }

    return found;
}

void gc0311_sensor_init(DD_HANDLE i2c_hdl, DD_HANDLE ejpeg_hdl, camera_sensor_t * sensor){

    os_printf("Intializing GC0311 sensor.\r\n");

    uint32_t i, size;
    uint8_t addr, data;
    //I2C_OP_ST i2c_operater;
    //DJPEG_DESC_ST ejpeg_cfg;

    sensor->i2c_cfg->salve_id = GC0311_DEV_ID;

    size = sizeof(gc0311_init_table) / 2;

    for (i = 0; i < size; i++){

        addr = gc0311_init_table[i][0];
        data = gc0311_init_table[i][1];
        camera_intf_sccb_write2(GC0311_DEV_ID, addr, &data, 1);
    }

    gc0311_camera_inf_cfg_ppi(CMPARAM_GET_PPI(sensor->ejpeg_cfg->sener_cfg));
    gc0311_camera_inf_cfg_fps(CMPARAM_GET_FPS(sensor->ejpeg_cfg->sener_cfg));

    os_printf("GC0311 initialization finished.\r\n");


}

void gc0311_camera_inf_cfg_ppi(uint32_t ppi_type){

    uint32_t i, size;
    uint8_t addr, data;

    os_printf("Setting PPI: %d\r\n", ppi_type);

    switch (ppi_type){
            
        case QVGA_320_240:
            size = sizeof(gc0311_QVGA_320_240_table) / 2;
            for (i = 0; i < size; i++)
            {
                addr = gc0311_QVGA_320_240_table[i][0];
                data = gc0311_QVGA_320_240_table[i][1];
                camera_intf_sccb_write2(GC0311_DEV_ID, addr, &data, 1);;
            }
            break;

        case VGA_640_480:
            size = sizeof(gc0311_VGA_640_480_table) / 2;
            for (i = 0; i < size; i++)
            {
                addr = gc0311_VGA_640_480_table[i][0];
                data = gc0311_VGA_640_480_table[i][1];
                camera_intf_sccb_write2(GC0311_DEV_ID, addr, &data, 1);;
            }
            break;

        default:
            os_printf("set PPI unknown\r\n");
            break;
    }
}

void gc0311_camera_inf_cfg_fps(uint32_t fps_type){

    uint32_t i, size;
    uint8_t addr, data;

    os_printf("Setting FPS: %d\r\n", fps_type);

    switch (fps_type){
        
        case TYPE_5FPS:
            size = sizeof(gc0311_5pfs_table) / 2;
            for (i = 0; i < size; i++)
            {
                addr = gc0311_5pfs_table[i][0];
                data = gc0311_5pfs_table[i][1];
                camera_intf_sccb_write2(GC0311_DEV_ID, addr, &data, 1);;
            }
            break;

        case TYPE_10FPS:
            size = sizeof(gc0311_10pfs_table) / 2;
            for (i = 0; i < size; i++)
            {
                addr = gc0311_10pfs_table[i][0];
                data = gc0311_10pfs_table[i][1];
                camera_intf_sccb_write2(GC0311_DEV_ID, addr, &data, 1);;
            }
            break;

        case TYPE_20FPS:
            size = sizeof(gc0311_20pfs_table) / 2;
            for (i = 0; i < size; i++)
            {
                addr = gc0311_20pfs_table[i][0];
                data = gc0311_20pfs_table[i][1];
                camera_intf_sccb_write2(GC0311_DEV_ID, addr, &data, 1);;
            }
            break;

        default:
            os_printf("set FPS unknown\r\n");
            size = sizeof(gc0311_20pfs_table) / 2;
            for (i = 0; i < size; i++)
            {
                addr = gc0311_20pfs_table[i][0];
                data = gc0311_20pfs_table[i][1];
                camera_intf_sccb_write2(GC0311_DEV_ID, addr, &data, 1);;
            }
            break;
    }
}
