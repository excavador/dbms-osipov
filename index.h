#ifndef __INDEX_H__
#define __INDEX_H__


#include "db.h"
#include "page.h"
#include "types.h"


typedef struct
{
    Page       common;
    /* minimal PageNumber  which index page controls */
    PageNumber start;
    /* count of pages which index page controls */
    PageNumber count;
    /* count of used pages which index page controls */
    PageNumber used;
    /* bitset where every bit 1 (page used) or 0 (page free) */
    uint8_t    data[1];
} Index;


Index* index_create(PageSize size);
Index* index_parse(void *raw, PageSize expectedPageSize);


inline PageNumber index_next(const Index* index)
{
    return index->next;
}

inline PageNumber index_begin(const Index* index)
{
    return index->start;
}

inline PageNumber index_end(const Index* index)
{
    return index_begin(index) + index->count;
}

/* PageNumber of first not used page which index page controls */
PageNumber index_free(Index* index);

/* does current index page control target? */
bool index_has(const Index* index, const PageNumber target)
{
    return index_begin(index) <= target && target < index_end(index);
}

bool index_full(const Index* index)
{
    return index->used == index->count;
}

bool index_get(const Index* index, PageNumber target);
void index_set_used(Index*, PageNumber);
void index_set_free(Index*, PageNumber);


#endif /* __INDEX_H__ */
