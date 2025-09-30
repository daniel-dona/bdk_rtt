#include <stdint.h>
#include "include.h"
#include "arm_arch.h"

#if CFG_USE_CAMERA_INTF
//#include "process.h"
#include "llc.h"

#include "video_transfer.h"

#include "jpeg_encoder_pub.h"
#include "i2c_pub.h"

#include "camera_intf.h"
#include "camera_intf_pub.h"

#include "drv_model_pub.h"
#include "general_dma_pub.h"
#include "mem_pub.h"
#include "bk_timer_pub.h"
#include "gpio_pub.h"

#include "uart_pub.h"

#include "sensors/bf2013.h"
#include "sensors/gc0308c.h"
#include "sensors/gc0311.h"
#include "sensors/gc0328c.h"
#include "sensors/hi704.h"
#include "sensors/hm1055.h"
#include "sensors/ov7670.h"
#include "sensors/pas6329.h"
#include "sensors/pas6375.h"

extern void delay100us(int32_t num);

DJPEG_DESC_ST ejpeg_cfg;
TVIDEO_DESC_ST tvideo_st;

DD_HANDLE i2c_hdl = DD_HANDLE_UNVALID, ejpeg_hdl = DD_HANDLE_UNVALID;
I2C_OP_ST i2c_operater;

// General interface functions

void camera_intf_delay_timer_hdl(uint8_t param){
    #if CFG_GENERAL_DMA
    GDMA_CFG_ST en_cfg;
    uint16_t already_len = ejpeg_cfg.rx_read_len;
    uint32_t channel = ejpeg_cfg.dma_channel;
    GLOBAL_INT_DECLARATION();

    if (ejpeg_hdl == DD_HANDLE_UNVALID)
    {
        return;
    }

    //REG_WRITE((0x00802800+(16*4)), 0x02);

    int left_len = sddev_control(GDMA_DEV_NAME, CMD_GDMA_GET_LEFT_LEN, (void *)channel);
    int rec_len = ejpeg_cfg.node_len - left_len;
    uint32_t frame_len = 0;
    frame_len = ddev_control(ejpeg_hdl, EJPEG_CMD_GET_FRAME_LEN, NULL);

    if ((ejpeg_cfg.node_full_handler != NULL) && (rec_len > 0))
    {
        ejpeg_cfg.node_full_handler(ejpeg_cfg.rxbuf + already_len, rec_len, 1, frame_len);
    }

    already_len += rec_len;
    if (already_len >= ejpeg_cfg.rxbuf_len)
    {
        already_len -= ejpeg_cfg.rxbuf_len;
    }

    GLOBAL_INT_DISABLE();
    ejpeg_cfg.rx_read_len = already_len;
    GLOBAL_INT_RESTORE();

    // turn off dma, so dma can start from first configure. for easy handler
    en_cfg.channel = ejpeg_cfg.dma_channel;
    en_cfg.param = 0;
    sddev_control(GDMA_DEV_NAME, CMD_GDMA_SET_DMA_ENABLE, &en_cfg);

    ejpeg_cfg.rx_read_len = 0;
    en_cfg.param = 1;
    sddev_control(GDMA_DEV_NAME, CMD_GDMA_SET_DMA_ENABLE, &en_cfg);
    #endif

    if ((ejpeg_cfg.data_end_handler))
    {
        ejpeg_cfg.data_end_handler();
    }

    channel = EJPEG_DELAY_HTIMER_CHNAL;
    sddev_control(TIMER_DEV_NAME, CMD_TIMER_UNIT_DISABLE, &channel);

    //REG_WRITE((0x00802800+(16*4)), 0x00);
}

static void camera_intf_start_delay_timer(void){
    timer_param_t param;

    if (ejpeg_hdl == DD_HANDLE_UNVALID)
    {
        return;
    }
    //REG_WRITE((0x00802800+(16*4)), 0x02);

    param.channel = EJPEG_DELAY_HTIMER_CHNAL;
    param.div = 1; // WTF
    param.period = EJPEG_DELAY_HTIMER_VAL;
    param.t_Int_Handler = camera_intf_delay_timer_hdl;

    sddev_control(TIMER_DEV_NAME, CMD_TIMER_INIT_PARAM, &param);

    //REG_WRITE((0x00802800+(16*4)), 0x00);
}

static void camera_intf_ejpeg_rx_handler(uint32_t dma){
    uint16_t already_len = ejpeg_cfg.rx_read_len;
    uint16_t copy_len = ejpeg_cfg.node_len;
    GLOBAL_INT_DECLARATION();

    if (ejpeg_hdl == DD_HANDLE_UNVALID)
    {
        return;
    }

    //REG_WRITE((0x00802800+(17*4)), 0x02);

    if (ejpeg_cfg.node_full_handler != NULL)
    {
        ejpeg_cfg.node_full_handler(ejpeg_cfg.rxbuf + already_len, copy_len, 0, 0);
    }

    already_len += copy_len;

    if (already_len >= ejpeg_cfg.rxbuf_len)
    {
        already_len = 0;
    }

    GLOBAL_INT_DISABLE();
    ejpeg_cfg.rx_read_len = already_len;
    GLOBAL_INT_RESTORE();

    //REG_WRITE((0x00802800+(17*4)), 0x00);
}

static void camera_intf_ejpeg_end_handler(void){
    camera_intf_start_delay_timer();
}

static void camera_intf_init_ejpeg_pixel(uint32_t ppi_type){
    switch (ppi_type)
    {
    case QVGA_320_240:
        ejpeg_cfg.x_pixel = X_PIXEL_320;
        ejpeg_cfg.y_pixel = Y_PIXEL_240;
        break;

    case VGA_640_480:
        ejpeg_cfg.x_pixel = X_PIXEL_640;
        ejpeg_cfg.y_pixel = Y_PIXEL_480;
        break;

    case VGA_800_600:
        ejpeg_cfg.x_pixel = X_PIXEL_800;
        ejpeg_cfg.y_pixel = Y_PIXEL_600;
        break;

    case VGA_1280_720:
        ejpeg_cfg.x_pixel = X_PIXEL_1280;
        ejpeg_cfg.y_pixel = Y_PIXEL_720;
        break;

    default:
        os_printf("cm PPI unknown, use QVGA\r\n");
        ejpeg_cfg.x_pixel = X_PIXEL_640;
        ejpeg_cfg.y_pixel = Y_PIXEL_480;
        break;
    }
}

static void camera_intf_config_ejpeg(void *data){
    os_memset(&ejpeg_cfg, 0, sizeof(DJPEG_DESC_ST));
    os_memcpy(&ejpeg_cfg, data, sizeof(TVIDEO_DESC_ST));

    camera_intf_init_ejpeg_pixel(CMPARAM_GET_PPI(ejpeg_cfg.sener_cfg));

    ejpeg_cfg.start_frame_handler = NULL;
    ejpeg_cfg.end_frame_handler = camera_intf_ejpeg_end_handler;

    #if CFG_GENERAL_DMA
    ejpeg_cfg.dma_rx_handler = camera_intf_ejpeg_rx_handler;
    ejpeg_cfg.dma_channel = GDMA_CHANNEL_4;
    #endif
}

void camera_intf_sccb_write(uint8_t addr, uint8_t data)
{
    unsigned int status;
    unsigned int err_count = 0;
    i2c_operater.op_addr = addr;
    i2c_operater.addr_width = ADDR_WIDTH_8;
    do
    {
        status = ddev_write(i2c_hdl, (char *)&data, 1, (uint32_t)&i2c_operater);
        if (err_count++ > I2C_WIRTE_TIMEOUT_COUNT)
        {
            break;
        }
    }
    while (status != 0);

}

void camera_intf_sccb_read(uint8_t addr, uint8_t *data)
{
    unsigned int status;
    i2c_operater.op_addr = addr;
    i2c_operater.addr_width = ADDR_WIDTH_8;
    do
    {
        status = ddev_read(i2c_hdl, (char *)data, 1, (uint32_t)&i2c_operater);
    }
    while (status != 0);
}

uint8_t camera_intf_sccb_write2(uint8_t device_addr, uint8_t register_addr, uint8_t *data, uint8_t len){

    uint8_t status;
    i2c_operater.salve_id = device_addr;
    i2c_operater.op_addr = register_addr;
    i2c_operater.addr_width = ADDR_WIDTH_8;

    status = ddev_write(i2c_hdl, (char *)data, (uint32_t)len, (uint32_t)&i2c_operater);

    if(status != 0){
        os_printf("Unable to write I2C.\r\n");
    }

    return status;

}

uint8_t camera_intf_sccb_read2(uint8_t device_addr, uint8_t register_addr, uint8_t *data, uint8_t len){
    uint8_t status;
    i2c_operater.salve_id = device_addr;
    i2c_operater.op_addr = register_addr;
    i2c_operater.addr_width = ADDR_WIDTH_8;

    status = ddev_read(i2c_hdl, (char *)data, (uint32_t)len, (uint32_t)&i2c_operater);

    if(status != 0){
        os_printf("Unable to read I2C.\r\n");
    }

    return status;

}

/* None of the sensors I can test use 16 bit I2C addresses

#else
void camera_intf_sccb_write(uint16_t addr, uint8_t data)
{
    unsigned int status;
    unsigned int err_count = 0;
    i2c_operater.op_addr = addr;
    i2c_operater.addr_width = ADDR_WIDTH_16;
    do
    {
        status = ddev_write(i2c_hdl, (char *)&data, 1, (uint32_t)&i2c_operater);
        if (err_count++ > I2C_WIRTE_TIMEOUT_COUNT)
        {
            break;
        }
    }
    while (status != 0);

}

void camera_intf_sccb_read(uint16_t addr, uint8_t *data)
{
    unsigned int status;
    i2c_operater.op_addr = addr;
    i2c_operater.addr_width = ADDR_WIDTH_16;
    do
    {
        status = ddev_read(i2c_hdl, (char *)data, 1, (uint32_t)&i2c_operater);
    }
    while (status != 0);
}
#endif

*/

void init_camera_resetpin(void)
{
    //bk_gpio_config_output(CAMERA_RESET_GPIO_INDEX);
    //bk_gpio_output(CAMERA_RESET_GPIO_INDEX, CAMERA_RESET_HIGH_VAL);
}

void camera_reset(void)
{
    //bk_gpio_output(CAMERA_RESET_GPIO_INDEX, CAMERA_RESET_HIGH_VAL);
    //delay100us(10);                                                   // 1ms
    //bk_gpio_output(CAMERA_RESET_GPIO_INDEX, CAMERA_RESET_LOW_VAL);
    //delay100us(10);                                                   // 1=1ms,
    //bk_gpio_output(CAMERA_RESET_GPIO_INDEX, CAMERA_RESET_HIGH_VAL);
    //delay100us(10);                                                   // 1ms
    //CAMERA_INTF_WPRT("Camera Reset\r\n");
}


/*---------------------------------------------------------------------------*/

void camera_intfer_init(void *ejpeg_config, camera_sensor_t *sensor){

    uint32_t status;

    camera_intf_config_ejpeg(ejpeg_config);

    ejpeg_hdl = ddev_open(EJPEG_DEV_NAME, &status, (uint32_t)&ejpeg_cfg);
    
    //camera_reset();

    if(sensor->i2c_bus == (char*) &I2C2_DEV_NAME){

        uint32_t i2c2_trans_mode = (0 & (~I2C2_MSG_WORK_MODE_MS_BIT)// master
                                & (~I2C2_MSG_WORK_MODE_AL_BIT))// 7bit address
                                | (I2C2_MSG_WORK_MODE_IA_BIT); // with inner address

        i2c_hdl = ddev_open(I2C2_DEV_NAME, &status, i2c2_trans_mode);

        bk_printf("open I2C2\r\n");

    }else{

        i2c_hdl = ddev_open(I2C1_DEV_NAME, &status, 0);

        bk_printf("open I2C1\r\n");
        
    }

    
    /*{
        extern void uart_hw_uninit(uint8_t uport);
        // disable uart temporarily
        uart_hw_uninit(1);
    }*/
    

    /*

    In case I2C1 is used, to be tested!!

    uint32_t oflag = 0;
    i2c_hdl = ddev_open(I2C1_DEV_NAME, &status, oflag);
    bk_printf("open I2C1\r\n");
    #endif*/

    //camera_intf_config_senser();

    sensor->i2c_cfg = &i2c_operater;
    sensor->ejpeg_cfg = &ejpeg_cfg;

    sensor->init(i2c_hdl, ejpeg_hdl, sensor);

    os_printf("camera_intfer_init,%p-%p\r\n", ejpeg_hdl, i2c_hdl);
}

void camera_intfer_deinit(camera_sensor_t *sensor){
    GLOBAL_INT_DECLARATION();
    os_printf("camera_intfer_deinit,%p-%p\r\n", ejpeg_hdl, i2c_hdl);

    ddev_close(ejpeg_hdl);
    ddev_close(i2c_hdl);

    GLOBAL_INT_DISABLE();
    ejpeg_hdl = i2c_hdl = DD_HANDLE_UNVALID;
    GLOBAL_INT_RESTORE();

    os_memset(&ejpeg_cfg, 0, sizeof(DJPEG_DESC_ST));
}

camera_sensor_t* camera_detect(){

    uint32_t status;

    camera_intf_config_ejpeg(&tvideo_st);

    ejpeg_hdl = ddev_open(EJPEG_DEV_NAME, &status, (uint32_t)&ejpeg_cfg);
    
    //camera_reset();

    uint32_t i2c2_trans_mode = (0 & (~I2C2_MSG_WORK_MODE_MS_BIT)// master
                              & (~I2C2_MSG_WORK_MODE_AL_BIT))// 7bit address
                             | (I2C2_MSG_WORK_MODE_IA_BIT); // with inner address

    i2c_hdl = ddev_open(I2C2_DEV_NAME, &status, i2c2_trans_mode);

    os_printf("Searching for camera sensors, using I2C2 bus...\r\n");

    camera_sensor_t* sensor = malloc(sizeof(camera_sensor_t));

    sensor->i2c_bus = I2C2_DEV_NAME;


    if(gc0328c_sensor_detect()){

        sensor->name = rt_strdup("GalaxyCore 328C");
        sensor->init = gc0328c_sensor_init;

    }else if (gc0311_sensor_detect()){

        sensor->name = rt_strdup("GalaxyCore 311");
        sensor->init = gc0311_sensor_init;

    }else if (hi704_sensor_detect()){

        sensor->name = rt_strdup("Hynix 704");
        sensor->init = hi704_sensor_init;

    }else{
        /*sensor->name = rt_strdup("None");
        sensor->init = hi704_sensor_init;*/
        os_printf("No compatible sensor found!\r\n");
        free(sensor);
        sensor = NULLPTR;
    }
    

    //GLOBAL_INT_DECLARATION();
    //os_printf("camera_intfer_deinit,%p-%p\r\n", ejpeg_hdl, i2c_hdl);

    


    if(sensor == NULLPTR){

        ddev_close(i2c_hdl);

        uint32_t i2c1_trans_mode = 0;

        i2c_hdl = ddev_open(I2C1_DEV_NAME, &status, i2c1_trans_mode);

        os_printf("Searching for camera sensors, using I2C1 bus...\r\n");

        sensor = malloc(sizeof(camera_sensor_t));

        sensor->i2c_bus = I2C1_DEV_NAME;

        if(gc0328c_sensor_detect()){

            sensor->name = rt_strdup("GalaxyCore 328C");
            sensor->init = gc0328c_sensor_init;

        }else if (gc0311_sensor_detect()){

            sensor->name = rt_strdup("GalaxyCore 311");
            sensor->init = gc0311_sensor_init;

        }else if (hi704_sensor_detect()){

            sensor->name = rt_strdup("Hynix 704");
            sensor->init = hi704_sensor_init;

        }else{
            os_printf("No compatible sensor found!\r\n");
            free(sensor);
            sensor = NULLPTR;
        }

    }
    

    GLOBAL_INT_DECLARATION();
    //os_printf("camera_intfer_deinit,%p-%p\r\n", ejpeg_hdl, i2c_hdl);

    ddev_close(ejpeg_hdl);
    ddev_close(i2c_hdl);

    GLOBAL_INT_DISABLE();
    ejpeg_hdl = i2c_hdl = DD_HANDLE_UNVALID;
    GLOBAL_INT_RESTORE();

    return sensor;
}

/*uint32_t camera_intfer_set_video_param(uint32_t ppi_type, uint32_t pfs_type)
{
    #if (USE_CAMERA == GC0328C_DEV)
    if (ejpeg_hdl == DD_HANDLE_UNVALID)
    {
        return 1;
    }

    if (ppi_type < PPI_MAX)
    {
        uint32_t param;
        camera_intf_init_ejpeg_pixel(ppi_type);

        param = ejpeg_cfg.x_pixel;
        ddev_control(ejpeg_hdl, EJPEG_CMD_SET_X_PIXEL, &param);

        param = ejpeg_cfg.y_pixel;
        ddev_control(ejpeg_hdl, EJPEG_CMD_SET_Y_PIXEL, &param);

        camera_inf_cfg_gc0328c_ppi(ppi_type);
    }

    if (pfs_type < FPS_MAX)
    {
        camera_inf_cfg_gc0328c_fps(pfs_type);
    }
    #endif
    return 0;

}*/
/*---------------------------------------------------------------------------*/

#endif // CFG_USE_CAMERA_INTF
