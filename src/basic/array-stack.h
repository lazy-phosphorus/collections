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
    void *array;
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
 */
void ArrayStackConstruct(ArrayStack *const restrict stack,
                         const unsigned int initialCapacity,
                         const unsigned long elementSize);

/**
 * @brief Allocate a new stack in heap. O(1).
 *
 * @param initialCapacity Initial capacity of `stack`.
 * @param elementSize Element size of stack.
 * @return ArrayStack* Pointer refering to a heap address.
 */
ArrayStack *ArrayStackNew(const unsigned int initialCapacity,
                          const unsigned long elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param stack Target to be destructed. If `NULL`, nothing will happen.
 */
void ArrayStackDestruct(ArrayStack *const restrict stack);

/**
 * @brief Release `stack` in heap. O(1).
 *
 * @param stack Pointer refers to the target which is to be deleted. The
 * target will be set to `NULL. If `NULL`, nothing will happen.
 */
void ArrayStackDelete(ArrayStack **const restrict stack);

/**
 * @brief Get value of the element which is on the top of `stack`. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param stack `this`.
 * @return void* If successful, the element will be returned. Otherwise, `NULL`
 * will be returned.
 */
void *ArrayStackTop(const ArrayStack *const restrict stack);

/**
 * @brief Push new element into `stack`. O(1).
 *
 * @param stack `this`.
 * @param value Value of element. It will be DEEP copied.
 */
void ArrayStackPush(ArrayStack *const restrict stack,
                    const void *const restrict value);

/**
 * @brief Remove the element which is on the top of `stack`. O(1).
 *
 * @param stack `this`.
 */
void ArrayStackPop(ArrayStack *const restrict stack);

#endif  // __COLLECTIONS_ARRAY_STACK__