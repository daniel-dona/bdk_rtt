/*

    i2c_operater.salve_id = BF_2013_DEV_ID;

    size = sizeof(bf_2013_init_talbe) / 2;

    for (i = 0; i < size; i++)
    {
        addr = bf_2013_init_talbe[i][0];
        data = bf_2013_init_talbe[i][1];
        camera_intf_sccb_write(addr, data);
    }
    CAMERA_INTF_WPRT("BF_2013 init finish\r\n");


*/