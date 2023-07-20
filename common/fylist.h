#ifndef FY_LIST_H
#define FY_LIST_H

#include "types.h"
#include "list.h"

/* 通用链表节点 */
typedef struct {
    void *node;
    struct list_head list;
} fynode_t;

/* 通用链表 */
typedef struct {
    uint size;      // 存数据结构大小
    uint count;     // 存数据个数
    fynode_t head;  // 数据链表
} fylist_t;

typedef void (fylist_op_t)(void *op);

// 创建通用链表句柄
fylist_t *create_fylist(uint size);
// 销毁通用链表句柄
void destroy_fylist(fylist_t *handle);
// 添加数据
int fylist_add_node(fylist_t *handle, void *node);
// 删除数据
int fylist_del_node(fylist_t *handle, void *node);
// 更新数据
int fylist_update_node(fylist_t *handle, void *old, void *new);
// 遍历数据
void fylist_travel(fylist_t *handle, fylist_op_t *op);

#endif