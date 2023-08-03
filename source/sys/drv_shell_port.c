#include "drv_shell_port.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

SHELL_TypeDef g_shell;

SHELL_TypeDef *get_shell_ctrl()
{
    return &g_shell;
}

/**
 * @brief shell读取数据函数原型
 * 
 * @param char shell读取的字符
 * 
 * @return char 0 读取数据成功
 * @return char -1 读取数据失败
 */
signed char userShellRead(char *data)
{
    *data = getchar();
    return 0;
}

/**
 * @brief shell写数据函数原型
 * 
 * @param const char 需写的字符
 */
void userShellWrite(const char data)
{
    putchar(data);
}

static int shellExit(int value)
{
    system("stty icanon");
    system("stty echo");
    return value;
}

void drv_shell_signal_handler(int signal)
{
    shellExit(0);
}

int drv_shell_init(void)
{
    SHELL_TypeDef *shell = get_shell_ctrl();

    system("stty -echo");
    system("stty -icanon");

    shell->read  = userShellRead;
    shell->write = userShellWrite;

    shellInit(shell);
 
    return SUCCESS;
}

void drv_shell_destroy(void)
{
    shellExit(0);
    return;
}

void drv_shell_run(void)
{
    SHELL_TypeDef *shell = get_shell_ctrl();
    shellTask(shell);
}
