#ifndef __COLLECTIONS_AVL_TREE__
#define __COLLECTIONS_AVL_TREE__

#include "types.h"

typedef struct __AvlTreeNode {
    struct __AvlTreeNode *parent;
    void *value;
    unsigned int height;
    struct __AvlTreeNode *right;
    struct __AvlTreeNode *left;
} AvlTreeNode;

typedef struct {
    AvlTreeNode *root;
    unsigned long elementSize;
    CompareFunction *compare;

    unsigned int Size;
} AvlTree;

/**
 * @brief Construct function. O(1).
 *
 * @param node Target to be constructed.
 * @param value Value of `node`. It will be DEEP copied.
 * @param parent Parent of `node`.
 * @param elementSize Size of `value`.
 */
void AvlTreeNodeConstruct(AvlTreeNode *const restrict node,
                          const void *const restrict value,
                          AvlTreeNode *const restrict parent,
                          unsigned long elementSize);

/**
 * @brief Allocate a new node in heap. O(1).
 *
 * @param value Value of node. It will be DEEP copied.
 * @param parent Parent of node.
 * @param elementSize Size of `value`.
 * @return AvlTreeNode* Pointer refering to a heap address.
 */
AvlTreeNode *AvlTreeNodeNew(const void *const restrict value,
                            AvlTreeNode *const restrict parent,
                            unsigned long elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param node Target to be destructed. If `NULL`, nothing will happen.
 */
void AvlTreeNodeDestruct(AvlTreeNode *const restrict node);

/**
 * @brief Release `node` in heap. O(1).
 *
 * @param node Pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void AvlTreeNodeDelete(AvlTreeNode **const restrict node);

/**
 * @brief Get height of `node`.
 *
 * @param node `this`.
 * @return unsigned int If `node` == `NULL`, `0` will be returned.
 */
unsigned int AvlTreeNodeHeight(const AvlTreeNode *const restrict node);

/**
 * @brief Construct function. O(1).
 *
 * @param tree Target to be constructed.
 * @param elementSize Element size of `tree`
 * @param compare Function used in comparing two elements.
 */
void AvlTreeConstruct(AvlTree *const restrict tree,
                      const unsigned long elementSize,
                      CompareFunction *const compare);

/**
 * @brief Allocate a new tree in heap. O(1).
 *
 * @param initialCapacity Initial capacity of tree.
 * @param elementSize Element size of tree.
 * @param compare Function used in comparing two elements.
 * @return AvlTree* Pointer refering to a heap address.
 */
AvlTree *AvlTreeNew(const unsigned long elementSize,
                    CompareFunction *const compare);

/**
 * @brief Destruct function. O(n).
 *
 * @param tree Target to be destructed. If `NULL`, nothing will happen.
 */
void AvlTreeDestruct(AvlTree *const restrict tree);

/**
 * @brief Release `tree` in heap. O(n).
 *
 * @param tree Pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void AvlTreeDelete(AvlTree **const restrict tree);

/**
 * @brief Try to get the element which is equal to the specified
 * `value`. O(log₂n).
 *
 * @param tree `this`.
 * @param value Specified value.
 * @return void* If not found, `NULL` will be returned.
 */
void *AvlTreeFind(const AvlTree *const restrict tree,
                  const void *const restrict value);

/**
 * @brief Add new element or replace old element. O(log₂n).
 *
 * @param tree `this`.
 * @param value Value of element
 */
void AvlTreeInsert(AvlTree *const restrict tree,
                   const void *const restrict value);

/**
 * @brief Remove the element which is equal to specified `value`. If not found,
 * nothing will happen. O(log₂n).
 *
 * @param tree `this`.
 * @param value Specified value.
 */
void AvlTreeRemove(AvlTree *const restrict tree,
                   const void *const restrict value);

/**
 * @brief Every value of elements in `tree` will be passed into `test()`
 * according to priority. If `test()` returns `TRUE` AT LEAST ONCE, `TRUE` will
 * be returned. Otherwise, `FALSE` will be returned. O(n).
 *
 * @param tree `this`.
 * @param test Function used in checking if some elements satisfy certain
 * conditions.
 */
Bool AvlTreeSome(AvlTree *const restrict tree, TestFunction *const test);

/**
 * @brief Every value of elements in `tree` will be passed into `test()`
 * according to priority. If `test()` ALWAYS returns `TRUE`, `TRUE` will
 * be returned. Otherwise, `FALSE` will be returned. O(n).
 *
 * @param tree `this`.
 * @param test Function used in checking if some elements satisfy certain
 * conditions.
 */
Bool AvlTreeAll(AvlTree *const restrict tree, TestFunction *const test);

#endif  // __COLLECTIONS_AVL_TREE__
