#include <stdint.h>
/*

    i2c_operater.salve_id = HM_1055_DEV_ID;

    size = sizeof(hm_1055_init_table) / 4;

    for (i = 0; i < size; i++)
    {
        uint16_t addr1;
        addr1 = hm_1055_init_table[i][0];
        data = hm_1055_init_table[i][1];
        addr = addr;
        camera_intf_sccb_write(addr1, data);
    }
    CAMERA_INTF_WPRT("HM_1055 init finish\r\n");

*/