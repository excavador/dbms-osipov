=============================
Oleg Tsarev TechnoSphera DBMS
=============================

Introduction
============

Here is home work of Oleg Tsarev DBMS course of Mail.Ru TechnoSphera.

I implemented simple search tree based on  `B*+-Tree <https://en.wikipedia.org/wiki/B%2B_tree>`_ (B-Plus-Star-Tree) algorithm.

This document explains the structure and implementation details with
references to source code.

.. contents:: Table of Contents

Storage file
============

All data stored in single **file**.
**File** splited to three logical parts:
- **storage metadata** - general information about database and page index
- **page index** - information about used and unused pages (**database size** and **page index size** (second depends from first) we choosed during database creation)
- **pages** - fixes-size parts with data. **page size** choosed during DB creation

The page enumerated from zero and references each other over **page number**.

Storage metadata
================

All fields aligned to 32-bit offset.

+------------------+------+----------------------------------+
|Name              |Width | Description                      |
+==================+======+==================================+
|            MAGIC |32-bit| Magic constant ``0xFACABADF``    |
+------------------+------+----------------------------------+
|            CRC32 |32-bit| CRC-32 checksum of header        |
+------------------+------+----------------------------------+
|          DB SIZE |32-bit| Maximum size (Kb) of storage     |
+------------------+------+----------------------------------+
|        PAGE SIZE |16-bit| Size (b) of node/page of tree    |
+------------------+------+----------------------------------+
|       PAGE COUNT |32-bit| Count of pages in database       |
+------------------+------+----------------------------------+
| ROOT PAGE NUMBER |32-bit| Page number of the B+*-tree root |
+------------------+------+----------------------------------+

PAGE COUNT is count of data pages AND also size (in bits) of **page index**.

Source is *metadata.h*


Page in general
===============

+-------------+------+--------------------------------+
|        Name |Width | Description                    |
+=============+======+================================+
|       MAGIC |32-bit| Magic constant ``0xFACABADC``  |
+-------------+------+--------------------------------+
|        SIZE |32-bit| Size of the page               |
+-------------+------+--------------------------------+
|       CRC32 |32-bit| CRC-32 checksum of page        |
+-------------+------+--------------------------------+
| PAGE NUMBER |32-bit| Page number                    |
+-------------+------+--------------------------------+

The rest of the page depends from the page kind.
Magic last four bytes depends from page kind:

+---------+---------+--------+
|         | NOT-LEAF|    LEAF|
+=========+=========+========+
| NOT-ROOT|       0 |      1 |
+---------+---------+--------+
|     ROOT|       2 |      3 |
+---------+---------+--------+

Magic for different page kinds:

+---------+--------------+--------------+
|         |      NOT-LEAF|          LEAF|
+=========+==============+==============+
| NOT-ROOT|``0xFACABADC``|``0xFACABADD``|
+---------+--------------+--------------+
|     ROOT|``0xFACABADE``|``0xFACABADF``|
+---------+--------------+--------------+


Index Page
==========

Every **index page** contains **index page header** and **index data data**

Source is *index.h*

-----------------
Index Page header
-----------------

+------------------------+------+----------------------------------+
|Name                    |Width |Description                       |
+========================+======+==================================+
|                  MAGIC |32-bit| See `Page in general`_           |
+------------------------+------+----------------------------------+
|                   SIZE |16-bit| See `Page in general`_           |
+------------------------+------+----------------------------------+
|                 CRC-32 |32-bit| See `Page in general`_           |
+------------------------+------+----------------------------------+
|            PAGE NUMBER |32-bit| See `Page in general`_           |
+------------------------+------+----------------------------------+
| DATA PAGE NUMBER START |32-bit|                                  |
+------------------------+------+----------------------------------+

Source is *index.h*

---------------
Index Page Data
---------------

Index Page Data is bitset, where every bit

- ``0`` if page used by storage
- ``1`` if page is free and can be reused

Source is *index.h*

Data Page
=========

Every data page can be two kinds:

- **leaf** page

- **not-leaf** page

More over, page can has **root** flag  which indicates root page.
Every page has **data page header** and **data page data** parts

Source is *node.h*

----------------
Data Page Header
----------------

TODO

Source is *node.h*

--------------
Leaf Data Page
--------------

TODO

Source is *node.h*

------------------
Not-Leaf Data Page
------------------

TODO

Source is *node.h*
