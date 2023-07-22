#include "car.h"
#include "common.h"
#include <stdlib.h>

#ifndef DEBUG

#define DEBUG   // 调试

#endif

static car_t g_car_base_defconfig[] = {
    { "car_def_1", RED, SPORTSCAR, 100, 200, 150000, 10000000 },
    { "car_def_2", CYAN, SPORTSCAR, 100, 200, 150000, 10000000 },
    { "car_def_3", ORANGE, SPORTSCAR, 100, 200, 150000, 10000000 },
    { "car_def_4", BLUE, SPORTSCAR, 100, 200, 150000, 10000000 },
    { "car_def_5", ORANGE, SPORTSCAR, 100, 200, 150000, 10000000 },
    { "car_def_6", VIOLET, SPORTSCAR, 100, 200, 150000, 10000000 },
};

static char g_color[COLOR_BUTT][12] = {
    "红色",
    "橙色",
    "黄色",
    "绿色",
    "青色",
    "蓝色",
    "紫色",
};

static char g_car_type[CAR_BUTT][20] = {
    "豪华轿车",
    "货车",
    "跑车",
    "客车",
    "三轮车",
    "两轮车",
    "其他车"
};

static char g_bool_string[][12] = {
    "否", "是"
};

static void init_def_node_car(node_car_t* node_car)
{
    int index;

    ERRP(node_car == NULL, "node is null!!!", goto ERR0);

    // get rand index value
    com_rand(0, ARRAY_SIZE(g_car_base_defconfig) - 1, &index);
#ifdef DEBUG
    PRI_D(index);
#endif // DEBUG
    memcpy(&node_car->car, &g_car_base_defconfig[index], sizeof(car_t));
    node_car->num               = 1;
    node_car->market            = TRUE;
    node_car->factory           = FALSE;
    node_car->sell_price        = node_car->car.product_price + 10000;
    node_car->push_storage_time = node_car->car.product_date;
    node_car->pop_storage_time  = node_car->car.product_date;

    // list init
    INIT_LIST_HEAD(&node_car->list);

ERR0:
    return;
}

node_car_t* create_node_car(void)
{
    node_car_t *new = NULL;

    new = (node_car_t*)malloc(sizeof(node_car_t));
    ERRP(new == NULL, "create node_car_t node fail!", goto ERR0);

    init_def_node_car(new);

    return new;
ERR0:
    return NULL;
}

void destroy_node_car(node_car_t *node_car)
{
    ERRP(node_car == NULL, "group_car node is null!", goto ERR0);

    list_del(&node_car->list);
    free(node_car);

ERR0:
    return;    
}

void destroy_all_node_car(node_car_t *head)
{
    node_car_t *node = NULL;
    struct list_head *pos = NULL;
    struct list_head *pos_next = NULL;

    list_for_each_safe(pos, pos_next, &head->list) {
        node = list_entry(pos, node_car_t, list);
        destroy_node_car(node);
        node = NULL;
    }

    return;
}

int add_node_car(node_car_t *new, node_car_t *head)
{
    ERRP((new == NULL || head == NULL), "add_node_car func param is null!", goto ERR0);

    list_add(&new->list, &head->list);
    return SUCCESS;
ERR0:
    return FAILURE;    
}

int add_tail_node_car(node_car_t *new, node_car_t *head)
{
    ERRP((new == NULL || head == NULL), "add_tail_node_car func param is null!", goto ERR0);

    list_add_tail(&new->list, &head->list);
    return SUCCESS;
ERR0:
    return FAILURE;
}

int del_node_car(node_car_t *node)
{
    ERRP(node == NULL, "del_node_car func param is null!", goto ERR0);

    if (!(--node->num)) {
        list_del(&node->list);
    }

    return SUCCESS;
ERR0:
    return FAILURE;    
}

int update_node_car(node_car_t *old, node_car_t *new)
{
    ERRP((old == NULL || new == NULL), "update_node_car func param is null!", goto ERR0);

    memcpy(&old->car, &new->car, sizeof(car_t));
    old->num               = new->num;
    old->market            = new->market;
    old->factory           = new->sell_price;
    old->push_storage_time = new->push_storage_time;
    old->pop_storage_time  = new->pop_storage_time;

    return SUCCESS;
ERR0:
    return FAILURE;      
}

void print_node_car(node_car_t *node)
{
//     ERRP(node == NULL, "print_node_car func param is null!", goto ERR0);

//     printf("---------base----------\n");
//     printf("名称: %s, 颜色: %s, 类型: %s, 速度: %d, 重量: %0.2f, 生产价格: %0.2f, 生产日期: %f\n",
//            node->car.name, g_color[node->car.color], g_car_type[node->car.type], node->car.speed,
//            node->car.weight, node->car.product_price, node->car.product_date);
//     printf("---------other---------\n");
//     printf("数量: %d, 销售: %s, 返厂: %s, 售价: %d, 入库时间: %f, 出库时间: %f\n",
//            node->num, g_bool_string[node->market], g_bool_string[node->factory],
//            node->sell_price, node->push_storage_time, node->pop_storage_time);
//     printf("\n");

// ERR0:
//     return; 
}

void print_node_car_data(void *car)
{
//     node_car_t *node = NULL;

//     ERRP(car == NULL, "print_node_car func param is null!", goto ERR0);

//     node = (node_car_t *)car;

//     printf("---------base----------\n");
//     printf("名称: %s, 颜色: %s, 类型: %s, 速度: %d, 重量: %0.2f, 生产价格: %0.2f, 生产日期: %d\n",
//            node->car.name, g_color[node->car.color], g_car_type[node->car.type], node->car.speed,
//            node->car.weight, node->car.product_price, node->car.product_date);
//     printf("---------other---------\n");
//     printf("数量: %d, 销售: %s, 返厂: %s, 售价: %d, 入库时间: %d, 出库时间: %d\n",
//            node->num, g_bool_string[node->market], g_bool_string[node->factory],
//            node->sell_price, node->push_storage_time, node->pop_storage_time);
//     printf("\n");

// ERR0:
//     return; 
}
#include "mln_core.h"
#include "mln_log.h"
#include "elog.h"
int main()
{
    /* close printf buffer */
    setbuf(stdout, NULL);
    /* initialize EasyLogger */
    elog_init();
    /* set EasyLogger log format */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
#ifdef ELOG_COLOR_ENABLE
    elog_set_text_color_enabled(true);
#endif
    /* start EasyLogger */
    elog_start();
    log_a("Hello EasyLogger!");
    log_e("Hello EasyLogger!");
    log_w("Hello EasyLogger!");
    log_i("Hello EasyLogger!");
    log_d("Hello EasyLogger!");
    log_v("Hello EasyLogger!");

    return 0;
}

