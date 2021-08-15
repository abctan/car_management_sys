#include "common.h"
#include "car.h"

#define MAX 10

int main()
{
    node_car_t head;
    node_car_t *new = NULL;
    node_car_t *tmp = NULL;
    struct list_head *pos = NULL;
    int i;
    int rand;

    INIT_LIST_HEAD(&head.list);

    for (i = 0; i < MAX; ++i) {
        new = create_node_car();
        ERRP(new == NULL, "create node car fail!", goto ERR0);
        add_node_car(new, &head);
    }

    list_for_each(pos, &head.list) {
        tmp = list_entry(pos, node_car_t, list);
        print_node_car(tmp);
    }

    destroy_all_node_car(&head);
    return SUCCESS;
ERR0:
    destroy_all_node_car(&head);
    return FAILURE;
}