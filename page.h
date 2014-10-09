#ifndef __PAGE_H__
#define __PAGE_H__


#include "db.h"
#include "types.h"


typedef uint16_t PageSize;
typedef uint32_t PageNumber;


static const uint32_t cPageMagic      = 0xfacabada;
static const uint32_t cPageRestOffset = 3 * sizeof(uint32_t);


typedef uint32_t PageKind;
static const uint32_t cPageMetaData     = 0xffffffffUL;
static const uint32_t cPageIndex        = 0xeeeeeeeeUL;
static const uint32_t cPageLeaf         = 0xddddddd0UL;
static const uint32_t cPageIntermediate = 0xddddddd1UL;
static const uint32_t cPageRoot         = 0xddddddd2UL;


typedef struct
{
    const uint32_t   magic;
    PageSize         padding;
    const PageSize   size;
    uint32_t         crc32;
    const PageNumber number;
    const PageKind   kind;
    uint8_t          data[1];
} Page;


/* do not use directly, use storage routines (storage.h) */
Page* page_create(PageSize size, PageKind kind);


/* load page */
Page* page_load(void* raw, PageSize expectedPageSize);


/* calculate page checksum and save in the page */
void page_checksum(Page*);


#endif /* __PAGE__H__ */
