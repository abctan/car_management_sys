#include "fwlist.h"

fwlist_t* create_fwlist(unsigned int size)
{
    fwlist_t *handle = NULL;
    fwnode_t *head = NULL;

    ERRP(size <= 0, "create param must big 0 !!!", goto ERR0);

    handle = (fwlist_t*)malloc(sizeof(fwlist_t));
    ERRP(handle == NULL, "malloc fwlist handle fail !", goto ERR0);
    head = &handle->head;

    handle->size = size;
    handle->count = 1;
    pthread_rwlock_init(&handle->rwlock, NULL);
    head->data = NULL;
    head->frc = 0;
    INIT_LIST_HEAD(&head->list); // init list

    return handle;
ERR0:
    return NULL;
}

void destroy_fwlist(fwlist_t *handle)
{
    fwnode_t *head = NULL;
    fwnode_t *tmp = NULL;
    struct list_head *pos = NULL;
    struct list_head *pos_next = NULL;

    ERRP(handle == NULL, "destroy_fwlist param is null !!!", goto ERR0);

    head = &handle->head;
    list_for_each_safe(pos, pos_next, &head->list) {
        list_del(pos);
        tmp = list_entry(pos, fwnode_t, list);
        free(tmp->data);
        free(tmp);
        tmp = NULL;
    }

    free(handle);
    pthread_rwlock_destroy(&handle->rwlock);
ERR0:
    return;        
}

int add_fwlist(void *data, unsigned int count, fwlist_t *handle)
{
    fwnode_t *node = NULL;

    ERRP((data == NULL || handle == NULL), "add_fwlist param is null !!!", goto ERR0);

    node = (fwnode_t *)malloc(sizeof(fwnode_t));
    ERRP(node == NULL, "malloc node fail !!!", goto ERR0);

    pthread_rwlock_wrlock(&handle->rwlock);
    node->data = data;
    node->frc = (count > 0) ? count : 1;
    list_add(&node->list, &handle->head.list);
    handle->count += node->frc;
    pthread_rwlock_unlock(&handle->rwlock);

    return SUCCESS;
ERR0:
    return FAILURE;
}

int del_fwlist(fwnode_t *node, fwlist_t *handle)
{
    int empty;

    ERRP((node == NULL || handle == NULL), "del_fwlist param is null !!!", goto ERR0);

    empty = list_empty(&handle->head.list);
    ERRP(empty, "fwlist node is empty!", goto ERR0);

    pthread_rwlock_wrlock(&handle->rwlock);
    if (!(--node->frc)) {
        list_del(&node->list);
        free(node->data);
        free(node);
    }
    --handle->count;
    pthread_rwlock_unlock(&handle->rwlock);

    return SUCCESS;
ERR0:
    return FAILURE;
}