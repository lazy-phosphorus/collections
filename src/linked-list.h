#ifndef __COLLECTIONS_LINKED_LIST__
#define __COLLECTIONS_LINKED_LIST__

#include "types.h"

/**
 * @brief Type of element in `LinkedList`.
 * @attention It is no recommended to use this struct.
 */
typedef struct __LinkedListNode {
    /**
     * @private
     * @brief Value of this node.
     */
    void *value;
    /**
     * @private
     * @brief Pointer refers to the next node.
     */
    struct __LinkedListNode *next;
} LinkedListNode;

/**
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `LinkedListConstruct`, `LinkedListNew`, `LinkedListDestruct`,
 * `LinkedListDelete`.
 */
typedef struct {
    /**
     * @private
     * @brief Pointer refers to the first element.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `LinkedListFront`, `LinkedListSet`, `LinkedListPushFront`,
     * `LinkedListPopFront`.
     */
    LinkedListNode *head;
    /**
     * @private
     * @brief Pointer refers to the last element.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `LinkedListBack`, `LinkedListSet`, `LinkedListPushBack`,
     * `LinkedListPopBack`.
     */
    LinkedListNode *tail;
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
} LinkedList;

/**
 * @brief Construct function. O(1).
 *
 * @param node Target to be constructed.
 * @param value Value of `node`.
 * @param elementSize Size of `value`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int LinkedListNodeConstruct(LinkedListNode *const restrict node,
                            const void *const restrict value,
                            unsigned long elementSize);

/**
 * @brief Allocate a new node in heap. O(1).
 *
 * @param value Value of node.
 * @param elementSize Size of `value`.
 * @return LinkedListNode* If successful, a pointer refering to a heap address
 * will be returned. Otherwise, `NULL` will be returned and `errno` will be set.
 */
LinkedListNode *LinkedListNodeNew(const void *const restrict value,
                                  unsigned long elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param node Target to be destructed. If `NULL`, nothing will happen.
 */
void LinkedListNodeDestruct(LinkedListNode *const restrict node);

/**
 * @brief Release `node` in heap. O(1).
 *
 * @param node A pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void LinkedListNodeDelete(LinkedListNode **const restrict node);

/**
 * @brief Construct function. O(1).
 *
 * @param list Target to be constructed.
 * @param elementSize Element size of `list`
 * @param compare Function used in comparing two elements.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int LinkedListConstruct(LinkedList *const restrict list,
                        const unsigned long elementSize,
                        CompareFunction *const compare);

/**
 * @brief Allocate a new list in heap. O(1).
 *
 * @param initialCapacity Initial capacity of list.
 * @param elementSize Element size of list.
 * @param compare Function used in comparing two elements.
 * @return LinkedList* If successful, a pointer refering to a heap address will
 * be returned. Otherwise, `NULL` will be returned and `errno` will be set.
 */
LinkedList *LinkedListNew(const unsigned long elementSize,
                          CompareFunction *const compare);

/**
 * @brief Destruct function. O(n).
 *
 * @param list Target to be destructed. If `NULL`, nothing will happen.
 */
void LinkedListDestruct(LinkedList *const restrict list);

/**
 * @brief Release `list` in heap. O(n).
 *
 * @param list A pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void LinkedListDelete(LinkedList **const restrict list);

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
void *LinkedListGet(const LinkedList *const restrict list,
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
int LinkedListSet(LinkedList *const restrict list, const unsigned int index,
                  const void *const restrict value);

/**
 * @brief Get value of the last element. O(1).
 *
 * @param list `this`.
 * @return void* If `list` is empty, `NULL` will be returned. If error, `NULL`
 * will be returned and `errno` will be set.
 */
void *LinkedListBack(LinkedList *const restrict list);

/**
 * @brief Get value of the first element. O(1).
 *
 * @param list `this`.
 * @return void* If `list` is empty, `NULL` will be returned. If error, `NULL`
 * will be returned and `errno` will be set.
 */
void *LinkedListFront(LinkedList *const restrict list);

/**
 * @brief Add new element at the end of `list`. O(1).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int LinkedListPushBack(LinkedList *const restrict list,
                       const void *const restrict value);

/**
 * @brief Remove the last element of `list`. O(n).
 *
 * @param list `this`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int LinkedListPopBack(LinkedList *const restrict list);

/**
 * @brief Add new element at the begin of `list`. O(1).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int LinkedListPushFront(LinkedList *const restrict list,
                        const void *const restrict value);

/**
 * @brief Remove the first element of `list`. O(1).
 *
 * @param list `this`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int LinkedListPopFront(LinkedList *const restrict list);

/**
 * @brief Add new element at the specified index of `list`. After element
 * added, `list[index]` will be the new element. O(n).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int LinkedListInsert(LinkedList *const restrict list, const unsigned int index,
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
int LinkedListFind(LinkedList *const restrict list,
                   const void *const restrict value);

/**
 * @brief Slice `list`, and return new list which contains DEEP copied
 * elements from index `start`(contained) and has `size` elements. O(n).
 *
 * @param list `this`.
 * @param start Start index.
 * @param size Size of returned list.
 * @return DelinkedList* New list with DEEP copied elements. This pointer will
 * NOT automatically be released. If error, `NULL` will be returned and `errno`
 * will be set.
 */
LinkedList *LinkedListSlice(LinkedList *const restrict list,
                            const unsigned int start, const unsigned int size);

#endif  // __COLLECTIONS_LINKED_LIST__
