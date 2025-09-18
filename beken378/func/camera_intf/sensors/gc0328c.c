#include "include.h"
#include "arm_arch.h"
#include "drv_model_pub.h"
#include "jpeg_encoder_pub.h"
#include "video_transfer.h"
#include "i2c_pub.h"
#include "camera_intf.h"
#include "camera_intf_pub.h"

#include "gc0328c.h"

uint8_t gc0328c_sensor_detect(void){

    uint8_t data;
    uint8_t addr = 0xF0;

    camera_intf_sccb_read((UINT8) addr, (UINT8 *) &data);

    os_printf("Result: %d, Expected: %d", data, GC0328C_DEV_CHIPID);

    return (data == GC0328C_DEV_CHIPID);
}

void gc0328c_sensor_init(DD_HANDLE i2c_hdl, DD_HANDLE ejpeg_hdl, camera_sensor_t * sensor){

    os_printf("Intializing GC0238C sensor.\r\n");

    UINT32 i, size;
    UINT8 addr, data;
    //I2C_OP_ST i2c_operater;
    //DJPEG_DESC_ST ejpeg_cfg;

    sensor->i2c_cfg->salve_id = GC0328C_DEV_ID;

    size = sizeof(gc0328c_init_talbe) / 2;

    for (i = 0; i < size; i++){

        addr = gc0328c_init_talbe[i][0];
        data = gc0328c_init_talbe[i][1];
        camera_intf_sccb_write(addr, data);
    }

    gc0328c_camera_inf_cfg_ppi(CMPARAM_GET_PPI(sensor->ejpeg_cfg->sener_cfg));
    gc0328c_camera_inf_cfg_fps(CMPARAM_GET_FPS(sensor->ejpeg_cfg->sener_cfg));

    os_printf("GC0328C initialization finished.\r\n");


}

void gc0328c_camera_inf_cfg_ppi(UINT32 ppi_type){

    UINT32 i, size;
    UINT8 addr, data;

    os_printf("Setting PPI: %d\r\n", ppi_type);

    switch (ppi_type){
            
        case QVGA_320_240:
            size = sizeof(gc0328c_QVGA_320_240_talbe) / 2;
            for (i = 0; i < size; i++)
            {
                addr = gc0328c_QVGA_320_240_talbe[i][0];
                data = gc0328c_QVGA_320_240_talbe[i][1];
                camera_intf_sccb_write(addr, data);
            }
            break;

        case VGA_640_480:
            size = sizeof(gc0328c_VGA_640_480_talbe) / 2;
            for (i = 0; i < size; i++)
            {
                addr = gc0328c_VGA_640_480_talbe[i][0];
                data = gc0328c_VGA_640_480_talbe[i][1];
                camera_intf_sccb_write(addr, data);
            }
            break;

        default:
            os_printf("set PPI unknown\r\n");
            break;
    }
}

void gc0328c_camera_inf_cfg_fps(UINT32 fps_type){

    UINT32 i, size;
    UINT8 addr, data;

    os_printf("Setting FPS: %d\r\n", fps_type);

    switch (fps_type){
        
        case TYPE_5FPS:
            size = sizeof(gc0328c_5pfs_talbe) / 2;
            for (i = 0; i < size; i++)
            {
                addr = gc0328c_5pfs_talbe[i][0];
                data = gc0328c_5pfs_talbe[i][1];
                camera_intf_sccb_write(addr, data);
            }
            break;

        case TYPE_10FPS:
            size = sizeof(gc0328c_10pfs_talbe) / 2;
            for (i = 0; i < size; i++)
            {
                addr = gc0328c_10pfs_talbe[i][0];
                data = gc0328c_10pfs_talbe[i][1];
                camera_intf_sccb_write(addr, data);
            }
            break;

        case TYPE_20FPS:
            size = sizeof(gc0328c_20pfs_talbe) / 2;
            for (i = 0; i < size; i++)
            {
                addr = gc0328c_20pfs_talbe[i][0];
                data = gc0328c_20pfs_talbe[i][1];
                camera_intf_sccb_write(addr, data);
            }
            break;

        default:
            os_printf("set FPS unknown\r\n");
            break;
    }
}
