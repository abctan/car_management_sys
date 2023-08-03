#ifndef __DRV_SHELL_PORT_H__
#define __DRV_SHELL_PORT_H__

#include "shell.h"
#include "types.h"

int drv_shell_init(void);
void drv_shell_destroy(void);
void drv_shell_signal_handler(int signal);
void drv_shell_run(void);

#endif