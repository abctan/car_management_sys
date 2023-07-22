#include "common.h"
#include "car.h"
#include "fwlist.h"

#define MAX 10
/*
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
*/

int main()
{
    fwlist_t *fwlist = NULL;
    node_car_t *cat = NULL;

    fwlist = create_fwlist(sizeof(node_car_t));
    ERRP(fwlist == NULL, "create fwlist fail!", goto ERR0);

    for (int i = 0; i < MAX; ++i) {
        cat = create_node_car();
        add_fwlist(cat, fwlist);
    }


    fwlist_travel(print_node_car_data, fwlist);

    destroy_fwlist(fwlist);
    

    return SUCCESS;
ERR0:
    return FAILURE;
}