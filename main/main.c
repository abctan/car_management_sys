#include "drv_sys.h"

/**
 * @brief main主入口
 * @param argc 
 * @param argv 
 * @return 
 */
int main(int argc, char **argv)
{
    int ret = drv_sys_init(argc, argv);

    // 事件

    drv_sys_deinit();

    return SUCCESS;
}