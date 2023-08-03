#include "drv_sys.h"
#include "drv_shell_port.h"
#include "elog.h"
#include "drv_db.h"
#include "mln_core.h"
#include "common.h"
#include <stdio.h>
#include <signal.h>

typedef struct drv_sys {
    bool init;
    struct mln_core_attr mln_attr;
} drv_sys_t;

static drv_sys_t g_drv_sys = {0};

drv_sys_t *get_drv_sys_ctrl(void)
{
    return &g_drv_sys;
}

static int sysExit(int value)
{
    drv_shell_signal_handler(0);
    drv_sys_deinit();
    exit(value);
    return value;
}

static void signalHandler(int signal)
{
    sysExit(0);
}

int drv_sys_init(int argc, char *argv[])
{
    drv_sys_t *ctx = get_drv_sys_ctrl();

    if (ctx->init == TRUE) {
        return SUCCESS;
    }

    drv_log_init();
    int ret = drv_sys_mln_init(argc, argv);
    ERRP(ret != SUCCESS, "mln init err", goto ERR0);
    drv_db_init();
    drv_shell_init();

    signal(SIGINT, signalHandler);

    ctx->init = TRUE;
    return SUCCESS;
ERR0:
    return FAILURE;
}

void drv_sys_deinit(void)
{
    drv_db_destroy();
    // elog_set_output_enabled(false);

}

int drv_sys_mln_init(int argc, char *argv[])
{
    drv_sys_t *ctx = get_drv_sys_ctrl();

    ctx->mln_attr.argc = argc;
    ctx->mln_attr.argv = argv;
    ctx->mln_attr.global_init = NULL;
    ctx->mln_attr.main_thread = NULL;
    ctx->mln_attr.master_process = NULL;
    ctx->mln_attr.worker_process = NULL;
    int ret = mln_core_init(&ctx->mln_attr);
    ERRP(ret != 0, "mln_core_init error", goto ERR0);

    return SUCCESS;
ERR0:
    return FAILURE;
}

void drv_log_init(void)
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
}

void drv_debug_func(void)
{
    log_a("Hello world!");
    log_e("Hello world!");
    log_w("Hello world!");
    log_i("Hello world!");
    log_d("Hello world!");
    log_v("Hello world!");
}

void drv_sys_run(void)
{
    drv_shell_run();
}
