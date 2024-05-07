#ifndef __COLLECTIONS_ARRAY_QUEUE__
#define __COLLECTIONS_ARRAY_QUEUE__

/**
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `ArrayQueueConstruct`, `ArrayQueueNew`, `ArrayQueueDestruct`,
 * `ArrayQueueDelete`.
 */
typedef struct {
    /**
     * @private
     * @brief Pointer refers to the first element.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `ArrayQueueTop`, `ArrayQueuePop`.
     */
    void *array;
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
    /**
     * @public
     * @brief Current element capacity of this queue. If `Size` is going to be
     * larger than `Capacity`, this queue will automatically expand its
     * capacity.
     * @attention Don't change value of this member directly. It is maintained
     * automatically.
     */
    unsigned int Capacity;
} ArrayQueue;

/**
 * @brief Construct function. O(1).
 *
 * @param queue Target to be constructed.
 * @param initialCapacity Initial capacity of `queue`.
 * @param elementSize Element size of `queue`.
 */
void ArrayQueueConstruct(ArrayQueue *const restrict queue,
                         const unsigned int initialCapacity,
                         const unsigned long elementSize);

/**
 * @brief Allocate a new queue in heap. O(1).
 *
 * @param initialCapacity Initial capacity of `queue`.
 * @param elementSize Element size of queue.
 * @return LinkedStack* Pointer refering to a heap address.
 */
ArrayQueue *ArrayQueueNew(const unsigned int initialCapacity,
                          const unsigned long elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param queue Target to be destructed. If `NULL`, nothing will happen.
 */
void ArrayQueueDestruct(ArrayQueue *const restrict queue);

/**
 * @brief Release `queue` in heap. O(1).
 *
 * @param queue Pointer refers to the target which is to be deleted. The
 * target will be set to `NULL. If `NULL`, nothing will happen.
 */
void ArrayQueueDelete(ArrayQueue **const restrict queue);

/**
 * @brief Get value of the first element in `queue`. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param queue `this`.
 * @return void* If successful, the element will be returned. Otherwise, `NULL`
 * will be returned.
 */
void *ArrayQueueFront(const ArrayQueue *const restrict queue);

/**
 * @brief Push new element into `queue`. O(1).
 *
 * @param queue `this`.
 * @param value Value of element. It will be DEEP copied.
 */
void ArrayQueuePush(ArrayQueue *const restrict queue,
                    const void *const restrict value);

/**
 * @brief Remove the first element in `queue`. O(n).
 *
 * @param queue `this`.
 */
void ArrayQueuePop(ArrayQueue *const restrict queue);

#endif  // __COLLECTIONS_ARRAY_QUEUE__
