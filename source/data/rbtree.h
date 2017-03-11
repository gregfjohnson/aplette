/* rbtree.h, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef RBTREE_H
#define RBTREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <unistd.h>

typedef int(rbtree_cmp_t)(void*, void*);

typedef void*(rbtree_malloc_t)(size_t size);
typedef void(rbtree_free_t)(void* ptr);

typedef struct _rbtree_node_t {
    void* userData;
    struct _rbtree_node_t* parent;
    struct _rbtree_node_t *lchild, *rchild;
    char color;
} rbtree_node_t;

typedef struct {
    rbtree_node_t* root;
    rbtree_cmp_t* cmp;

    /* optional custom functions to allocate and free rbtree_node_t's.
     * if not given, system malloc() and free() are used.
     */
    rbtree_malloc_t* malloc;
    rbtree_free_t* free;
} rbtree_t;

typedef struct {
    rbtree_node_t* next_node;
    rbtree_t* tree;
} rbtree_iter_t;

void rbtree_init(rbtree_t* tree, rbtree_cmp_t* cmp);
void rbtree_set_malloc_free(rbtree_t* tree, rbtree_malloc_t* malloc, rbtree_free_t* free);

void* rbtree_find(rbtree_t* tree, void* z);
void* rbtree_first(rbtree_t* tree);

void* rbtree_delete(rbtree_t* tree, void* z);
void rbtree_insert(rbtree_t* tree, void* x);

rbtree_iter_t rbtree_iter(rbtree_t* tree);
void* rbtree_iter_next(rbtree_iter_t* iter);

#ifdef __cplusplus
}
#endif

#endif
