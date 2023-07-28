#include "drv_db.h"
#include "common.h"
#include "elog.h"
#include <stdio.h>

static drv_db_t g_drv_db = {0};

drv_db_t *get_db_ctrl(void)
{
    return &g_drv_db;
}

static int drv_db_add_history(void *data, int lenght)
{
    drv_db_t *ctx = get_db_ctrl();

    int ret = mln_queue_full(ctx->history.queue);
    if (ret != 0) {
        void *old = mln_queue_get(ctx->history.queue);
        mln_queue_remove(ctx->history.queue);
        ctx->history.attr.free_handler(old);
    }

    void *new = malloc(sizeof(void) * lenght);
    ERRP(new == NULL, "malloc error", goto ERR0);

    memcpy(new, data, lenght);
    mln_queue_append(ctx->history.queue, new);

    return SUCCESS;
ERR0:
    return FAILURE;
}

static int drv_db_exec(const char *sql, int (*callback)(void*, int, char**, char**), void *call_param)
{
    drv_db_t *ctx = get_db_ctrl();
    int ret = sqlite3_exec(ctx->db, sql, callback, call_param, &ctx->db_errmsg);
    ERRP(ret != SQLITE_OK, ctx->db_errmsg, goto ERR0);
    drv_db_add_history((void *)sql, strlen(sql) + 1);
    return ret;
ERR0:
    sqlite3_free(ctx->db_errmsg);
    return ret;
}

int drv_db_init(void)
{
    drv_db_t *ctx = get_db_ctrl();

    ctx->db_path = SQLFILE_PATH;
    ctx->history.attr.qlen = DB_HISTORY_MAX_LEN;
    ctx->history.attr.free_handler = free;
    ctx->history.queue = mln_queue_init(&ctx->history.attr);
    ERRP(ctx->history.queue == NULL, "history init err", goto ERR0);

    int ret = sqlite3_open_v2(ctx->db_path, &ctx->db, SQLITE_OPEN_READWRITE, NULL);
    if (ret != SQLITE_OK) {
        elog_e("debug", "数据库%s不存在, 初始化数据库!!!", SQLFILE_PATH);
        ret = sqlite3_open_v2(SQLFILE_PATH, &ctx->db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
        ERRP(ret != SQLITE_OK, "初始化数据库失败", goto ERR0);
        ret = drv_db_create_table();
        ERRPGO(ret != SUCCESS, goto ERR0);
        elog_e("debug", "初始化数据库成功!!!");
    }

    drv_db_exec(SQL_INSERT_DEFAULT_USER, NULL, NULL);

    ctx->init = TRUE;

    return SUCCESS;
ERR0:
    return FAILURE;
}

// int pri(void *data, void *param)
// {
//     printf("%s\n", (char *)data);
//     return 0;
// }
// static void debug_print_history()
// {
//     drv_db_t *ctx = get_db_ctrl();

//     mln_queue_iterate(ctx->history.queue, pri, NULL);
// }

void drv_db_destroy(void)
{
    drv_db_t *ctx = get_db_ctrl();

    if (ctx->init != TRUE) {
        return;
    }

    // debug_print_history();

    mln_queue_destroy(ctx->history.queue);
    sqlite3_close_v2(ctx->db);
    ctx->db = NULL;
    ctx->init = FALSE;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");

    if (atoi(argv[0]) == 0) {
        printf("第一次创建数据库\n");
    }

   return 0;
}

int drv_db_check_is_has_sql(void)
{
    char sql[128];
    drv_db_t *ctx = get_db_ctrl();

    ERRP(ctx->init != TRUE, "not init db", goto ERR0);
    sprintf(sql, SQL_FIND_IS_HAS_TABLE_NAME, MAGIC_NUMBER);

    int ret = sqlite3_exec(ctx->db, sql, callback, NULL, NULL);
    ERRP(ret != SQLITE_OK, "check sql table err", goto ERR0);

    return SUCCESS;
ERR0:
    return FAILURE;
}

int drv_db_create_table(void)
{
    drv_db_t *ctx = get_db_ctrl();

    int ret = drv_db_exec(SQL_CREATE_USER_TABLE, NULL, NULL);
    ERRP(ret != SQLITE_OK, "创建用户表失败！！！", goto ERR0);
    ret = drv_db_exec(SQL_INSERT_DEFAULT_USER, NULL, NULL);
    ERRP(ret != SQLITE_OK, "添加默认用户失败！！！", goto ERR0);

    return SUCCESS;
ERR0:
    return FAILURE;
}
