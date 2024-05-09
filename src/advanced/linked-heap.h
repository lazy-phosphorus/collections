#ifndef __COLLECTIONS_LINKED_HEAP__
#define __COLLECTIONS_LINKED_HEAP__

#include "types.h"

/**
 * @brief Type of element in `LinkedHeap`.
 * @attention It is no recommended to use this struct.
 */
typedef struct __LinkedHeapNode {
    /**
     * @private
     * @brief Pointer refers to the parent node.
     */
    struct __LinkedHeapNode *parent;
    /**
     * @private
     * @brief Value of this node.
     */
    void *value;
    /**
     * @private
     * @brief Pointer refers to left child.
     */
    struct __LinkedHeapNode *left;
    /**
     * @private
     * @brief Pointer refers to right child.
     */
    struct __LinkedHeapNode *right;
} LinkedHeapNode;

/**
 * @attention It is not recommended to use this struct. Use `ArrayHeap` instead.
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `LinkedHeapConstruct()`, `LinkedHeapNew()`, `LinkedHeapDestruct()`,
 * `LinkedHeapDelete()`.
 */
typedef struct {
    /**
     * @private
     * @brief Pointer refers to the top element.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `LinkedHeapTop()`, `LinkedHeapPush()`, `LinkedHeapPop()`.
     */
    LinkedHeapNode *root;
    /**
     * @private
     * @brief Element size of this heap.
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
     * @brief Current element quantity of this heap.
     * @attention Don't modify the value of this member directly. It is
     * maintained automatically.
     */
    unsigned int Size;
} LinkedHeap;

/**
 * @brief Construct function. O(1).
 *
 * @param node Target to be constructed.
 * @param value Value of `node`. It will be DEEP copied.
 * @param elementSize Size of `value`.
 */
void LinkedHeapNodeConstruct(LinkedHeapNode *const restrict node,
                             const void *const restrict value,
                             unsigned long elementSize);

/**
 * @brief Allocate a new node in heap. O(1).
 *
 * @param value Value of node. It will be DEEP copied.
 * @param elementSize Size of `value`.
 * @return LinkedHeapNode* Pointer refering to a heap address.
 */
LinkedHeapNode *LinkedHeapNodeNew(const void *const restrict value,
                                  unsigned long elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param node Target to be destructed. If `NULL`, nothing will happen.
 */
void LinkedHeapNodeDestruct(LinkedHeapNode *const restrict node);

/**
 * @brief Release `node` in heap. O(1).
 *
 * @param node Pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void LinkedHeapNodeDelete(LinkedHeapNode **const restrict node);

/**
 * @brief Constructor function. O(1).
 *
 * @param heap Target to be constructed.
 * @param initialCapacity Initial capacity of `heap`.
 * @param elementSize Element size of `heap`.
 * @param compare Function used in comparing two elements.
 */
void LinkedHeapConstruct(LinkedHeap *const restrict heap,
                         const unsigned long elementSize,
                         CompareFunction *const compare);

/**
 * @brief Allocate a new heap in heap. O(1).
 *
 * @param initialCapacity Initial capacity of heap.
 * @param elementSize Element size of heap.
 * @param compare Function used in comparing two elements.
 * @return LinkedHeap* Pointer refering to a heap address.
 */
LinkedHeap *LinkedHeapNew(const unsigned long elementSize,
                          CompareFunction *const compare);

/**
 * @brief Destruct function. O(n).
 *
 * @param heap Target to be destructed. If `NULL`, nothing will happen.
 */
void LinkedHeapDestruct(LinkedHeap *const restrict heap);

/**
 * @brief Release `heap` in heap. O(n).
 *
 * @param heap Pointer refers to the target which is to be deleted. The
 * target will be set to `NULL`. If `NULL`, nothing will happen.
 */
void LinkedHeapDelete(LinkedHeap **const restrict heap);

/**
 * @brief Get value of the element which is on the top of `heap`. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param heap `this`.
 * @return void* If successful, value of the element will be returned.
 * Otherwise, `NULL` will be returned.
 */
void *LinkedHeapTop(const LinkedHeap *const restrict heap);

/**
 * @brief Add a new element into `heap. O(n).
 * @attention `ArrayQueue` is used inside.
 *
 * @param heap `this`.
 * @param value Value of element. It will be DEEP copied.
 */
void LinkedHeapPush(LinkedHeap *const restrict heap,
                    const void *const restrict value);

/**
 * @brief Remove the element which is on the top of `heap`. O(n).
 * @attention `ArrayQueue` is used inside.
 *
 * @param heap `this`
 */
void LinkedHeapPop(LinkedHeap *const restrict heap);

#endif  // __COLLECTIONS_LINKED_HEAP__
