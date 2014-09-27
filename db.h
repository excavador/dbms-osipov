#ifndef _DB_H_
#define _DB_H_

#include <stddef.h>

/* check `man dbopen` */
struct DBT {
     void  *data;
     size_t size;
};
typedef struct DBT DBT;

struct DB {
    /* Public API */
    int (*close)(const struct DB *db);
    int (*del)(const struct DB *db, const DBT *key);
    int (*get)(const struct DB *db, DBT *key, struct DBT *data);
    int (*put)(const struct DB *db, DBT *key, const DBT *data);
    int (*sync)(const struct DB *db);
};
typedef struct DB DB;

struct DBC {
  /* Maximum on-disk file size */
  /* 512MB by default */
  size_t db_size;
  /* Maximum chunk (node/data chunk) size */
  /* 4KB by default */
  size_t chunk_size;
  /* Maximum memory size */
  /* 16MB by default */
  size_t mem_size;
};
typedef struct DBC DBC;

DB *dbcreate(const char *file, const struct DBC conf);
DB *dbopen  (const char *file); /* Metadata in file */

#endif /* _DB_H_ */
