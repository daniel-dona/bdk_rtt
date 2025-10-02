

/*


    i2c_operater.salve_id = OV_7670_DEV_ID;

    size = sizeof(ov_7670_init_table) / 2;

    for (i = 0; i < size; i++)
    {
        addr = ov_7670_init_table[i][0];
        data = ov_7670_init_table[i][1];
        camera_intf_sccb_write(addr, data);
    }
    CAMERA_INTF_WPRT("OV_7670 init finish\r\n");

*/