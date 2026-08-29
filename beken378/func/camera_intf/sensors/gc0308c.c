
/*



    i2c_operater.salve_id = GC0308C_DEV_ID;

    size = sizeof(gc0308c_init_talbe) / 2;

    for (i = 0; i < size; i++)
    {
        addr = gc0308c_init_talbe[i][0];
        data = gc0308c_init_talbe[i][1];
        camera_intf_sccb_write(addr, data);
    }
    CAMERA_INTF_WPRT("GC0308C init finish\r\n");

*/