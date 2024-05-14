#include "avl-tree.h"

#include <assert.h>
#include <malloc.h>
#include <memory.h>

void AvlTreeNodeConstruct(AvlTreeNode *const restrict node,
                          const void *const restrict value,
                          AvlTreeNode *const restrict parent,
                          unsigned long elementSize) {
    assert(node != NULL);
    assert(value != NULL);
    assert(elementSize > 0);

    node->value = malloc(elementSize);
    assert(node->value != NULL);
    memcpy(node->value, value, elementSize);
    node->height = 1;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
}

AvlTreeNode *AvlTreeNodeNew(const void *const restrict value,
                            AvlTreeNode *const restrict parent,
                            unsigned long elementSize) {
    AvlTreeNode *node = (AvlTreeNode *)malloc(sizeof(AvlTreeNode));
    AvlTreeNodeConstruct(node, value, parent, elementSize);
    return node;
}

void AvlTreeNodeDestruct(AvlTreeNode *const restrict node) {
    if (node == NULL) return;

    free(node->value);
    node->value = NULL;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
}

void AvlTreeNodeDelete(AvlTreeNode **const restrict node) {
    if (node == NULL) return;

    AvlTreeNodeDestruct(*node);
    free(*node);
    *node = NULL;
}

unsigned int AvlTreeNodeHeight(const AvlTreeNode *const restrict node) {
    if (node == NULL) return 0;
    return node->height;
}

void AvlTreeConstruct(AvlTree *const restrict tree,
                      const unsigned long elementSize,
                      CompareFunction *const compare) {
    assert(tree != NULL);
    assert(compare != NULL);
    assert(elementSize > 0);

    tree->root = NULL;
    tree->Size = 0;
    tree->compare = compare;
    tree->elementSize = elementSize;
}

AvlTree *AvlTreeNew(const unsigned long elementSize,
                    CompareFunction *const compare) {
    AvlTree *tree = (AvlTree *)malloc(sizeof(AvlTree));
    AvlTreeConstruct(tree, elementSize, compare);
    return tree;
}

static void __AvlTreeDestruct(AvlTreeNode *const restrict node) {
    if (node == NULL) return;

    __AvlTreeDestruct(node->left);
    __AvlTreeDestruct(node->right);
    AvlTreeNodeDestruct(node);
    free(node);
}

void AvlTreeDestruct(AvlTree *const restrict tree) {
    if (tree == NULL) return;

    __AvlTreeDestruct(tree->root);
    tree->root = NULL;
    tree->compare = NULL;
    tree->elementSize = 0;
    tree->Size = 0;
}

void AvlTreeDelete(AvlTree **const restrict tree) {
    if (tree == NULL) return;

    AvlTreeDestruct(*tree);
    free(*tree);
    *tree = NULL;
}

void *AvlTreeFind(const AvlTree *const restrict tree,
                  const void *const restrict value) {
    assert(tree != NULL);
    assert(value != NULL);

    AvlTreeNode *node = NULL;
    int ret = 0;
    if (tree->Size == 0) return NULL;
    node = tree->root;
    while (node != NULL) {
        ret = tree->compare(node->value, value);
        if (ret > 0)
            node = node->left;
        else if (ret < 0)
            node = node->right;
        else
            break;
    }
    return node;
}

static inline unsigned int __max(unsigned int a, unsigned int b) {
    return a > b ? a : b;
}

static inline Bool __unbalanced(unsigned int left, unsigned int right) {
    return left > right ? left - right > 1 : right - left > 1;
}

static inline AvlTreeNode *__ll(AvlTree *const restrict tree,
                                AvlTreeNode *const restrict node) {
    AvlTreeNode *temp = node->left;
    node->left = temp->right;
    if (temp->right != NULL) temp->right->parent = node;
    temp->right = node;
    temp->parent = node->parent;
    node->parent = temp;
    if (temp->parent == NULL)
        tree->root = temp;
    else if (temp->parent->left == node)
        temp->parent->left = temp;
    else
        temp->parent->right = temp;
    node->height =
        __max(AvlTreeNodeHeight(node->left), AvlTreeNodeHeight(node->right)) +
        1;
    temp->height =
        __max(AvlTreeNodeHeight(temp->left), AvlTreeNodeHeight(temp->right)) +
        1;
    return temp;
}

static inline AvlTreeNode *__rr(AvlTree *const restrict tree,
                                AvlTreeNode *const restrict node) {
    AvlTreeNode *temp = node->right;
    node->right = temp->left;
    if (temp->left != NULL) temp->left->parent = node;
    temp->left = node;
    temp->parent = node->parent;
    node->parent = temp;
    if (temp->parent == NULL)
        tree->root = temp;
    else if (temp->parent->left == node)
        temp->parent->left = temp;
    else
        temp->parent->right = temp;
    node->height =
        __max(AvlTreeNodeHeight(node->left), AvlTreeNodeHeight(node->right)) +
        1;
    temp->height =
        __max(AvlTreeNodeHeight(temp->left), AvlTreeNodeHeight(temp->right)) +
        1;
    return temp;
}

/**
 * @brief Rebalance the tree from bottom to top. O(log₂n).
 *
 * @param tree `this`.
 * @param from Where to start rebalancing.
 */
static void __AvlTreeRebalance(AvlTree *const restrict tree,
                               AvlTreeNode *const restrict from) {
    unsigned int left = 0, right = 0;
    AvlTreeNode *node = from;
    while (node != NULL) {
        left = AvlTreeNodeHeight(node->left);
        right = AvlTreeNodeHeight(node->right);
        if (__unbalanced(left, right)) {
            if (left > right) {
                left = AvlTreeNodeHeight(node->left->left);
                right = AvlTreeNodeHeight(node->left->right);

                if (right > left) node = __rr(tree, node->left);
                node = __ll(tree, node);
            } else {
                left = AvlTreeNodeHeight(node->right->left);
                right = AvlTreeNodeHeight(node->right->right);

                if (left > right) node = __ll(tree, node->left);
                node = __rr(tree, node);
            }
        } else
            node->height = __max(AvlTreeNodeHeight(node->left),
                                 AvlTreeNodeHeight(node->right)) +
                           1;
        node = node->parent;
    }
}

/**
 * @brief Add new element or replace old element without rebalancing. O(log₂n).
 *
 * @param tree `this`.
 * @param value Specified value.
 * @return AvlTreeNode* If new element added, a pointer refers to its parent
 * will be returned. Otherwise, `NULL` will be returned.
 */
static AvlTreeNode *__AvlTreeInsert(AvlTree *const restrict tree,
                                    const void *const restrict value) {
    int ret = 0;
    AvlTreeNode *node = tree->root;
    while (TRUE) {
        ret = tree->compare(node->value, value);
        if (ret > 0) {
            if (node->left == NULL) {
                node->left = AvlTreeNodeNew(value, node, tree->elementSize);
                break;
            }
            node = node->left;
        } else if (ret < 0) {
            if (node->right == NULL) {
                node->right = AvlTreeNodeNew(value, node, tree->elementSize);
                break;
            }
            node = node->right;
        } else {
            memcpy(node->value, value, tree->elementSize);
            return NULL;
        }
    }
    return node;
}

void AvlTreeInsert(AvlTree *const restrict tree,
                   const void *const restrict value) {
    assert(tree != NULL);
    assert(value != NULL);

    int ret = 0;
    AvlTreeNode *node = NULL;
    if (tree->Size == 0) {
        tree->root = AvlTreeNodeNew(value, NULL, tree->elementSize);
        tree->Size++;
        return;
    }

    node = __AvlTreeInsert(tree, value);
    if (node == NULL) return;
    __AvlTreeRebalance(tree, node);
    tree->Size++;
}

static AvlTreeNode *__AvlTreeFindForRemove(AvlTree *const restrict tree,
                                           const void *const restrict value) {
    int ret = 0;
    AvlTreeNode *node = tree->root;
    while (node != NULL) {
        ret = tree->compare(node->value, value);
        if (ret > 0)
            node = node->left;
        else if (ret < 0)
            node = node->right;
        else
            break;
    }
    return node;
}

/**
 * @brief Remove the specified `target` without rebalancing. O(log₂n).
 *
 * @param tree `this`.
 * @param target Specified node.
 * @return AvlTreeNode* The parent of removed node.
 */
static AvlTreeNode *__AvlTreeRemove(AvlTree *const restrict tree,
                                    AvlTreeNode *const restrict target) {
    AvlTreeNode *temp = NULL, *node = target->parent;
    if (target->left == NULL && target->right == NULL) {
        // target node is leaf
        if (node == NULL)
            AvlTreeNodeDelete(&tree->root);
        else {
            if (target == node->left)
                AvlTreeNodeDelete(&node->left);
            else
                AvlTreeNodeDelete(&node->right);
        }
    } else if (target->left == NULL) {
        // target node only has right child
        temp = target->right;
        if (node == NULL) {
            AvlTreeNodeDelete(&tree->root);
            tree->root = temp;
            temp->parent = NULL;
        } else {
            if (target == node->left) {
                AvlTreeNodeDelete(&node->left);
                node->left = temp;
            } else {
                AvlTreeNodeDelete(&node->right);
                node->right = temp;
            }
            temp->parent = node;
        }
    } else if (target->right == NULL) {
        // target node only has left child
        temp = target->left;
        if (node == NULL) {
            AvlTreeNodeDelete(&tree->root);
            tree->root = temp;
            temp->parent = NULL;
        } else {
            if (target == node->left) {
                AvlTreeNodeDelete(&node->left);
                node->left = temp;
            } else {
                AvlTreeNodeDelete(&node->right);
                node->right = temp;
            }
            temp->parent = node;
        }
    } else {
        // target has left child and right child
        // replace it by the smallest node in right children
        temp = target->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        memcpy(target->value, temp->value, tree->elementSize);
        if (temp->right != NULL) temp->right->parent = temp->parent;
        if (temp == temp->parent->right)
            temp->parent->right = temp->right;
        else
            temp->parent->left = temp->right;
        node = temp->parent;
        AvlTreeNodeDelete(&temp);
    }
    return node;
}

void AvlTreeRemove(AvlTree *const restrict tree,
                   const void *const restrict value) {
    assert(tree != NULL);
    assert(value != NULL);

    AvlTreeNode *node = NULL;
    if (tree->Size == 0) return;

    node = __AvlTreeFindForRemove(tree, value);
    if (node == NULL) return;
    node = __AvlTreeRemove(tree, node);
    if (node == NULL) return;
    __AvlTreeRebalance(tree, node);
    tree->Size--;
}

Bool __AvlTreeSome(AvlTreeNode *const restrict node, TestFunction *const test) {
    Bool result = FALSE;
    if (node == NULL) return FALSE;

    result = __AvlTreeSome(node->left, test);
    if (result == TRUE) return TRUE;
    result = test(node->value);
    if (result == TRUE) return TRUE;
    return __AvlTreeSome(node->right, test);
}

Bool AvlTreeSome(AvlTree *const restrict tree, TestFunction *const test) {
    assert(tree != NULL);
    assert(test != NULL);

    return __AvlTreeSome(tree->root, test);
}

Bool __AvlTreeAll(AvlTreeNode *const restrict node, TestFunction *const test) {
    Bool result = TRUE;

    if (node->left != NULL) {
        result = __AvlTreeAll(node->left, test);
        if (result == FALSE) return FALSE;
    }
    result = test(node->value);
    if (result == FALSE) return FALSE;
    if (node->right != NULL)
        return __AvlTreeAll(node->right, test);
    else
        return TRUE;
}

Bool AvlTreeAll(AvlTree *const restrict tree, TestFunction *const test) {
    assert(tree != NULL);
    assert(test != NULL);

    return __AvlTreeAll(tree->root, test);
}
