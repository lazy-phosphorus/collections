#ifndef __COLLECTIONS_PRIORITY_QUEUE__
#define __COLLECTIONS_PRIORITY_QUEUE__

#include "array-heap.h"
#include "types.h"

/**
 * @brief Type of element in `PriorityQueue`.
 * @attention It is no recommended to use this struct.
 */
typedef struct {
    /**
     * @private
     * @brief Priority of this node.
     */
    int priority;
    /**
     * @private
     * @brief Value of this node.
     */
    void *value;
} PriorityQueueNode;

typedef ArrayHeapIterator PriorityQueueIterator;

/**
 * @brief This struct is implemented by `ArrayHeap`.
 * @attention There is no similar struct implemented by `LinkedHeap`. Because
 * level order traversal is needed while pushing element into `LinkedHeap`,
 * which will use queue.
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `PriorityQueueConstruct()`, `PriorityQueueNew()`,
 * `PriorityQueueDestruct()`, `PriorityQueueDelete()`.
 */
typedef struct {
    /**
     * @private
     * @brief Heap.
     * @warning Don't modify this member directly. It is maintained
     * automatically.
     * @see `PriorityQueueFront()`, `PriorityQueuePush()`, `PriorityQueuePop()`.
     */
    ArrayHeap *heap;
    /**
     * @private
     * @brief Element size of this queue.
     * @warning Don't modify this member directly.
     */
    unsigned long elementSize;

    /**
     * @public
     * @brief Current element quantity of this queue.
     * @attention Don't modify the value of this member directly. It is
     * maintained automatically.
     */
    unsigned int Size;
} PriorityQueue;

/**
 * @brief Construct function. O(1).
 *
 * @param node Target to be constructed.
 * @param priority Priority of `node`.
 * @param value Value of `node`. It will be DEEP copied.
 * @param elementSize Size of `value`.
 */
void PriorityQueueNodeConstruct(PriorityQueueNode *const restrict node,
                                const int priority,
                                const void *const restrict value,
                                unsigned long elementSize);

/**
 * @brief Allocate a new node in heap. O(1).
 *
 * @param value Value of node. It will be DEEP copied.
 * @param priority Priority of node.
 * @param elementSize Size of `value`.
 * @return PriorityQueueNode* Pointer refering to a heap address.
 */
PriorityQueueNode *PriorityQueueNodeNew(const int priority,
                                        const void *const restrict value,
                                        unsigned long elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param node Target to be destructed. If `NULL`, nothing will happen.
 */
void PriorityQueueNodeDestruct(PriorityQueueNode *const restrict node);

/**
 * @brief Release `node` in heap. O(1).
 *
 * @param node Pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void PriorityQueueNodeDelete(PriorityQueueNode **const restrict node);

/**
 * @brief Constructor function. O(1).
 *
 * @param queue Target to be constructed.
 * @param initialCapacity Initial capacity of `queue`.
 * @param elementSize Element size of `queue`.
 */
void PriorityQueueConstruct(PriorityQueue *const restrict queue,
                            const unsigned int initialCapacity,
                            const unsigned long elementSize);

/**
 * @brief Allocate a new queue in queue. O(1).
 *
 * @param initialCapacity Initial capacity of queue.
 * @param elementSize Element size of queue.
 * @return PriorityQueue* Pointer refering to a queue address.
 */
PriorityQueue *PriorityQueueNew(const unsigned int initialCapacity,
                                const unsigned long elementSize);

/**
 * @brief Destruct function. O(n).
 *
 * @param queue Target to be destructed. If `NULL`, nothing will happen.
 */
void PriorityQueueDestruct(PriorityQueue *const restrict queue);

/**
 * @brief Release `queue` in queue. O(n).
 *
 * @param queue Pointer refers to the target which is to be deleted. The
 * target will be set to `NULL`. If `NULL`, nothing will happen.
 */
void PriorityQueueDelete(PriorityQueue **const restrict queue);

/**
 * @brief Get value of the first element of `queue`. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param queue `this`.
 * @return void* If successful, value of the element will be returned.
 * Otherwise, `NULL` will be returned.
 */
void *PriorityQueueFront(const PriorityQueue *const restrict queue);

/**
 * @brief Add a new element into `queue. O(log₂n).
 *
 * @param queue `this`.
 * @param value Value of element. It will be DEEP copied.
 */
void PriorityQueuePush(PriorityQueue *const restrict queue, const int priority,
                       const void *const restrict value);

/**
 * @brief Remove the first element of `queue`. O(log₂n).
 *
 * @param queue `this`
 */
void PriorityQueuePop(PriorityQueue *const restrict queue);

/**
 * @brief Every value of elements in `queue` will be passed into `test()`. If
 * `test()` returns `TRUE` AT LEAST ONCE, `TRUE` will be returned. Otherwise,
 * `FALSE` will be returned. O(n).
 * @attention This function will try to visit every element until `test()`
 * returns `TRUE`, but it will NOT adhere to the priority order.
 *
 * @param queue `this`.
 * @param test Function used in checking if some elements satisfy certain
 * conditions.
 */
Bool PriorityQueueSome(PriorityQueue *const restrict queue,
                       TestFunction *const test);

/**
 * @brief Every value of elements in `queue` will be passed into `test()`. If
 * `test()` ALWAYS returns `TRUE`, `TRUE` will be returned. Otherwise,
 * `FALSE` will be returned. O(n).
 * @attention This function will try to visit every element until `test()`
 * returns `FALSE`, but it will NOT adhere to the priority order.
 *
 * @param queue `this`.
 * @param test Function used in checking if some elements satisfy certain
 * conditions.
 */
Bool PriorityQueueAll(PriorityQueue *const restrict queue,
                      TestFunction *const test);

/**
 * @brief Get iterator of `queue`. O(1).
 *
 * @param queue `this`.
 * @return PriorityQueueIterator Iterator.
 */
PriorityQueueIterator PriorityQueueGetIterator(
    PriorityQueue *const restrict queue);

/**
 * @brief Get reverse iterator of `queue`. O(1).
 *
 * @param queue `this`.
 * @return PriorityQueueIterator Iterator.
 */
PriorityQueueIterator PriorityQueueGetReverseIterator(
    PriorityQueue *const restrict queue);

/**
 * @brief Move to the next element. O(1).
 *
 * @param iterator `this`.
 * @return PriorityQueueIterator Renewed iterator.
 */
PriorityQueueIterator PriorityQueueIteratorNext(
    PriorityQueueIterator const iterator);

/**
 * @brief Move to the previous element. O(1).
 *
 * @param iterator `this`.
 * @return PriorityQueueIterator Renewed iterator.
 */
PriorityQueueIterator PriorityQueueIteratorPrevious(
    PriorityQueueIterator const iterator);

/**
 * @brief Get value of current element. O(1).
 *
 * @param iterator `this`.
 * @return void* Value of element.
 */
void *PriorityQueueIteratorGetValue(PriorityQueueIterator const iterator);

/**
 * @brief Check if iterator reaches end. O(1).
 *
 * @param iterator `this`.
 * @return Bool.
 */
Bool PriorityQueueIteratorEnded(PriorityQueueIterator const iterator);

#endif  // __COLLECTIONS_PRIORITY_QUEUE__
