#ifndef __TYPES_H__
#define __TYPES_H__


/* See tree.h for documentation */


#include <stdbool.h>
#include <stdint.h>


#include "db.h"


/* size in bytes */
typedef uint16_t Size;


/* index/number of item (key, value) or child  */
typedef uint16_t ItemNumber;


/* index/number of the node/page in file */
typedef uint32_t NodeNumber;


/* node kind */
typedef uint32_t NodeKind;
#define NODE_KIND_MASK_LEAF (1 << 0)
#define NODE_KIND_MASK_ROOT (1 << 2)


/* offsets in node */
#define NODE_OFFSET_MAGIC  0
#define NODE_OFFSET_NUMBER (NODE_OFFSET_MAGIC  + sizeof(uint32_t))
#define NODE_OFFSET_KIND   (NODE_OFFSET_NUMBER + sizeof(uint32_t))
#define NODE_OFFSET_COUNT  (NODE_OFFSET_KIND   + sizeof(uint32_t))
#define NODE_OFFSET_DATA   (NODE_OFFSET_COUNT  + sizeof(uint32_t))

/* magic four bytes in begin of the node*/
#define NODE_MAGIC 0xFACABABA


/* invalid node/page number */
#define NODE_INVALID 0xFFFFFFFF


/* see tree.h */
struct Index;
struct Node;
struct Storage;

typedef struct Index   Index;
typedef struct Node    Node;
typedef struct Storage Storage;



#endif /* __TYPES__H__ */
