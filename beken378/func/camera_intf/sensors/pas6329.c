
/*

    i2c_operater.salve_id = PAS6329_DEV_ID;

    size = sizeof(pas6329_page0) / 2;
    PAS6329_SET_PAGE0;

    for (i = 0; i < size; i++)
    {
        addr = pas6329_page0[i][0];
        data = pas6329_page0[i][1];
        camera_intf_sccb_write(addr, data);
    }

    size = sizeof(pas6329_page1) / 2;
    PAS6329_SET_PAGE1;
    for (i = 0; i < size; i++)
    {
        addr = pas6329_page1[i][0];
        data = pas6329_page1[i][1];
        camera_intf_sccb_write(addr, data);
    }

    size = sizeof(pas6329_page2) / 2;
    PAS6329_SET_PAGE2;
    for (i = 0; i < size; i++)
    {
        addr = pas6329_page2[i][0];
        data = pas6329_page2[i][1];
        camera_intf_sccb_write(addr, data);
    }

    PAS6329_SET_PAGE0;
    CAMERA_INTF_WPRT("PAS6329 init finish\r\n");


*/