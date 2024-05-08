#ifndef __COLLECTIONS_PRIORITY_QUEUE__
#define __COLLECTIONS_PRIORITY_QUEUE__

#include "basic/array-heap.h"
#include "types.h"

typedef struct {
    int priority;
    void *value;
} PriorityQueueNode;

typedef struct {
    ArrayHeap *heap;
    unsigned long elementSize;

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
 *
 * @param queue `this`
 * @param test Function used in checking if some elements satisfy certain
 * conditions.
 */
Bool PriorityQueueSome(PriorityQueue *const restrict queue,
                       TestFunction *const test);

/**
 * @brief Every value of elements in `queue` will be passed into `test()`. If
 * `test()` ALWAYS returns `TRUE`, `TRUE` will be returned. Otherwise,
 * `FALSE` will be returned. O(n).
 *
 * @param queue `this`
 * @param test Function used in checking if some elements satisfy certain
 * conditions.
 */
Bool PriorityQueueAll(PriorityQueue *const restrict queue,
                      TestFunction *const test);

#endif  // __COLLECTIONS_PRIORITY_QUEUE__
