#ifndef __COLLECTIONS_DELINKED_LIST__
#define __COLLECTIONS_DELINKED_LIST__

#include "types.h"

/**
 * @brief Type of element in `DelinkedList`.
 * @attention It is no recommended to use this struct.
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
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `DelinkedListConstruct`, `DelinkedListNew`, `DelinkedListDestruct`,
 * `DelinkedListDelete`.
 */
typedef struct {
    /**
     * @private
     * @brief Pointer refers to the first element.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `DelinkedListFront`, `DelinkedListSet`, `DelinkedListPushFront`,
     * `DelinkedListPopFront`.
     */
    DelinkedListNode *head;
    /**
     * @private
     * @brief Pointer refers to the last element.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `DelinkedListBack`, `DelinkedListSet`, `DelinkedListPushBack`,
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
 * @param value Value of `node`.
 * @param elementSize Value size of `value`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelinkedListNodeConstruct(DelinkedListNode *const node,
                              const void *const restrict value,
                              unsigned long elementSize);

/**
 * @brief Allocate a new node in heap. O(1).
 *
 * @param value Value of node.
 * @param elementSize Size of `value`.
 * @return DelinkedListNode* If successful, a pointer refering to a heap address
 * will be returned. Otherwise, `NULL` will be returned and `errno` will be set.
 */
DelinkedListNode *DelinkedListNodeNew(const void *const restrict value,
                                      unsigned long elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param node Target to be destructed. If `NULL`, nothing will happen.
 */
void DelinkedListNodeDestruct(DelinkedListNode *const node);

/**
 * @brief Release `node` in heap. O(1).
 *
 * @param node A pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void DelinkedListNodeDelete(DelinkedListNode **const node);

/**
 * @brief Construct function. O(1).
 *
 * @param list Target to be constructed.
 * @param elementSize Element size of `list`
 * @param compare Function used in comparing two elements.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelinkedListConstruct(DelinkedList *const restrict list,
                          const unsigned long elementSize,
                          CompareFunction *const compare);

/**
 * @brief Allocate a new list in heap. O(1).
 *
 * @param initialCapacity Initial capacity of list.
 * @param elementSize Element size of list.
 * @param compare Function used in comparing two elements.
 * @return DelinkedList* If successful, a pointer refering to a heap address
 * will be returned. Otherwise, `NULL` will be returned and `errno` will be set.
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
 * @param list A pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void DelinkedListDelete(DelinkedList **const restrict list);

/**
 * @brief Get value of the element at specified `index`. O(n).
 * @attention The returned value is shallow copied from `list[index]`. Don't
 * free it.
 *
 * @param list `this`.
 * @param index Specified index.
 * @return void* If successful, the element will be returned. Otherwise, `NULL`
 * will be returned and `errno` will be set.
 */
void *DelinkedListGet(const DelinkedList *const restrict list,
                      const unsigned int index);

/**
 * @brief Set value of element at specified `index`. O(n).
 *
 * @param list `this`.
 * @param index Specified index.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelinkedListSet(DelinkedList *const restrict list, const unsigned int index,
                    const void *const restrict value);

/**
 * @brief Get value of the last element. O(1).
 *
 * @param list `this`.
 * @return void* If `list` is empty, `NULL` will be returned. If error, `NULL`
 * will be returned and `errno` will be set.
 */
void *DelinkedListBack(DelinkedList *const restrict list);

/**
 * @brief Get value of the first element. O(1).
 *
 * @param list `this`.
 * @return void* If `list` is empty, `NULL` will be returned. If error, `NULL`
 * will be returned and `errno` will be set.
 */
void *DelinkedListFront(DelinkedList *const restrict list);

/**
 * @brief Add new element at the end of `list`. O(1).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelinkedListPushBack(DelinkedList *const restrict list,
                         const void *const restrict value);

/**
 * @brief Remove the last element of `list`. O(1).
 *
 * @param list `this`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelinkedListPopBack(DelinkedList *const restrict list);

/**
 * @brief Add new element at the begin of `list`. O(1).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelinkedListPushFront(DelinkedList *const restrict list,
                          const void *const restrict value);

/**
 * @brief Remove the first element of `list`. O(1).
 *
 * @param list `this`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelinkedListPopFront(DelinkedList *const restrict list);

/**
 * @brief Add new element at the specified index of `list`. After element
 * added, `list[index]` will be the new element. O(n).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelinkedListInsert(DelinkedList *const restrict list,
                       const unsigned int index,
                       const void *const restrict value);

/**
 * @brief Find the element which has `value`. O(n).
 *
 * @param list `this`.
 * @param value Specified value.
 * @return int If found, the index of the element will be returned. If not
 * found, only `-1` will be returned. If error, `-1` will be returned and
 * `errno` will be set.
 */
int DelinkedListFind(DelinkedList *const restrict list,
                     const void *const restrict value);

#endif  // __COLLECTIONS_DELINKED_LIST__
