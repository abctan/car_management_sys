#include "drv_db.h"
#include "common.h"
#include "elog.h"
#include <stdio.h>

static drv_db_t g_drv_db = {0};

drv_db_t *get_db_ctrl(void)
{
    return &g_drv_db;
}

int drv_db_init(void)
{
    drv_db_t *ctx = get_db_ctrl();

    int ret = sqlite3_open_v2(SQLFILE_PATH, &ctx->db, SQLITE_OPEN_READWRITE, NULL);
    if (ret != SQLITE_OK) {
        elog_e("debug", "数据库%s不存在, 初始化数据库!!!", SQLFILE_PATH);
        ret = sqlite3_open_v2(SQLFILE_PATH, &ctx->db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
        ERRP(ret != SQLITE_OK, "初始化数据库失败", goto ERR0);
        ret = drv_db_create_table();
        ERRPGO(ret != SUCCESS, goto ERR0);
        elog_e("debug", "初始化数据库成功!!!");
    }
    

    ctx->init = TRUE;

    return SUCCESS;
ERR0:
    return FAILURE;
}

void drv_db_destroy(void)
{
    drv_db_t *ctx = get_db_ctrl();

    if (ctx->init != TRUE) {
        return;
    }

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
    int ret = sqlite3_exec(ctx->db, SQL_CREATE_USER_TABLE, NULL, NULL, NULL);
    ERRP(ret != SQLITE_OK, "创建用户表失败！！！", goto ERR0);

    return SUCCESS;
ERR0:
    return FAILURE;
}
