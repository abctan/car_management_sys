#include "drv_sys.h"
#include "common.h"
/**
 * @brief main主入口
 * @param argc 
 * @param argv 
 * @return 
 */
int main(int argc, char **argv)
{
    int ret = drv_sys_init(argc, argv);
    ERRP(ret != SUCCESS, "init error", goto ERR0);

    // 事件
    drv_sys_run();

    drv_sys_deinit();

    return SUCCESS;
ERR0:
    return FAILURE;
}