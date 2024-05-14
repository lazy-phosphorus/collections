#ifndef __COLLECTIONS_LINKED_QUEUE__
#define __COLLECTIONS_LINKED_QUEUE__

#include "types.h"

/**
 * @brief Type of element in `LinkedQueue`.
 * @attention It is not recommended to use this struct.
 * @see `LinkedQueueGetIterator()`, `LinkedQueueIteratorNext()`,
 * `LinkedQueueIteratorGetValue()`, `LinkedQueueIteratorEnded()`
 */
typedef struct __LinkedQueueNode {
    /**
     * @private
     * @brief Value of this node.
     */
    void *value;
    /**
     * @private
     * @brief Pointer refers to the next node.
     */
    struct __LinkedQueueNode *next;
} LinkedQueueNode;

/**
 * @brief Iterator of `LinkedQueue`.
 * @attention This iterator has no void head node. You can call
 * `LinkedQueueIteratorGetValue()` directly.
 */
typedef LinkedQueueNode *LinkedQueueIterator;

/**
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `LinkedQueueConstruct()`, `LinkedQueueNew()`, `LinkedQueueDestruct()`,
 * `LinkedQueueDelete()`.
 */
typedef struct {
    /**
     * @private
     * @brief Pointer refers to the first element.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `LinkedQueueTop()`, `LinkedQueuePop()`.
     */
    LinkedQueueNode *head;
    /**
     * @private
     * @brief Pointer refers to the last element.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `LinkedQueuePush()`.
     */
    LinkedQueueNode *tail;
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
} LinkedQueue;

/**
 * @brief Construct function. O(1).
 *
 * @param node Target to be constructed.
 * @param value Value of `node`. It will be DEEP copied.
 * @param elementSize Size of `value`.
 */
void LinkedQueueNodeConstruct(LinkedQueueNode *const restrict node,
                              const void *const restrict value,
                              const unsigned long elementSize);

/**
 * @brief Allocate a new node in heap. O(1).
 *
 * @param value Value of node. It will be DEEP copied.
 * @param elementSize Size of `value`.
 * @return LinkedStackNode* Pointer refering to a heap address.
 */
LinkedQueueNode *LinkedQueueNodeNew(const void *const restrict value,
                                    const unsigned long elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param node Target to be destructed. If `NULL`, nothing will happen.
 */
void LinkedQueueNodeDestruct(LinkedQueueNode *const restrict node);

/**
 * @brief Release `node` in heap. O(1).
 *
 * @param node Pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void LinkedQueueNodeDelete(LinkedQueueNode **const restrict node);

/**
 * @brief Construct function. O(1).
 *
 * @param queue Target to be constructed.
 * @param elementSize Element size of `queue`.
 */
void LinkedQueueConstruct(LinkedQueue *const restrict queue,
                          const unsigned long elementSize);

/**
 * @brief Allocate a new queue in heap. O(1).
 *
 * @param elementSize Element size of queue.
 * @return LinkedStack* Pointer refering to a heap address.
 */
LinkedQueue *LinkedQueueNew(const unsigned long elementSize);

/**
 * @brief Destruct function. O(n).
 *
 * @param queue Target to be destructed. If `NULL`, nothing will happen.
 */
void LinkedQueueDestruct(LinkedQueue *const restrict queue);

/**
 * @brief Release `queue` in heap. O(n).
 *
 * @param stack Pointer refers to the target which is to be deleted. The
 * target will be set to `NULL. If `NULL`, nothing will happen.
 */
void LinkedQueueDelete(LinkedQueue **const restrict queue);

/**
 * @brief Get value of the first element in `queue`. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param queue `this`.
 * @return void* If successful, the element will be returned. Otherwise, `NULL`
 * will be returned.
 */
void *LinkedQueueFront(const LinkedQueue *const restrict queue);

/**
 * @brief Push new element into `queue`. O(1).
 *
 * @param queue `this`.
 * @param value Value of element. It will be DEEP copied.
 */
void LinkedQueuePush(LinkedQueue *const restrict queue,
                     const void *const restrict value);

/**
 * @brief Remove the first element in `queue`. O(1).
 *
 * @param queue `this`.
 */
void LinkedQueuePop(LinkedQueue *const restrict queue);

/**
 * @brief Every value of elements in `queue` will be passed into `test()`. If
 * `test()` returns `TRUE` AT LEAST ONCE, `TRUE` will be returned. Otherwise,
 * `FALSE` will be returned. O(n).
 *
 * @param queue `this`.
 * @param test Function used in checking if some elements satisfy certain
 * conditions.
 */
Bool LinkedQueueSome(LinkedQueue *const restrict queue,
                     TestFunction *const test);

/**
 * @brief Every value of elements in `queue` will be passed into `test()`. If
 * `test()` ALWAYS returns `TRUE`, `TRUE` will be returned. Otherwise,
 * `FALSE` will be returned. O(n).
 *
 * @param queue `this`.
 * @param test Function used in checking if some elements satisfy certain
 * conditions.
 */
Bool LinkedQueueAll(LinkedQueue *const restrict queue,
                    TestFunction *const test);

/**
 * @brief Get iterator of `queue`. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param queue `this`.
 * @return LinkedQueueIterator Iterator SHALLOW copied from `queue->head`.
 */
LinkedQueueIterator LinkedQueueGetIterator(LinkedQueue *const restrict queue);

/**
 * @brief Move to the next element. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param iterator `this`.
 * @return LinkedQueueIterator Renewed iterator.
 */
LinkedQueueIterator LinkedQueueIteratorNext(
    LinkedQueueIterator const restrict iterator);

/**
 * @brief Get value of current element. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param iterator `this`.
 * @return void* Value of element.
 */
void *LinkedQueueIteratorGetValue(LinkedQueueIterator const restrict iterator);

/**
 * @brief Check if iterator reaches end. O(1).
 *
 * @param iterator `this`.
 * @return Bool.
 */
Bool LinkedQueueIteratorEnded(LinkedQueueIterator const restrict iterator);

#endif  // __COLLECTIONS_LINKED_QUEUE__
