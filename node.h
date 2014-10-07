#ifndef __NODE_H__
#define __NODE_H__


/*
  See tree.h for begin of documentation


  ================
  Node of BPS-tree
  ================

  Header (every field aligned to 32-bit)
    Name       Width     Description
    ----       -----     -----------
    MAGIC         32     magic constant
    NUMBER        32     node/page number in the file
    KIND           2     node/page kind
    COUNT         16     count of keys/values/children on page
    DATA      <rest>     stored keys/values/children


  Notes about kind
    - first bit   page is leaf (has not children)
    - second bit  page is root (has not parent)


  Leaf page contains only (key,value) pairs.

  Non-leaf page contains keys and references to children.

  DATA of leaf page:
    key_1.offset value_1.offset ... key_n.offset value_n.offset data_end.offset key_1.data value_1.data ... key_n.data value_n.data

  DATA of non-leaf page:
    child_1 key_1.offset child_2 key_2.offset ... child_n ken_n.offset child_n+1 data_end.offset

*/


#include "db.h"
#include "item.h"
#include "types.h"


struct Node
{
  Storage* tree;
  uint8_t* raw;
};


inline bool node_kind_is(NodeKind value, NodeKind mask)
{ return (bool)(mask == (value & mask)); }


inline bool node_kind_is_leaf(NodeKind value)
{ return node_kind_is(value, NODE_KIND_MASK_LEAF); }


inline bool node_kind_is_root(NodeKind value)
{ return node_kind_is(value, NODE_KIND_MASK_ROOT); }


#define NODE_ACCESS(node, type, offset) ((type*)(node->raw + offset))


inline bool node_is_dirty(Node* node)
{ return node->dirty; }


inline bool node_is_valid(Node* node)
{ return NODE_MAGIC == NODE_ACCESS(node, uint32_t, NODE_MAGIC); }


inline uint32_t node_number(Node* node)
{ return *NODE_ACCESS(node, NodeNumber, NODE_OFFSET_NUMBER ); }


inline NodeKind node_kind(Node* node)
{ return *NODE_ACCESS(node, NodeKind, NODE_OFFSET_KIND); }


inline bool node_is_leaf(Node* node)
{ return node_kind_is_leaf(node_kind(node)); }


inline bool node_is_root(Node* node)
{ return node_kind_is_root(node_kind(node)); }


inline ItemNumber node_number(Node* node)
{ return *NODE_ACCESS(node, ItemNumber, NODE_OFFSET_COUNT); }


inline ItemNumber node_count_item(Node* node)
{ return node_number(node); }


inline ItemNumber node_count_child(Node* node)
{ return node_is_leaf(node) ? 0 : node_number(node) + 1; }


inline Item node_get_key(Node* node, ItemNumber which);


inline Item node_get_value(Node* node, ItemNumber which);


inline NodeNumber node_get_child(Node* node, ItemNumber which);


#endif /* __NODE__H__ */
