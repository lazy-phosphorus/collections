#ifndef __COLLECTIONS_LINKED_QUEUE__
#define __COLLECTIONS_LINKED_QUEUE__

/**
 * @brief Type of element in `LinkedQueue`.
 * @attention It is not recommended to use this struct.
 */
typedef struct __LinkedQueueNode {
    /**
     * @private
     * @brief Value of this node.
     */
    void* value;
    /**
     * @private
     * @brief Pointer refers to the next node.
     */
    struct __LinkedQueueNode* next;
} LinkedQueueNode;

/**
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `LinkedQueueConstruct`, `LinkedQueueNew`, `LinkedQueueDestruct`,
 * `LinkedQueueDelete`.
 */
typedef struct {
    /**
     * @private
     * @brief Pointer refers to the first element.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `LinkedQueueTop`, `LinkedQueuePop`.
     */
    LinkedQueueNode* head;
    /**
     * @private
     * @brief Pointer refers to the last element.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `LinkedQueuePush`.
     */
    LinkedQueueNode* tail;
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
void LinkedQueueNodeConstruct(LinkedQueueNode* const restrict node,
                              const void* const restrict value,
                              const unsigned long elementSize);

/**
 * @brief Allocate a new node in heap. O(1).
 *
 * @param value Value of node. It will be DEEP copied.
 * @param elementSize Size of `value`.
 * @return LinkedStackNode* Pointer refering to a heap address.
 */
LinkedQueueNode* LinkedQueueNodeNew(const void* const restrict value,
                                    const unsigned long elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param node Target to be destructed. If `NULL`, nothing will happen.
 */
void LinkedQueueNodeDestruct(LinkedQueueNode* const restrict node);

/**
 * @brief Release `node` in heap. O(1).
 *
 * @param node Pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void LinkedQueueNodeDelete(LinkedQueueNode** const restrict node);

/**
 * @brief Construct function. O(1).
 *
 * @param queue Target to be constructed.
 * @param elementSize Element size of `queue`.
 */
void LinkedQueueConstruct(LinkedQueue* const restrict queue,
                          const unsigned long elementSize);

/**
 * @brief Allocate a new queue in heap. O(1).
 *
 * @param elementSize Element size of queue.
 * @return LinkedStack* Pointer refering to a heap address.
 */
LinkedQueue* LinkedQueueNew(const unsigned long elementSize);

/**
 * @brief Destruct function. O(n).
 *
 * @param queue Target to be destructed. If `NULL`, nothing will happen.
 */
void LinkedQueueDestruct(LinkedQueue* const restrict queue);

/**
 * @brief Release `queue` in heap. O(n).
 *
 * @param stack Pointer refers to the target which is to be deleted. The
 * target will be set to `NULL. If `NULL`, nothing will happen.
 */
void LinkedQueueDelete(LinkedQueue** const restrict queue);

/**
 * @brief Get value of the first element in `queue`. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param queue `this`.
 * @return void* If successful, the element will be returned. Otherwise, `NULL`
 * will be returned.
 */
void* LinkedQueueFront(const LinkedQueue* const restrict queue);

/**
 * @brief Push new element into `queue`. O(1).
 *
 * @param queue `this`.
 * @param value Value of element. It will be DEEP copied.
 */
void LinkedQueuePush(LinkedQueue* const restrict queue,
                     const void* const restrict value);

/**
 * @brief Remove the first element in `queue`. O(1).
 *
 * @param queue `this`.
 */
void LinkedQueuePop(LinkedQueue* const restrict queue);

#endif  // __COLLECTIONS_LINKED_QUEUE__
