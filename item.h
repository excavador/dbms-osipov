#ifndef __ITEM_H__
#define __ITEM_H__


/* See tree.h for documentation */


#include "db.h"


/* key or value */
typedef DBT Item;


/* compare two items */
inline int item_compare(const Item* left, const Item* right)
{
  int result = memcmp(left->data, right->data,
                      min(left->size, right->size));
  if (0 != result)
    return result;
  else if (left->size < right->size)
    return -1;
  else if (right->size > left->size)
    return 1;
  else
    return 0;
}

#endif /* __ITEM_H__ */
