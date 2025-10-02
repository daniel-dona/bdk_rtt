
/*
    i2c_operater.salve_id = PAS6375_DEV_ID;

    size = sizeof(pas6375_init_table) / 2;

    for (i = 0; i < size; i++)
    {
        addr = pas6375_init_table[i][0];
        data = pas6375_init_table[i][1];
        camera_intf_sccb_write(addr, data);
    }
    CAMERA_INTF_WPRT("PAS6375 init finish\r\n");
*/