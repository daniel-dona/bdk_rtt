#include <stdint.h>
/*
 * File      : main.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-5-30      Bernard      the first version
 */

#include "rtthread.h"
#if defined(RT_USING_DFS_ROMFS)
#include <dfs_fs.h>
#endif

#include "include.h"
#include "driver_pub.h"
#include "func_pub.h"
//#include "app.h"
//#include "ate_app.h"
#include "shell.h"
#include <fal.h>
#include "rt_ota.h"
#include "sys_ctrl_pub.h"
#include "sdcard.h"
#include "saradc_intf.h"

extern const struct romfs_dirent romfs_root;
#define DFS_ROMFS_ROOT          (&romfs_root) 

extern int rt_hw_flash_disk_readonly_init(const char *name, uint32_t base, uint32_t sector_size, uint32_t capacity);

extern void saradc_config_vddram_voltage(uint32_t vol);
extern void app_pre_start(void);
extern void app_start(void); 

void mount_fs(){

    /* mount ROMFS as root directory */

    #if defined(RT_USING_DFS_ROMFS)
        if (dfs_mount(RT_NULL, "/", "rom", 0, (const void *)DFS_ROMFS_ROOT) == 0)
        {
            rt_kprintf("ROMFS File System initialized!\n");
        }
        else
        {
            rt_kprintf("ROMFS File System initialized Failed!\n");
        }
    #endif

    #if 1
        /* mount sd card fat partition 1 as root directory */
        saradc_config_vddram_voltage(PSRAM_VDD_3_3V);

        if(dfs_mount("sd0", "/sd", "elm", 0, 0) == 0)
            rt_kprintf("SD File System initialized!\n");
        else
            rt_kprintf("SD File System initialzation failed!\n");
    
    #endif

    #if 0
        const struct fal_partition *dl_part = RT_NULL;

        if ((dl_part = fal_partition_find("app")) != RT_NULL)
        {
            /* dump current firmware version. */
            rt_kprintf("current image name: %s, version: %s, timestamp: %d \n", rt_ota_get_fw_dest_part_name(dl_part), rt_ota_get_fw_version(dl_part), rt_ota_get_fw_timestamp(dl_part));

            rt_hw_flash_disk_readonly_init("flash0", dl_part->offset + 96, 512, dl_part->len - 1024);
            /* mount sd card fat partition 1 as root directory */
            if(dfs_mount("flash0", "/flash0", "elm", 0, 0) == 0)
                rt_kprintf("FLASH File System initialized!\n");
            else
                rt_kprintf("FLASH File System initialzation failed!\n");
        }
        else
        {
            rt_kprintf("not found %s partition \n", RT_BK_DL_PART_NAME);
        }

    #endif
    
}

int main(int argc, char **argv){

    // Old main funcs, need cleanup
    app_pre_start();

    rt_kprintf("\r\n[+++] Mounting filesystems...\r\n\r\n");

    mount_fs();

    rt_kprintf("\r\n[+++] Running project code...\r\n\r\n");

    // Project main
	app_start(); 

}