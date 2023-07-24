#include "drv_db.h"
#include "common.h"
#include "elog.h"

static drv_db_t g_drv_db = {0};

drv_db_t *get_db_ctrl(void)
{
    return &g_drv_db;
}

int drv_db_init(void)
{
    drv_db_t *ctx = get_db_ctrl();

    int ret = sqlite3_open(SQLFILE_PATH, &ctx->db);
    ERRP(ret != SQLITE_OK, "sqlite3_open failed", goto ERR0);

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

    sqlite3_close(ctx->db);
    ctx->db = NULL;
    ctx->init = FALSE;
}
