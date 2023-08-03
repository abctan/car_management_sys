#ifndef __DRV_SYS_H
#define __DRV_SYS_H

#include "types.h"

int drv_sys_init(int argc, char *argv[]);
void drv_sys_deinit(void);
int drv_sys_mln_init(int argc, char *argv[]);
void drv_log_init(void);
void drv_debug_func(void);
void drv_sys_run(void);

#endif