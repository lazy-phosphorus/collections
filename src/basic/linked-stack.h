#ifndef __COLLECTIONS_LINKED_STACK__
#define __COLLECTIONS_LINKED_STACK__

#include "types.h"

/**
 * @brief Type of element in `LinkedStack`.
 * @attention It is not recommended to use this struct.
 * @see `LinkedStackGetIterator()`, `LinkedStackIteratorPrevious()`,
 * `LinkedStackIteratorGetValue()`, `LinkedStackIteratorEnded()`
 */
typedef struct __LinkedStackNode {
    /**
     * @private
     * @brief Pointer refers to the next node.
     */
    struct __LinkedStackNode *previous;
    /**
     * @private
     * @brief Value of this node.
     */
    void *value;
} LinkedStackNode;

/**
 * @brief Iterator of `LinkedStack`.
 * @attention This iterator has no void head node. You can call
 * `LinkedStackIteratorGetValue()` directly.
 */
typedef LinkedStackNode *LinkedStackIterator;

/**
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `LinkedStackConstruct()`, `LinkedStackNew()`, `LinkedStackDestruct()`,
 * `LinkedStackDelete()`.
 */
typedef struct {
    /**
     * @private
     * @brief Pointer refers to the last element(top element of the stack).
     * @warning Don't modify this member directly. Please use functions below.
     * @see `LinkedStackTop()`, `LinkedStackPush()`, `LinkedStackPop()`.
     */
    LinkedStackNode *tail;
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
 * @param value Value of `node`. It will be DEEP copied.
 * @param elementSize Size of `value`.
 */
void LinkedStackNodeConstruct(LinkedStackNode *const restrict node,
                              const void *const restrict value,
                              const unsigned long elementSize);
/**
 * @brief Allocate a new node in stack. O(1).
 *
 * @param value Value of node. It will be DEEP copied.
 * @param elementSize Size of `value`.
 * @return LinkedStackNode* Pointer refering to a stack address.
 */
LinkedStackNode *LinkedStackNodeNew(const void *const restrict value,
                                    const unsigned long elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param node Target to be destructed. If `NULL`, nothing will happen.
 */
void LinkedStackNodeDestruct(LinkedStackNode *const restrict node);

/**
 * @brief Release `node` in stack. O(1).
 *
 * @param node Pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void LinkedStackNodeDelete(LinkedStackNode **const restrict node);

/**
 * @brief Construct function. O(1).
 *
 * @param stack Target to be constructed.
 * @param elementSize Element size of `stack`.
 */
void LinkedStackConstruct(LinkedStack *const restrict stack,
                          const unsigned long elementSize);

/**
 * @brief Allocate a new stack in stack. O(1).
 *
 * @param elementSize Element size of stack.
 * @return LinkedStack* Pointer refering to a stack address.
 */
LinkedStack *LinkedStackNew(const unsigned long elementSize);

/**
 * @brief Destruct function. O(n).
 *
 * @param stack Target to be destructed. If `NULL`, nothing will happen.
 */
void LinkedStackDestruct(LinkedStack *const restrict stack);

/**
 * @brief Release `stack` in stack. O(n).
 *
 * @param stack Pointer refers to the target which is to be deleted. The
 * target will be set to `NULL. If `NULL`, nothing will happen.
 */
void LinkedStackDelete(LinkedStack **const restrict stack);

/**
 * @brief Get value of the element which is on the top of `stack`. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param stack `this`.
 * @return void* If successful, the element will be returned. Otherwise, `NULL`
 * will be returned.
 */
void *LinkedStackTop(const LinkedStack *const restrict stack);

/**
 * @brief Push new element into `stack`. O(1).
 *
 * @param stack `this`.
 * @param value Value of element. It will be DEEP copied.
 */
void LinkedStackPush(LinkedStack *const restrict stack,
                     const void *const restrict value);

/**
 * @brief Remove the element which is on the top of `stack`. O(1).
 *
 * @param stack `this`.
 */
void LinkedStackPop(LinkedStack *const restrict stack);

/**
 * @brief Get iterator of `stack`. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param stack `this`.
 * @return LinkedStackIterator Iterator SHALLOW copied from `stack->head`.
 */
LinkedStackIterator LinkedStackGetIterator(LinkedStack *const restrict stack);

/**
 * @brief Move to the previous element. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param iterator `this`.
 * @return LinkedStackIterator Renewed iterator.
 */
LinkedStackIterator LinkedStackIteratorPrevious(
    LinkedStackIterator const restrict iterator);

/**
 * @brief Get value of current element. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param iterator `this`.
 * @return void* Value of element.
 */
void *LinkedStackIteratorGetValue(LinkedStackIterator const restrict iterator);

/**
 * @brief Check if iterator reaches end. O(1).
 *
 * @param iterator `this`.
 * @return Bool.
 */
Bool LinkedStackIteratorEnded(LinkedStackIterator const restrict iterator);

#endif  // __COLLECTIONS_LINKED_STACK__
