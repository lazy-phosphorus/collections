#ifndef __COLLECTIONS_DELINKED_LIST__
#define __COLLECTIONS_DELINKED_LIST__

#include "types.h"

/**
 * @brief Type of element in `DelinkedList`.
 * @attention It is no recommended to use this struct.
 * @see `DelinkedListGetIterator()`, `DelinkedListGetReverseIterator()`,
 * `DelinkedListIteratorNext()`, `DelinkedListIteratorPrevious()`,
 * `DelinkedListIteratorGetValue()`, `DelinkedListIteratorEnded()`
 */
typedef struct __DelinkedListNode {
    /**
     * @private
     * @brief Pointer refers to the previous node.
     */
    struct __DelinkedListNode *previous;
    /**
     * @private
     * @brief Value of this node.
     */
    void *value;
    /**
     * @private
     * @brief Pointer refers to the next node.
     */
    struct __DelinkedListNode *next;
} DelinkedListNode;

/**
 * @brief Iterator of `DelinkedList`.
 * @attention This iterator has no void head node. You can call
 * `DelinkedListIteratorGetValue()` directly.
 */
typedef DelinkedListNode *DelinkedListIterator;

/**
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `DelinkedListConstruct()`, `DelinkedListNew()`,
 * `DelinkedListDestruct()`, `DelinkedListDelete()`.
 */
typedef struct {
    /**
     * @private
     * @brief Pointer refers to the first element.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `DelinkedListFront()`, `DelinkedListSet()`,
     * `DelinkedListPushFront()`, `DelinkedListPopFront()`.
     */
    DelinkedListNode *head;
    /**
     * @private
     * @brief Pointer refers to the last element.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `DelinkedListBack()`, `DelinkedListSet()`, `DelinkedListPushBack()`,
     * `DelinkedListPopBack`.
     */
    DelinkedListNode *tail;
    /**
     * @private
     * @brief Element size of this list.
     * @warning Don't modify this member directly.
     */
    unsigned long elementSize;
    /**
     * @private
     * @brief Functions used in comparing two elements.
     * @warning Don't modify this member directly.
     */
    CompareFunction *compare;

    /**
     * @public
     * @brief Current element quantity of this list.
     * @attention Don't modify the value of this member directly. It is
     * maintained automatically.
     */
    unsigned int Size;
} DelinkedList;

/**
 * @brief Construct function. O(1).
 *
 * @param node Target to be constructed.
 * @param value Value of `node`. It will be DEEP copied.
 * @param elementSize Value size of `value`.
 */
void DelinkedListNodeConstruct(DelinkedListNode *const restrict node,
                               const void *const restrict value,
                               unsigned long elementSize);

/**
 * @brief Allocate a new node in heap. O(1).
 *
 * @param value Value of node. It will be DEEP copied.
 * @param elementSize Size of `value`.
 * @return DelinkedListNode* Pointer refering to a heap address.
 */
DelinkedListNode *DelinkedListNodeNew(const void *const restrict value,
                                      unsigned long elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param node Target to be destructed. If `NULL`, nothing will happen.
 */
void DelinkedListNodeDestruct(DelinkedListNode *const restrict node);

/**
 * @brief Release `node` in heap. O(1).
 *
 * @param node Pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void DelinkedListNodeDelete(DelinkedListNode **const restrict node);

/**
 * @brief Construct function. O(1).
 *
 * @param list Target to be constructed.
 * @param elementSize Element size of `list`
 * @param compare Function used in comparing two elements.
 */
void DelinkedListConstruct(DelinkedList *const restrict list,
                           const unsigned long elementSize,
                           CompareFunction *const compare);

/**
 * @brief Allocate a new list in heap. O(1).
 *
 * @param initialCapacity Initial capacity of list.
 * @param elementSize Element size of list.
 * @param compare Function used in comparing two elements.
 * @return DelinkedList* Pointer refering to a heap address.
 */
DelinkedList *DelinkedListNew(const unsigned long elementSize,
                              CompareFunction *const compare);

/**
 * @brief Destruct function. O(n).
 *
 * @param list Target to be destructed. If `NULL`, nothing will happen.
 */
void DelinkedListDestruct(DelinkedList *const restrict list);

/**
 * @brief Release `list` in heap. O(n).
 *
 * @param list Pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void DelinkedListDelete(DelinkedList **const restrict list);

/**
 * @brief Get value of the element at specified `index`. O(n).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param list `this`.
 * @param index Specified index.
 * @return void* If successful, the element will be returned. Otherwise, `NULL`
 * will be returned.
 */
void *DelinkedListGet(const DelinkedList *const restrict list,
                      const unsigned int index);

/**
 * @brief Set value of element at specified `index`. O(n).
 *
 * @param list `this`.
 * @param index Specified index.
 * @param value Value of element. It will be DEEP copied.
 */
void DelinkedListSet(DelinkedList *const restrict list,
                     const unsigned int index,
                     const void *const restrict value);

/**
 * @brief Get value of the last element. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param list `this`.
 * @return void* If `list` is empty, `NULL` will be returned.
 */
void *DelinkedListBack(DelinkedList *const restrict list);

/**
 * @brief Get value of the first element. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param list `this`.
 * @return void* If `list` is empty, `NULL` will be returned.
 */
void *DelinkedListFront(DelinkedList *const restrict list);

/**
 * @brief Add new element at the end of `list`. O(1).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 */
void DelinkedListPushBack(DelinkedList *const restrict list,
                          const void *const restrict value);

/**
 * @brief Remove the last element of `list`. O(1).
 *
 * @param list `this`.
 */
void DelinkedListPopBack(DelinkedList *const restrict list);

/**
 * @brief Add new element at the begin of `list`. O(1).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 */
void DelinkedListPushFront(DelinkedList *const restrict list,
                           const void *const restrict value);

/**
 * @brief Remove the first element of `list`. O(1).
 *
 * @param list `this`.
 */
void DelinkedListPopFront(DelinkedList *const restrict list);

/**
 * @brief Add new element at the specified index of `list`. After element
 * added, `list[index]` will be the new element. O(n).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 */
void DelinkedListInsert(DelinkedList *const restrict list,
                        const unsigned int index,
                        const void *const restrict value);

/**
 * @brief Find the element which has `value`. O(n).
 *
 * @param list `this`.
 * @param value Specified value.
 * @return int If found, the index of the element will be returned. If not
 * found, `-1` will be returned.
 */
int DelinkedListFind(DelinkedList *const restrict list,
                     const void *const restrict value);

/**
 * @brief Slice `list`, and return new list which contains DEEP copied
 * elements from index `start`(contained) and has `size` elements. O(n).
 *
 * @param list `this`.
 * @param start Start index.
 * @param size Size of returned list.
 * @return DelinkedList* New list with DEEP copied elements. This pointer will
 * NOT automatically be released.
 */
DelinkedList *DelinkedListSlice(DelinkedList *const restrict list,
                                const unsigned int start,
                                const unsigned int size);

/**
 * @brief Use quick sort algorithm to sort `list`. O(nlog₂n).
 *
 * @param list `this`.
 */
void DelinkedListQuickSort(DelinkedList *const restrict list);

/**
 * @brief Get iterator of `list`. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param list `this`.
 * @return DelinkedListIterator Iterator SHALLOW copied from `list->head`.
 */
DelinkedListIterator DelinkedListGetIterator(DelinkedList *const restrict list);

/**
 * @brief Get reverse iterator of `list`. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param list `this`
 * @return DelinkedListIterator Iterator SHALLOW copied
 * from `list->tail`.
 */
DelinkedListIterator DelinkedListGetReverseIterator(
    DelinkedList *const restrict list);

/**
 * @brief Move to the next element. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param iterator `this`.
 * @return DelinkedListIterator Renewed iterator.
 */
DelinkedListIterator DelinkedListIteratorNext(
    DelinkedListIterator const restrict iterator);

/**
 * @brief Move to the previous element. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param iterator `this`.
 * @return DelinkedListIterator Renewed iterator.
 */
DelinkedListIterator DelinkedListIteratorPrevious(
    DelinkedListIterator const restrict iterator);

/**
 * @brief Get value of current element. O(1).
 * @attention The returned value is shallow copied. Don't free it.
 *
 * @param iterator `this`.
 * @return void* Value of element.
 */
void *DelinkedListIteratorGetValue(
    DelinkedListIterator const restrict iterator);

/**
 * @brief Check if iterator reaches end. O(1).
 *
 * @param iterator `this`.
 * @return Bool.
 */
Bool DelinkedListIteratorEnded(DelinkedListIterator const restrict iterator);

#endif  // __COLLECTIONS_DELINKED_LIST__
