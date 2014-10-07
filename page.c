#include <strings.h>
#include <zlib.h>
#include "error.h"
#include "page.h"


Page* page_create(PageSize size)
{
    Page* result;

    result  = (Page*) malloc(size);

    bzero(result, size);

    result->magic = cPageMagic;
    result->size  = size;
    result->crc32 = 0;
    result->kind  = kind;

    return result;
}


Page* page_load(void* raw, PageSize expectedPageSize)
{
    Page*    result;
    uint32_t crc;

    result = (Page*) raw;

    /* check magic */
    if (cPageMagic != result->magic)
    {
        error_code = ERROR_PAGE_BAD_MAGIC;
        return NULL;
    }

    /* check size */
    if (expectedPageSize != page->size)
    {
        error_code = ERROR_PAGE_BAD_SIZE;
        return NULL;
    }

    /* calculate CRC32 */
    crc = crc32(0L, Z_NULL, 0);
    /* skip MAGIC, SIZE, CRC32 */
    crc = crc32(crc, page, page->size - cPageRestOffset);
    /* check CRC32 */
    if (crc != page->crc)
    {
        error_code = ERROR_PAGE_BAD_CRC32;
        return NULL;
    }

    switch (page->kind)
    {
    case ePageMetaData:     break;
    case aPageIndex:        break;
    case ePageLeaf:         break;
    case ePageIntermediate: break;
    case ePageRoot:         break;
    default:
    {
        error_code = ERROR_PAGE_BAD_KIND;
        return NULL;
    }
    }

    return page;
}


void page_checksum(Page* page)
{
    /* calculate CRC32 */
    page->crc32 = crc32(0L, Z_NULL, 0);
    /* skip MAGIC, SIZE, CRC32 */
    page->crc32 = crc32(crc, page, page->size - cPageRestOffset);
}
