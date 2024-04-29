#ifndef __COLLECTIONS_LINKED_STACK__
#define __COLLECTIONS_LINKED_STACK__

/**
 * @brief Type of element in `LinkedStack`.
 * @attention It is not recommended to use this struct.
 */
typedef struct __LinkedStackNode {
    /**
     * @private
     * @brief Pointer refers to the next node.
     */
    struct __LinkedStackNode* previous;
    /**
     * @private
     * @brief Value of this node.
     */
    void* value;
} LinkedStackNode;

/**
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `LinkedStackConstruct`, `LinkedStackNew`, `LinkedStackDestruct`,
 * `LinkedStackDelete`.
 */
typedef struct {
    /**
     * @private
     * @brief Pointer refers to the last element(top element of the stack).
     * @warning Don't modify this member directly. Please use functions below.
     * @see `LinkedStackTop`, `LinkedStackPush`, `LinkedStackPop`.
     */

    LinkedStackNode* tail;
    /**
     * @private
     * @brief Element size of this stack.
     * @warning Don't modify this member directly.
     */
    unsigned long elementSize;

    /**
     * @public
     * @brief Current element quantity of this stack.
     * @attention Don't modify the value of this member directly. It is
     * maintained automatically.
     */
    unsigned int Size;
} LinkedStack;

/**
 * @brief Construct function. O(1).
 *
 * @param node Target to be constructed.
 * @param value Value of `node`.
 * @param elementSize Size of `value`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int LinkedStackNodeConstruct(LinkedStackNode* const restrict node,
                             const void* const restrict value,
                             const unsigned int elementSize);
/**
 * @brief Allocate a new node in heap. O(1).
 *
 * @param value Value of node.
 * @param elementSize Size of `value`.
 * @return LinkedStackNode* If successful, a pointer refering to a heap address
 * will be returned. Otherwise, `NULL` will be returned and `errno` will be set.
 */
LinkedStackNode* LinkedStackNodeNew(const void* const restrict value,
                                    const unsigned int elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param node Target to be destructed. If `NULL`, nothing will happen.
 */
void LinkedStackNodeDestruct(LinkedStackNode* const restrict node);

/**
 * @brief Release `node` in heap. O(1).
 *
 * @param node A pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void LinkedStackNodeDelete(LinkedStackNode** const restrict node);

/**
 * @brief Construct function. O(1).
 *
 * @param stack Target to be constructed.
 * @param elementSize Element size of `stack`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int LinkedStackConstruct(LinkedStack* const restrict stack,
                         const unsigned int elementSize);

/**
 * @brief Allocate a new stack in heap. O(1).
 *
 * @param elementSize Element size of stack.
 * @return LinkedStack* If successful, a pointer refering to a heap address will
 * be returned. Otherwise, `NULL` will be returned and `errno` will be set.
 */
LinkedStack* LinkedStackNew(const unsigned int elementSize);

/**
 * @brief Destruct function. O(n).
 *
 * @param stack Target to be destructed. If `NULL`, nothing will happen.
 */
void LinkedStackDestruct(LinkedStack* const restrict stack);

/**
 * @brief Release `stack` in heap. O(n).
 *
 * @param stack A pointer refers to the target which is to be deleted. The
 * target will be set to `NULL. If `NULL`, nothing will happen.
 */
void LinkedStackDelete(LinkedStack** const restrict stack);

/**
 * @brief Get value of the element which is on the top of `stack`. O(1).
 *
 * @param stack `this`.
 * @return void* If successful, the element will be returned. Otherwise, `NULL`
 * will be returned and `errno` will be set.
 */
void* LinkedStackTop(const LinkedStack* const restrict stack);

/**
 * @brief Push new element into `stack`. O(1).
 *
 * @param stack `this`.
 * @param value Value of element.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int LinkedStackPush(LinkedStack* const restrict stack,
                    const void* const restrict value);

/**
 * @brief Remove the element which is on the top of `stack`. O(1).
 *
 * @param stack `this`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int LinkedStackPop(LinkedStack* const restrict stack);

#endif  // __COLLECTIONS_LINKED_STACK__
