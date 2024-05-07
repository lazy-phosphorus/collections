#ifndef __COLLECTIONS_ARRAY_LIST__
#define __COLLECTIONS_ARRAY_LIST__

#include "types.h"

/**
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `ArrayListConstruct`, `ArrayListNew`, `ArrayListDestruct`,
 * `ArrayListDelete`.
 */
typedef struct {
    /**
     * @private
     * @brief All elements will be stored in this member.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `ArrayListGet`, `ArrayListSet`.
     */
    void *array;
    /**
     * @private
     * @brief Element size of this list.
     * @warning Don't modify this member directly.
     */
    unsigned long elementSize;
    /**
     * @private
     * @brief Function used in comparing two elements.
     * @warning Don't modify this member directly.
     */
    CompareFunction *compare;

    /**
     * @public
     * @brief Current element quantity of this list.
     * @attention Don't change value of this member directly. It is maintained
     * automatically.
     */
    unsigned int Size;
    /**
     * @public
     * @brief Current element capacity of this list. If `Size` is going to be
     * larger than `Capacity`, this list will automatically expand its
     * capacity.
     * @attention Don't change value of this member directly. It is maintained
     * automatically.
     */
    unsigned int Capacity;
} ArrayList;

/**
 * @brief Constructor function. O(1).
 *
 * @param list Target to be constructed.
 * @param initialCapacity Initial capacity of `list`.
 * @param elementSize Element size of `list`.
 * @param compare Function used in comparing two elements.
 */
void ArrayListConstruct(ArrayList *const restrict list,
                        const unsigned int initialCapacity,
                        const unsigned long elementSize,
                        CompareFunction *const compare);

/**
 * @brief Allocate a new list in heap. O(1).
 *
 * @param initialCapacity Initial capacity of list.
 * @param elementSize Element size of list.
 * @param compare Function used in comparing two elements.
 * @return ArrayList* Pointer refering to a heap address.
 */
ArrayList *ArrayListNew(const unsigned int initialCapacity,
                        const unsigned long elementSize,
                        CompareFunction *const compare);

/**
 * @brief Destruct function. O(1).
 *
 * @param list Target to be destructed. If `NULL`, nothing will happen.
 */
void ArrayListDestruct(ArrayList *const restrict list);

/**
 * @brief Release `list` in heap. O(1).
 *
 * @param list Pointer refers to the target which is to be deleted. The
 * target will be set to `NULL`. If `NULL`, nothing will happen.
 */
void ArrayListDelete(ArrayList **const restrict list);

/**
 * @brief Get the value of the element at specified `index`. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param list `this`.
 * @param index Specified index.
 * @return void* If successful, the element will be returned. Otherwise, `NULL`
 * will be returned.
 */
void *ArrayListGet(const ArrayList *const restrict list,
                   const unsigned int index);

/**
 * @brief Set the value of element at specified `index`. O(1).
 *
 * @param list `this`.
 * @param index Specified index.
 * @param value Value of element. It will be DEEP copied.
 */
void ArrayListSet(ArrayList *const restrict list, const unsigned int index,
                  const void *const restrict value);

/**
 * @brief Get value of the last element. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param list `this`.
 * @return void* If `list` is empty, `NULL` will be returned.
 */
void *ArrayListBack(const ArrayList *const restrict list);

/**
 * @brief Get value of the first element. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param list `this`.
 * @return void* If `list` is empty, `NULL` will be returned.
 */
void *ArrayListFront(const ArrayList *const restrict list);

/**
 * @brief Add new element at the end of `list`. O(1).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 */
void ArrayListPushBack(ArrayList *const restrict list,
                       const void *const restrict value);

/**
 * @brief Remove the last element of `list`. O(1).
 *
 * @param list `this`.
 */
void ArrayListPopBack(ArrayList *const restrict list);

/**
 * @brief Add new element at the begin of `list`. O(n).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 */
void ArrayListPushFront(ArrayList *const restrict list,
                        const void *const restrict value);

/**
 * @brief Remove the first element of `list`. O(n).
 *
 * @param list `this`.
 */
void ArrayListPopFront(ArrayList *const restrict list);

/**
 * @brief Add new element at the specified index of `list`. After element
 * added, `list[index]` will be the new element. O(n).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 */
void ArrayListInsert(ArrayList *const restrict list, const unsigned int index,
                     const void *const restrict value);

/**
 * @brief Find the element which is equal to `value`. O(n).
 *
 * @param list `this`.
 * @param value Specified value.
 * @return int If found, the index of the element will be returned. Otherwise,
 * `-1` will be returned.
 */
int ArrayListFind(const ArrayList *const restrict list,
                  const void *const restrict value);

/**
 * @brief Slice `list`, and return new list which contains DEEP copied
 * elements from index `start`(contained) and has `size` elements. O(n).
 *
 * @param list `this`.
 * @param start Start index.
 * @param size Size of returned list.
 * @return ArrayList* New list with DEEP copied elements. This pointer will NOT
 * automatically be released.
 */
ArrayList *ArrayListSlice(const ArrayList *const restrict list,
                          const unsigned int start, const unsigned int size);

/**
 * @brief Use quick sort algorithm to sort `list`. O(nlog₂n).
 *
 * @param list `this`.
 */
void ArrayListQuickSort(ArrayList *const restrict list);

#endif  // __COLLECTIONS_ARRAY_LIST__
