#ifndef __COM_SYS_ATTR_H
#define __COM_SYS_ATTR_H

#include "types.h"


typedef enum {
    ONLINE,
    OFFLINE,
    STATUS_BUFF
} status_e;


/* 车库属性 */
typedef struct tag_garage {
    car_gather_t car_gather;  // 具体入库存描述
    unsigned int count;       // 车库总数量
} garage_t;

/* 汽车销售管理系统基本属性 */
typedef struct tag_sell_sys {
    // 车库系统
    garage_t garage;
    // 销售系统
    // 用户系统

} sell_sys_t;

#endif // !__COM_SYS_ATTR_H