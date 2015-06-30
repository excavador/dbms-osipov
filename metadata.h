#ifndef __METADATA_H__
#define __METADATA_H__


#include "db.h"
#include "page.h"
#include "types.h"


typedef struct
{
    Page       common;
    uint32_t   db_size;
    PageSize   padding;
    PageSize   page_size;
    PageNumber page_root;
} Metadata;


Metadata* metadata_create(const DBC config);


/* load page: page size read from metadata */
Metadata* metadata_parse(void* raw);


#endif /* __METADATA_H__ */
