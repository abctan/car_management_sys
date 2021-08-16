#ifndef __FWLIST_H
#define __FWLIST_H

#include "types.h"
#include "common.h"
#include "list.h"
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    void *data;
    unsigned int frc;
    struct list_head list;
} fwnode_t;

typedef struct {
    unsigned int size;
    unsigned int count;
    fwnode_t head;
    pthread_rwlock_t rwlock; // 读写锁
} fwlist_t;

// 创建框架
fwlist_t* create_fwlist(unsigned int size);
// 销毁框架
void destroy_fwlist(fwlist_t *handle);
// 添加数据
int add_fwlist(void *data, unsigned int count, fwlist_t *handle);
// 删除数据
int del_fwlist(fwnode_t *node, fwlist_t *handle);


#endif // __FWLIST_H