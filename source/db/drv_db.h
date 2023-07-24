#ifndef _DRV_DB_H
#define _DRV_DB_H

#include "types.h"
#include <sqlite3.h>

typedef struct drv_db {
    bool init;
    sqlite3 *db;
} drv_db_t;

#define SQLFILE_PATH "db/car.db"

int drv_db_init(void);
void drv_db_destroy(void);

#endif