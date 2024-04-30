#ifndef __COLLECTIONS_ARRAY_STACK__
#define __COLLECTIONS_ARRAY_STACK__

/**
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `ArrayStackConstruct`, `ArrayStackNew`, `ArrayStackDestruct`,
 * `ArrayStackDelete`.
 */
typedef struct {
    /**
     * @private
     * @brief All elements will be stored in this member.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `ArrayStackPush`, `ArrayStackPop`.
     */
    void* array;
    /**
     * @private
     * @brief Element size of this stack.
     * @warning Don't modify this member directly.
     */
    unsigned long elementSize;

    /**
     * @public
     * @brief Current element quantity of this stack.
     * @attention Don't change value of this member directly. It is maintained
     * automatically.
     */
    unsigned int Size;
    /**
     * @public
     * @brief Current element capacity of this stack. If `Size` is going to be
     * larger than `Capacity`, this stack will automatically expand its
     * capacity.
     * @attention Don't change value of this member directly. It is maintained
     * automatically.
     */
    unsigned int Capacity;
} ArrayStack;

/**
 * @brief Construct function. O(1).
 *
 * @param stack Target to be constructed.
 * @param initialCapacity Initial capacity of `stack`.
 * @param elementSize Element size of `stack`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ArrayStackConstruct(ArrayStack* const restrict stack,
                        const unsigned int initialCapacity,
                        const unsigned long elementSize);

/**
 * @brief Allocate a new stack in heap. O(1).
 *
 * @param initialCapacity Initial capacity of `stack`.
 * @param elementSize Element size of stack.
 * @return ArrayStack* If successful, a pointer refering to a heap address will
 * be returned. Otherwise, `NULL` will be returned and `errno` will be set.
 */
ArrayStack* ArrayStackNew(const unsigned int initialCapacity,
                          const unsigned long elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param stack Target to be destructed. If `NULL`, nothing will happen.
 */
void ArrayStackDestruct(ArrayStack* const restrict stack);

/**
 * @brief Release `stack` in heap. O(1).
 *
 * @param stack A pointer refers to the target which is to be deleted. The
 * target will be set to `NULL. If `NULL`, nothing will happen.
 */
void ArrayStackDelete(ArrayStack** const restrict stack);

/**
 * @brief Get value of the element which is on the top of `stack`. O(1).
 *
 * @param stack `this`.
 * @return void* If successful, the element will be returned. Otherwise, `NULL`
 * will be returned and `errno` will be set.
 */
void* ArrayStackTop(const ArrayStack* const restrict stack);

/**
 * @brief Push new element into `stack`. O(1).
 *
 * @param stack `this`.
 * @param value Value of element.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ArrayStackPush(ArrayStack* const restrict stack,
                   const void* const restrict value);

/**
 * @brief Remove the element which is on the top of `stack`. O(1).
 *
 * @param stack `this`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ArrayStackPop(ArrayStack* const restrict stack);

#endif  // __COLLECTIONS_ARRAY_STACK__