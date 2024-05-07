#ifndef __COLLECTIONS_ARRAY_HEAP__
#define __COLLECTIONS_ARRAY_HEAP__

#include "types.h"

/**
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `ArrayHeapConstruct`, `ArrayHeapNew`, `ArrayHeapDestruct`,
 * `ArrayHeapDelete`.
 */
typedef struct {
    /**
     * @private
     * @brief All elements will be stored in this member.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `ArrayHeapTop`, `ArrayHeapPush`, `ArrayHeapPop`.
     */
    void* array;
    /**
     * @private
     * @brief Element size of this heap.
     * @warning Don't modify this member directly.
     */
    unsigned long elementSize;
    /**
     * @private
     * @brief Function used in comparing two elements.
     * @warning Don't modify this member directly.
     */
    CompareFunction* compare;

    /**
     * @public
     * @brief Current element quantity of this heap.
     * @attention Don't change value of this member directly. It is maintained
     * automatically.
     */
    unsigned int Size;
    /**
     * @public
     * @brief Current element capacity of this heap. If `Size` is going to be
     * larger than `Capacity`, this heap will automatically expand its
     * capacity.
     * @attention Don't change value of this member directly. It is maintained
     * automatically.
     */
    unsigned int Capacity;
} ArrayHeap;

/**
 * @brief Constructor function. O(1).
 *
 * @param heap Target to be constructed.
 * @param initialCapacity Initial capacity of `heap`.
 * @param elementSize Element size of `heap`.
 * @param compare Function used in comparing two elements.
 */
void ArrayHeapConstruct(ArrayHeap* const restrict heap,
                        const unsigned int initialCapacity,
                        const unsigned long elementSize,
                        CompareFunction* const compare);

/**
 * @brief Allocate a new heap in heap. O(1).
 *
 * @param initialCapacity Initial capacity of heap.
 * @param elementSize Element size of heap.
 * @param compare Function used in comparing two elements.
 * @return ArrayHeap* Pointer refering to a heap address.
 */
ArrayHeap* ArrayHeapNew(const unsigned int initialCapacity,
                        const unsigned long elementSize,
                        CompareFunction* const compare);

/**
 * @brief Destruct function. O(1).
 *
 * @param heap Target to be destructed. If `NULL`, nothing will happen.
 */
void ArrayHeapDestruct(ArrayHeap* const restrict heap);

/**
 * @brief Release `heap` in heap. O(1).
 *
 * @param heap Pointer refers to the target which is to be deleted. The
 * target will be set to `NULL`. If `NULL`, nothing will happen.
 */
void ArrayHeapDelete(ArrayHeap** const restrict heap);

/**
 * @brief Get value of the element which is on the top of `heap`. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param heap `this`.
 * @return void* If successful, value of the element will be returned.
 * Otherwise, `NULL` will be returned.
 */
void* ArrayHeapTop(const ArrayHeap* const restrict heap);

/**
 * @brief Add a new element into `heap. O(log₂n).
 *
 * @param heap `this`.
 * @param value Value of element. It will be DEEP copied.
 */
void ArrayHeapPush(ArrayHeap* const restrict heap,
                   const void* const restrict value);

/**
 * @brief Remove the element which is on the top of `heap`. O(log₂n).
 *
 * @param heap `this`
 */
void ArrayHeapPop(ArrayHeap* const restrict heap);

#endif  // __COLLECTIONS_ARRAY_HEAP__
