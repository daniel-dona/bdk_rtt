#include <stdint.h>
#ifndef _DRV_MODEL_PUB_H_
#define _DRV_MODEL_PUB_H_

#include "typedef.h"

#define DRV_FAILURE                  ((uint32_t)-5)
#define DRV_SUCCESS                  (0)

#define DD_HANDLE_MAGIC_WORD         (0xA5A50000)
#define DD_HANDLE_MAGIC_MASK         (0xFFFF0000)
#define DD_HANDLE_ID_MASK            (0x0000FFFF)

#define DD_HANDLE_UNVALID            ((uint32_t)-1)
#define DD_ID_UNVALID                ((uint32_t)-1)

typedef uint32_t                       DD_HANDLE;

typedef struct _dd_operations_
{
    uint32_t (*open) (uint32_t op_flag);
    uint32_t (*close) (void);
    uint32_t (*read) (char *user_buf, uint32_t count, uint32_t op_flag);
    uint32_t (*write) (char *user_buf, uint32_t count, uint32_t op_flag);
    uint32_t (*control) (uint32_t cmd, void *parm);
} DD_OPERATIONS;

typedef struct _sdd_operations_
{
    uint32_t (*control) (uint32_t cmd, void *parm);
} SDD_OPERATIONS;

typedef enum _DD_OPEN_METHOD_
{
    DD_OPEN_METHOD_ONE_TIME = 0,	// open one time only
    DD_OPEN_METHOD_MUTI_TIME	    // open multi times
} DD_OPEN_METHOD;

/*******************************************************************************
* Function Declarations
*******************************************************************************/
extern uint32_t drv_model_init(void);
extern uint32_t drv_model_uninit(void);
extern DD_HANDLE ddev_open(char *dev_name, uint32_t *status, uint32_t op_flag);
extern uint32_t ddev_close(DD_HANDLE handle);
extern uint32_t ddev_read(DD_HANDLE handle, char *user_buf , uint32_t count, uint32_t op_flag);
extern uint32_t ddev_write(DD_HANDLE handle, char *user_buf , uint32_t count, uint32_t op_flag);
extern uint32_t ddev_control(DD_HANDLE handle, uint32_t cmd, void *param);
extern uint32_t sddev_control(char *dev_name, uint32_t cmd, void *param);
extern uint32_t ddev_register_dev(char *dev_name, DD_OPERATIONS *optr);
extern uint32_t sddev_register_dev(char *dev_name, SDD_OPERATIONS *optr);
extern uint32_t ddev_unregister_dev(char *dev_name);
extern uint32_t sddev_unregister_dev(char *dev_name);

#endif //_DRV_MODEL_PUB_H_

