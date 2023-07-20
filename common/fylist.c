#include "fylist.h"
#include "common.h"
#include <stdlib.h>
#include <string.h>

fylist_t *create_fylist(uint size)
{
    ERRP(size <= 0, "create fylist size must big 0 !!!", goto ERR0);

    fylist_t *handle = (fylist_t *)malloc(sizeof(fylist_t));
    ERRP(handle == NULL, "malloc fylist handle err !!!", goto ERR0);

    handle->size = size;
    handle->count = 0;
    handle->head.node = NULL;
    INIT_LIST_HEAD(&handle->head.list);

    return handle;
ERR0:
    return NULL;
}

void destroy_fylist(fylist_t *handle)
{
    ERRP(handle == NULL, "fylist handle is null !!!", goto ERR0);

    fynode_t *pos = NULL;
    fynode_t *next = NULL;
    list_for_each_entry_safe(pos, next, &handle->head.list, list) {
        free(pos->node);
        list_del(&pos->list);
        free(pos);
    }
    handle->count = 0;
    free(handle);
ERR0:
    return;
}

int fylist_add_node(fylist_t *handle, void *node)
{
    ERRP(handle == NULL, "fylist handle is null !!!", goto ERR0);
    ERRP(node == NULL, "node is null !!!", goto ERR0);

    fynode_t *fynode = (fynode_t *)malloc(sizeof(fynode_t));
    ERRP(fynode == NULL, "malloc list err !!!", goto ERR0);
    void *new = (void *)malloc(handle->size);
    ERRP(new == NULL, "malloc new node err !!!", goto ERR1);

    memcpy(new, node, handle->size);
    fynode->node = new;
    list_add_tail(&fynode->list, &handle->head.list);
    handle->count++;

    return SUCCESS;
ERR1:
    free(fynode);
ERR0:
    return FAILURE;
}

int fylist_del_node(fylist_t *handle, void *node)
{
    ERRP(handle == NULL, "fylist handle is null !!!", goto ERR0);
    ERRP(node == NULL, "node is null !!!", goto ERR0);
    ERRP(handle->count == 0, "node is zero !!!", goto ERR0);

    fynode_t *pos = NULL;
    fynode_t *next = NULL;

    list_for_each_entry_safe(pos, next, &handle->head.list, list) {
        if (memcmp(pos, node, handle->size) == 0) {
            free(pos->node);
            list_del(&pos->list);
            free(pos);
            handle->count--;
            break;
        }
    }

    ERRP(pos == &handle->head, "del err, not find node !!!", goto ERR0);

    return SUCCESS;
ERR0:
    return FAILURE;
}

int fylist_update_node(fylist_t *handle, void *old, void *new)
{
    ERRP(handle == NULL, "fylist handle is null !!!", goto ERR0);
    ERRP(old == NULL, "old is null !!!", goto ERR0);
    ERRP(new == NULL, "old is null !!!", goto ERR0);

    fynode_t *pos = NULL;
    fynode_t *next = NULL;

    list_for_each_entry_safe(pos, next, &handle->head.list, list) {
        if (memcmp(pos, old, handle->size) == 0) {
            memcpy(pos, new, handle->size);
            break;
        }
    }

    ERRP(pos == &handle->head, "not find old node !!!", goto ERR0);

    return SUCCESS;
ERR0:
    return FAILURE;
}

void fylist_travel(fylist_t *handle, fylist_op_t *op)
{
    ERRP(handle == NULL, "fylist handle is null !!!", goto ERR0);
    ERRP(op == NULL, "print func is null !!!", goto ERR0);

    fynode_t *pos = NULL;

    list_for_each_entry(pos, &handle->head.list, list) {
        op(pos->node);
    }

ERR0:
    return;
}



#if 1

struct student {
    int id;
};

void student_print(void *param)
{
    struct student *stu = (struct student *)param;
    printf("Student id: %d\n", stu->id);
}

int main()
{
    fylist_t *student = NULL;

    student = create_fylist(sizeof(struct student));
    ERRP(student == NULL, "fylist handle is null!!!", goto ERR0);

    struct student stu;

    for (int i = 0; i < 10; i++) {
        // com_rand(0, 100, &stu.id);
        stu.id = i;
        printf("%d\n", stu.id);
        fylist_add_node(student, &stu);
    }

    printf("总个数 %d\n", student->count);

    fylist_travel(student, student_print);

    destroy_fylist(student);

    return SUCCESS;
ERR0:
    return FAILURE;
}

#endif