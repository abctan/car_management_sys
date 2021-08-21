#ifndef __CAR_H
#define __CAR_H

#include "types.h"
#include "list.h"
#include <time.h>

#define STRING_MAX_LENGTH 256   // 字符串大小

typedef enum {
    LIMOUSINE,  // 豪华轿车
    TRUCKS,     // 货车
    SPORTSCAR,  // 跑车
    PASSENGER,  // 客车
    TRICYCLE,   // 三轮车
    TWOWHEELER, // 两轮车
    CAR_OTHER,  // 其他
    CAR_BUTT
} car_type_e;

/* 汽车类基本属性 */
typedef struct tag_car {
    char name[STRING_MAX_LENGTH];   // 名称
    color_e color;                  // 颜色
    car_type_e type;                // 类型
    unsigned int speed;             // 速度
    double weight;                  // 重量
    double product_price;           // 生产价格
    time_t product_date;            // 生产日期
} car_t;

/* 车辆节点集合 */
typedef struct tag_node_car {
    car_t car;                  // 车辆基本属性
    unsigned int num;           // 该类型车数量
    bool market;                // 是否销售
    bool factory;               // 是否返厂
    unsigned int sell_price;    // 售价
    time_t push_storage_time;   // 入库时间
    time_t pop_storage_time;    // 出库时间
    struct list_head list;      // 链表操作
} node_car_t;

// 创建一个车辆信息节点
node_car_t* create_node_car(void);
// 销毁一个车辆信息节点
void destroy_node_car(node_car_t *node_car);
void destroy_all_node_car(node_car_t *head);
// 添加一个车辆信息节点
int add_node_car(node_car_t *new, node_car_t *head);
int add_tail_node_car(node_car_t *new, node_car_t *head);
// 从链表删除一个信息节点
int del_node_car(node_car_t *node);
// 更新一个车辆信息节点
int update_node_car(node_car_t *old, node_car_t *new);
// 打印一个节点信息
void print_node_car(node_car_t *node_car);
void print_node_car_data(void *car);

#endif // !__CAR_H