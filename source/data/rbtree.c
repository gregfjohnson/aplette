/* rbtree.c, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <stdlib.h>
#include "rbtree.h"

/* Implementation of red-black trees; ordered binary trees
 * that maintain balance in the presence of arbitrary sequences
 * of inserts and deletes.
 *
 * Each node is given a color (red or black), and the tree satisfies
 * the following two properties:
 * black property:  sibling nodes have the same black-height.
 * red property:    no red node has a red parent.
 *
 * Usage:
 *     rbtree_t tree;
 *     rbtree_init(&tree, my_data_comparison_function);
 *
 *     rtbree_insert(&tree, &my_data);
 *     rbtree_delete(&tree, &my_data);
 *
 *     my_data_t search, *found;
 *     search.key = key
 *     found = rbtree_find(&tree, &search);
 *
 *     found = rbtree_first(&tree) 
 *
 *     rb_tree_t iter = rb_iter(&tree);
 *     while ((found = rbtree_iter_next(&iter)) != NULL) {
 *         ...
 *     }
 *
 * Don't believe what they tell you in algorithms textbooks ;-).  The red-black
 * tree algorithms are hard to understand.  This implementation is intended to
 * be helpful in making the opaque magic easier to grok.
 */

static rbtree_node_t* parent(rbtree_node_t* node)
{
    return (node != NULL ? node->parent : NULL);
}

static int is_left_child(rbtree_node_t* node)
{
    return parent(node) != NULL ? parent(node)->lchild == node : 0;
}

static rbtree_node_t* grandparent(rbtree_node_t* node)
{
    return (parent(node) != NULL ? parent(node)->parent : NULL);
}

static int is_red_node(rbtree_node_t* node)
{
    return (node != NULL ? node->color == 'r' : 0);
}

static int is_root_node(rbtree_node_t* node)
{
    return (node != NULL && parent(node) == NULL);
}

static int is_inside_child(rbtree_node_t* node)
{
    return (is_left_child(node) != is_left_child(parent(node)));
}

static rbtree_node_t* inside_child(rbtree_node_t* node)
{
    return (node == NULL ? NULL : is_left_child(node) ? node->rchild : node->lchild);
}

static rbtree_node_t* outside_child(rbtree_node_t* node)
{
    return (node == NULL ? NULL : is_left_child(node) ? node->lchild : node->rchild);
}

static rbtree_node_t* sibling(rbtree_node_t* node)
{
    return parent(node) != NULL
        ? (is_left_child(node) ? parent(node)->rchild : parent(node)->lchild)
        : NULL;
}

static rbtree_node_t* uncle(rbtree_node_t* node)
{
    return sibling(parent(node));
}

static rbtree_node_t* near_nephew(rbtree_node_t* node)
{
    return inside_child(sibling(node));
}

static rbtree_node_t* far_nephew(rbtree_node_t* node)
{
    return outside_child(sibling(node));
}

static rbtree_node_t* successor(rbtree_node_t* node)
{
    rbtree_node_t* result;

    if (node == NULL)
        return NULL;

    if (node->rchild != NULL) {
        result = node->rchild;

        while (result->lchild != NULL)
            result = result->lchild;
    }
    else {
        result = node;
        while (result != NULL && !is_left_child(result))
            result = parent(result);

        result = parent(result);
    }
    return result;
}

static void init_node(rbtree_node_t* node, void* vnode)
{
    node->parent = NULL;
    node->lchild = node->rchild = NULL;
    node->color = 'r';
    node->userData = vnode;
}

static rbtree_node_t* new_node(rbtree_t* tree, void* vnode)
{
    rbtree_node_t* x = (rbtree_node_t*)tree->malloc(sizeof(rbtree_node_t));

    if (x != NULL) {
        init_node(x, vnode);
    }

    return x;
}

static int violatesRedProperty(rbtree_node_t* node)
{
    return (is_red_node(node) && is_red_node(parent(node)));
}

static rbtree_node_t* set_child(rbtree_t* tree, rbtree_node_t* node,
    rbtree_node_t* child, char left_child)
{
    if (node == NULL)
        tree->root = child;

    else if (left_child)
        node->lchild = child;

    else
        node->rchild = child;

    if (child != NULL)
        child->parent = node;

    return child;
}

static rbtree_node_t* set_lchild(rbtree_t* tree, rbtree_node_t* node,
    rbtree_node_t* child)
{
    return set_child(tree, node, child, 1);
}

static rbtree_node_t* set_rchild(rbtree_t* tree, rbtree_node_t* node,
    rbtree_node_t* child)
{
    return set_child(tree, node, child, 0);
}

static void rotateUpNode(rbtree_t* tree, rbtree_node_t* node)
{
    int left_child = is_left_child(node);
    rbtree_node_t* p = parent(node);
    rbtree_node_t* gp = grandparent(node);

    set_child(tree, p, inside_child(node), left_child);
    set_child(tree, gp, node, is_left_child(p));
    set_child(tree, node, p, !left_child);
}

/*       old_top:c1                node:c1
 *          |                        |         
 *     +----+----+     ===>     +----+----+    
 *     |         |              |         |    
 *  node:c2     t_3            t_1     old_top:c2
 *     |                                  |    
 *  +--+--+                            +--+--+ 
 *  |     |                            |     | 
 * t_1   t_2                          t_2   t_3
 *
 * t_2 stays at same depth and its parent stays the same color.
 * t_1 and t_3 both change depth, and swap color of parent.
 * new tree has same depth, and same root-node color.
 */
static void rotateUp(rbtree_t* tree, rbtree_node_t* node)
{
    rbtree_node_t* p = parent(node);
    char pc = p->color;
    p->color = node->color;
    node->color = pc;

    rotateUpNode(tree, node);
}

static rbtree_node_t* rec_rbtree_find(rbtree_t* tree, rbtree_node_t* root,
    rbtree_node_t* search)
{
    int rel;

    if (root == NULL)
        return NULL;

    else if ((rel = tree->cmp(search->userData, root->userData)) == 0)
        return root;

    else if (rel < 0)
        return rec_rbtree_find(tree, root->lchild, search);

    else
        return rec_rbtree_find(tree, root->rchild, search);
}

/* do a binary search looking for a node whose data compares equal to
 * vsearch.  if found, return a pointer to the user-provided data in
 * the matching node.  if not found, return NULL.
 * if multiple nodes test equal, return an arbitrary one.
 */
void* rbtree_find(rbtree_t* tree, void* vsearch)
{
    rbtree_node_t search, *found;
    search.userData = vsearch;
    found = rec_rbtree_find(tree, tree->root, &search);

    if (found == NULL)
        return NULL;
    else
        return found->userData;
}

static rbtree_node_t* tree_insert(rbtree_t* tree, rbtree_node_t** node_ptr,
    void* new_data)
{
    int cmp;
    rbtree_node_t* node = *node_ptr;
    rbtree_node_t* newNode;

    if (node == NULL) {
        if ((newNode = new_node(tree, new_data)) == NULL)
            return NULL;
        return tree->root = newNode;
    }

    cmp = tree->cmp(new_data, node->userData);

    if (cmp < 0) {
        if (node->lchild == NULL) {
            if ((newNode = new_node(tree, new_data)) == NULL)
                return NULL;
            return set_lchild(tree, node, newNode);
        }
        else {
            return tree_insert(tree, &node->lchild, new_data);
        }
    }
    else {
        if (node->rchild == NULL) {
            if ((newNode = new_node(tree, new_data)) == NULL)
                return NULL;
            return set_rchild(tree, node, newNode);
        }
        else {
            return tree_insert(tree, &node->rchild, new_data);
        }
    }
}

/* node is red and its parent is also red. */
static void restoreRedProperty(rbtree_t* tree, rbtree_node_t* fixme)
{
    if (is_root_node(parent(fixme))) {
        parent(fixme)->color = 'b';

        /* if both parent and uncle are red, they can both be made black
     * and grandparent can be made red.  this will fix the red-property
     * violation between "fixme" and its parent, but it may
     * require a recursive fix-up of the grandparent.
     */
    }
    else if (is_red_node(uncle(fixme))) {
        parent(fixme)->color = 'b';
        uncle(fixme)->color = 'b';
        grandparent(fixme)->color = 'r';

        if (violatesRedProperty(grandparent(fixme)))
            restoreRedProperty(tree, grandparent(fixme));
    }
    else {
        /* see picture on rotateUp(p):
         * outside child (t_1) changes parent color,
         * and sibling(t_3) changes parent color.
         *
         * so, if we can make sure that fixme is an outside child,
         * then rotateUp(parent) will fix its red violation.
         * and, since uncle node is black, changing
         * the color of that node's parent is safe.
         */

        if (is_inside_child(fixme)) {
            rotateUp(tree, fixme);
            fixme = outside_child(fixme);
        }

        rotateUp(tree, parent(fixme));
    }
}

void rbtree_insert(rbtree_t* tree, void* vnode)
{
    rbtree_node_t* x = tree_insert(tree, &tree->root, vnode);

    if (x == NULL)
        return; /* can happen if malloc fails.. */

    if (violatesRedProperty(x))
        restoreRedProperty(tree, x);
}

/* black-depth of fixme is one less than black-depth of sibling.
 * node is not red.
 */
static void restoreBlackProperty(rbtree_t* tree, rbtree_node_t* fixme)
{
    /* we need sibling to be black.. */
    if (is_red_node(sibling(fixme))) {
        rotateUp(tree, sibling(fixme));
    }

    /* if sibling has no red children, it can be made red.
     * this will make sibling shorter, so that both nodes now have
     * same black-depth.
     *
     * but, unless parent is root this will make parent shorter
     * than its sibling.  if we're lucky and parent is red, we
     * can make it taller by changing it to black and all is well.
     * if not, we recursively fix parent.
     */

    if (!is_red_node(near_nephew(fixme)) && !is_red_node(far_nephew(fixme))) {
        sibling(fixme)->color = 'r';

        if (is_red_node(parent(fixme))) {
            parent(fixme)->color = 'b';
        }
        else if (!is_root_node(parent(fixme))) {
            restoreBlackProperty(tree, parent(fixme));
        }
    }
    else {
        /* rotateUp() below will increase black-depth of fixme (good)
         * but decrease black-depth of far nephew (bad).
         * however, we can guarantee the far nephew is red, and
         * that will let us fix its black depth by coloring it black.
         */

        if (!is_red_node(far_nephew(fixme))) {
            rotateUp(tree, near_nephew(fixme));
        }

        rotateUp(tree, sibling(fixme));

        /* node that was our far nephew is now our uncle.. */
        uncle(fixme)->color = 'b';
    }
}

void* rbtree_delete(rbtree_t* tree, void* vnode)
{
    rbtree_node_t *delete_me, *childOrNull, search;
    void *userData;

    search.userData = vnode;
    delete_me = rec_rbtree_find(tree, tree->root, &search);

    if (delete_me == NULL) {
        return NULL;
    }

    userData = delete_me->userData;

    /* ensure delete_me has at least one NULL child node.
     * if delete_me has two non-null child nodes, exchange
     * it with its immediate successor, the leftmost child of
     * its right subtree.
     */

    if (delete_me->lchild != NULL && delete_me->rchild != NULL) {
        delete_me->userData = successor(delete_me)->userData;
        delete_me = successor(delete_me);
    }

    if (!is_root_node(delete_me) && !is_red_node(delete_me)) {
        delete_me->color = 'w';
        restoreBlackProperty(tree, delete_me);
    }

    childOrNull = delete_me->lchild != NULL ? delete_me->lchild
                                            : delete_me->rchild;

    set_child(tree, parent(delete_me),
        childOrNull,
        is_left_child(delete_me));

    tree->free(delete_me);

    return userData;
}

/* initialize a new red-black tree with comparison method cmp. */
void rbtree_init(rbtree_t* tree, int (*cmp)(void*, void*))
{
    tree->root = NULL;
    tree->cmp = cmp;
    tree->malloc = malloc;
    tree->free = free;
}

/* set optional custom malloc and free functions for internals of rbtree implementation */
void rbtree_set_malloc_free(rbtree_t* tree, rbtree_malloc_t* malloc, rbtree_free_t* free)
{
    tree->malloc = malloc;
    tree->free = free;
}

/* find the first (smallest) node in the tree.  return NULL if tree is empty. */
static rbtree_node_t* first_node(rbtree_t* tree)
{
    rbtree_node_t* node;
    if (tree->root == NULL) {
        return NULL;
    }

    node = tree->root;
    while (node->lchild != NULL) {
        node = node->lchild;
    }

    return node;
}

/* return the successor in the tree of node.  if no successor, return NULL. */
static rbtree_node_t* next_node(rbtree_node_t* node)
{
    if (node == NULL) {
        return NULL;
    }

    /* if we have a right child, find its leftmost descendent. */
    if (node->rchild != NULL) {
        node = node->rchild;

        while (node->lchild != NULL) {
            node = node->lchild;
        }

        /* else, traverse toward root looking for a node that's parent of a left
     * child on the traversal path.
     */
    }
    else {
        while (1) {
            if (node->parent == NULL) {
                return NULL;
            }
            if (node->parent->lchild == node) {
                node = node->parent;
                break;
            }
            node = node->parent;
        }
    }

    return node;
}

/* initialize and return an iterator for the user-data elements in the tree */
rbtree_iter_t rbtree_iter(rbtree_t* tree)
{
    rbtree_iter_t iter;

    iter.next_node = first_node(tree);
    iter.tree = tree;

    return iter;
}

/* return the next node in the tree using state stored in iterator "iter" */
void* rbtree_iter_next(rbtree_iter_t* iter)
{
    void* result;

    if (iter->next_node == NULL) {
        return NULL;
    }

    /* we will return the data pointed to by the current node; remember it. */
    result = iter->next_node->userData;

    /* find the node that will be returned the next time we are called */
    iter->next_node = next_node(iter->next_node);

    return result;
}

void* rbtree_first(rbtree_t* tree)
{
    rbtree_node_t* node = first_node(tree);
    if (node == NULL) {
        return NULL;
    }

    return node->userData;
}
