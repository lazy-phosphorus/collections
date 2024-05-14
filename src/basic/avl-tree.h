#ifndef __COLLECTIONS_AVL_TREE__
#define __COLLECTIONS_AVL_TREE__

#include "types.h"

/**
 * @brief Type of element in `AvlTree`.
 * @attention It is no recommended to use this struct.
 */
typedef struct __AvlTreeNode {
    /**
     * @private
     * @brief Pointer refers to the parent node.
     */
    struct __AvlTreeNode *parent;
    /**
     * @private
     * @brief Value of this node.
     */
    void *value;
    /**
     * @private
     * @brief Height of this node.
     */
    unsigned int height;
    /**
     * @private
     * @brief Pointer refers to the right child.
     */
    struct __AvlTreeNode *right;
    /**
     * @private
     * @brief Pointer refers to the left child.
     */
    struct __AvlTreeNode *left;
} AvlTreeNode;

/**
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `AvlTreeConstruct()`, `AvlTreeNew()`, `AvlTreeDestruct()`,
 * `AvlTreeDelete()`.
 */
typedef struct {
    /**
     * @private
     * @brief Pointer refers to the root node.
     * @warning Don't modify thie member directly. Please use functions below.
     * @see `AvlTreeInsert()`, `AvlTreeRemove()`.
     */
    AvlTreeNode *root;
    /**
     * @private
     * @brief Element size of this tree.
     * @warning Don't modify this member directly.
     */
    unsigned long elementSize;
    /**
     * @private
     * @brief Functions used in comparing two elements.
     * @warning Don't modify this member directly.
     */
    CompareFunction *compare;

    /**
     * @public
     * @brief Current element quantity of this tree.
     * @attention Don't modify the value of this member directly. It is
     * maintained automatically.
     */
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
 * according to priority. If `test()` returns `TRUE`, `TRUE` will be returned
 * immediately. If `FALSE` is always returned by `test()`, `FALSE` will be
 * returned. O(n).
 *
 * @param tree `this`.
 * @param test Function used in checking if some elements satisfy certain
 * conditions.
 * @return Bool
 */
Bool AvlTreeSome(AvlTree *const restrict tree, TestFunction *const test);

/**
 * @brief Every value of elements in `tree` will be passed into `test()`
 * according to priority. If `test()` returns `FALSE`, `FALSE` will be returned
 * immediately. If `TRUE` is always returned by `test()`, `TRUE` will be
 * returned. O(n).
 *
 * @param tree `this`.
 * @param test Function used in checking if some elements satisfy certain
 * conditions.
 * @return Bool
 */
Bool AvlTreeAll(AvlTree *const restrict tree, TestFunction *const test);

#endif  // __COLLECTIONS_AVL_TREE__
