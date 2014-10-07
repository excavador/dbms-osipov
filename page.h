#ifndef __PAGE_H__
#define __PAGE_H__


#include "db.h"
#include "types.h"


typedef uint16_t PageSize;
typedef uint32_t PageNumber;


static const uint32_t cPageMagic      = 0xFACABADA;
static const uint32_t cPageRestOffset = 3 * sizeof(uint32_t);


typedef enum
{
    ePageMetaData     = 0xFFFFFFFF,
    ePageIndex        = 0xEEEEEEEE,
    ePageLeaf         = 0xDDDDDDD0,
    ePageIntermediate = 0xDDDDDDD1,
    ePageRoot         = 0xDDDDDDD2
} PageKind;


typedef struct
{
    const uint32_t  magic;
    union
    {
        const PageSize size;
        uin32_t        pack;
    };
    uint32_t         crc32;
    const PageNumber number;
    const PageKind   kind;
    uint8_t          data[0];
} Page;


/* do not use directly, use storage routines (storage.h) */
Page* page_create(PageSize size, PageKind kind);


/* load page */
Page* page_load(void* raw, PageSize expectedPageSize);


/* calculate page checksum and save in the page */
void page_checksum(Page*);


#endif /* __PAGE__H__ */
