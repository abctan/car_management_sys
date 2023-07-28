#ifndef _DRV_DB_H
#define _DRV_DB_H

#include "types.h"
#include "mln_queue.h"
#include <sqlite3.h>

struct drv_db_sql_history {
    mln_queue_t *queue;
    struct mln_queue_attr attr;
};

typedef struct drv_db {
    bool init;
    bool is_first_load;
    char *db_path;
    sqlite3 *db;
    char *db_errmsg;
    struct drv_db_sql_history history;
} drv_db_t;

#define SQLFILE_PATH "db/car.db"
#define DB_HISTORY_MAX_LEN  20 

#define MAGIC_NUMBER                "car_magic"
#define SQL_FIND_IS_HAS_TABLE_NAME  "SELECT COUNT(*) FROM sqlite_master where type ='table' and name = '%s'"

// 创建user表
#define SQL_CREATE_USER_TABLE \
"CREATE TABLE user ( \
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \
    username TEXT NOT NULL, \
    password TEXT NOT NULL, \
    limits INT NOT NULL, \
    login_time INTEGER NOT NULL, \
    create_time INTEGER NOT NULL \
);"

#define SQL_INSERT_DEFAULT_USER \
"INSERT INTO user (id, username, password, limits, login_time, create_time) \
    VALUES (NULL, 'admin', 'admin', 1, 10, 10);"


int drv_db_init(void);
void drv_db_destroy(void);
int drv_db_check_is_has_sql(void);
int drv_db_create_table(void);

#endif