#include <assert.h>
#include "error.h"
#include "index.h"


Index* index_create(PageSize size)
{
    Index* result;

    result = (Index*) page_create(size, cPageIndex);

    if (NULL == result)
        return NULL;

    result->next  = cPageInvalid;
    result->start = 0;
    result->count = 0;
    result->used  = 0;

    return result;
}


Index* index_parse(void* raw, PageSize expectedPageSize)
{
    Index* result;

    result = (Index*) page_parse(raw, expectedPageSize);

    if (NULL == result)
        return NULL;

    if (result->common.kind != cPageIndex)
    {
        error_code = ERROR_PAGE_UNEXPECTED_KIND;
        return NULL;
    }

    return result;
}


static uint8_t gBitMask[8] = { 1, 2, 4, 8, 16, 32, 64, 128};


bool index_get(const Index* index, PageNumber target)
{
    PageNumber offset;
    PageSize  byte;
    uint8_t bit;

    assert(index_has(index, target));

    offset = target - index_begin(index);
    byte = offset / 8;
    bit = gBitMask[offset % 8];
    return (index->data[byte] & bit) > 0;
}


void index_set(Index* index, PageNumber target, bool value)
{
    PageNumber offset;
    PageSize byte;
    uint8_t  bit;

    assert(index_has(index, target));

    offset = target - index_begin(index);
    byte = offset / 8;
    bit = gBitMask[offset % 8];

    assert(value != ((index->data[byte] & bit) > 0));

    if (value)
    {
        index->used += 1;
        index->data[byte] &= bit;
    }
    else
    {
        index->used -= 1;
        index->data[byte] &= ~bit;
    }
}


void index_set_used(Index* index, PageNumber target)
{
    index_set(index, target, true);
}


void index_set_free(Index* index, PageNumber target)
{
    index_set(index, target, false);
}
