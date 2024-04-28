#ifndef __COLLECTIONS_ARRAY__
#define __COLLECTIONS_ARRAY__

#include "types.h"

/**
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `ArrayConstruct`, `ArrayNew`, `ArrayDestruct`, `ArrayDelete`.
 */
typedef struct {
    /**
     * @private
     * @warning Don't operate this member directly. Please use functions below.
     * @see `ArrayGet`, `ArraySet`.
     */
    void* array;
    /**
     * @private
     * @warning Don't operate this member directly.
     */
    unsigned long elementSize;
    /**
     * @private
     * @warning Don't operate this member directly.
     */
    CompareFunction* compare;

    /**
     * @public
     * @brief Current element quantity of this array.
     * @attention Don't change value of this member directly. It is maintained
     * automatically.
     */
    unsigned int Size;
    /**
     * @public
     * @brief Current element capacity of this array. If `Size` is going to be
     * larger than `Capacity`, this array will automatically expand its
     * capacity.
     * @attention Don't change value of this member directly. It is maintained
     * automatically.
     */
    unsigned int Capacity;
} Array;

/**
 * @brief Constructor function. O(1).
 *
 * @param array Target to be constructed.
 * @param initialCapacity Initial capacity of `array`.
 * @param elementSize Element size of `array`.
 * @param compare Function used in comparing two elements.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ArrayConstruct(Array* const restrict array,
                   const unsigned int initialCapacity,
                   const unsigned long elementSize,
                   CompareFunction* const compare);

/**
 * @brief Allocate a new array in heap. O(1).
 *
 * @param initialCapacity Initial capacity of array.
 * @param elementSize Element size of array.
 * @param compare Function used in comparing two elements.
 * @return Array* If successful, a pointer refering to a heap address will be
 * returned. Otherwise, `NULL` will be returned and `errno` will be set.
 */
Array* ArrayNew(const unsigned int initialCapacity,
                const unsigned long elementSize,
                CompareFunction* const compare);

/**
 * @brief Destructor function. O(1).
 *
 * @param array Target to be destructed. If `NULL`, nothing will happen.
 */
void ArrayDestruct(Array* const restrict array);

/**
 * @brief Release `array` in heap. O(1).
 *
 * @param array A pointer refers to the target to be deleted. The target will be
 * set to `NULL`. If `NULL`, nothing will happen.
 */
void ArrayDelete(Array** const restrict array);

/**
 * @brief Get the value of the element at specified `index`. O(1).
 * @attention The returned value is shallow copied from `array[index]`. Don't
 * free it.
 *
 * @param array `this`.
 * @param index Specified index.
 * @return void* If successful, the element will be returned. Otherwise, `NULL`
 * will be returned and `errno` will be set.
 */
void* ArrayGet(const Array* const restrict array, const unsigned int index);

/**
 * @brief Set the value of element at specified `index`. O(1).
 *
 * @param array `this`.
 * @param index Specified index.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ArraySet(Array* const restrict array, const unsigned int index,
             const void* const restrict value);

/**
 * @brief Get value of the last element. O(1).
 * @attention The returned value is shallow copied from `array[index]`. Don't
 * free it.
 *
 * @param array `this`.
 * @return void* If `array` is empty, `NULL` will be returned. If error, `NULL`
 * will be returned and `errno` will be set.
 */
void* ArrayBack(const Array* const restrict array);

/**
 * @brief Get value of the first element. O(1).
 * @attention The returned value is shallow copied from `array[index]`. Don't
 * free it.
 *
 * @param array `this`.
 * @return void* If `array` is empty, `NULL` will be returned. If error, `NULL`
 * will be returned and `errno` will be set.
 */
void* ArrayFront(const Array* const restrict array);

/**
 * @brief Add new element at the end of `array`. O(1).
 *
 * @param array `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ArrayPushBack(Array* const restrict array,
                  const void* const restrict value);

/**
 * @brief Remove the last element of `array`. O(1).
 *
 * @param array `this`.
 */
void ArrayPopBack(Array* const restrict array);

/**
 * @brief Add new element at the begin of `array`. O(n).
 *
 * @param array `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ArrayPushFront(Array* const restrict array,
                   const void* const restrict value);

/**
 * @brief Remove the first element of `array`. O(n).
 *
 * @param array `this`.
 */
void ArrayPopFront(Array* const restrict array);

/**
 * @brief Add new element at the specified index of `array`. After element
 * added, `array[index]` will be the new element. O(n).
 *
 * @param array `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ArrayInsert(Array* const restrict array, const unsigned int index,
                const void* const restrict value);

/**
 * @brief Find the element which is equal to `value`. O(n).
 *
 * @param array `this`.
 * @param value Specified value.
 * @return int If found, the index of the element will be returned. If not
 * found, only `-1` will be returned. If error, `-1` will be returned and
 * `errno` will be set.
 */
int ArrayFind(const Array* const restrict array,
              const void* const restrict value);

/**
 * @brief Slice `array`, and return new array which contains DEEP copied
 * elements from index `start`(contained) and has `size` elements. O(n).
 *
 * @param array `this`.
 * @param start Start index.
 * @param size Size of returned array.
 * @return Array* New array with DEEP copied elements. This pointer will NOT
 * automatically be released. If error, `NULL` will be returned and `errno` will
 * be set.
 */
Array* ArraySlice(const Array* const restrict array, const unsigned int start,
                  const unsigned int size);

#endif  // __COLLECTIONS_ARRAY__