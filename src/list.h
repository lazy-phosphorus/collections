#ifndef __COLLECTIONS_LIST__
#define __COLLECTIONS_LIST__

#include "types.h"

typedef struct __ListNode {
    void *value;
    struct __ListNode *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
    unsigned long elementSize;
    CompareFunction *compare;

    unsigned int Size;
} List;

/**
 * @brief Construct function. O(1).
 *
 * @param node Target to be constructed.
 * @param value Value of `node`.
 * @param elementSize Size of `value`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ListNodeConstruct(ListNode *const node, const void *const restrict value,
                      unsigned long elementSize);

/**
 * @brief Allocate a new node in heap. O(1).
 *
 * @param value Value of node.
 * @param elementSize Size of `value`.
 * @return ListNode* If successful,`0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
ListNode *ListNodeNew(const void *const restrict value,
                      unsigned long elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param node Target to be destructed. If `NULL`, nothing will happen.
 */
void ListNodeDestruct(ListNode *const node);

/**
 * @brief Release `node` in heap. O(1).
 *
 * @param node A pointer refers to the target to be deleted. The target will be
 * set to `NULL`. If `NULL`, nothing will happen.
 */
void ListNodeDelete(ListNode **const node);

/**
 * @brief Construct function. O(1).
 *
 * @param list Target to be constructed.
 * @param elementSize Element size of `list`
 * @param compare Function used in comparing two elements.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ListConstruct(List *const restrict list, const unsigned long elementSize,
                  CompareFunction *const compare);

/**
 * @brief Allocate a new list in heap. O(1).
 *
 * @param initialCapacity Initial capacity of list.
 * @param elementSize Element size of list.
 * @param compare Function used in comparing two elements.
 * @return List* If successful, a pointer refering to a heap address will be
 * returned. Otherwise, `NULL` will be returned and `errno` will be set.
 */
List *ListNew(const unsigned long elementSize, CompareFunction *const compare);

/**
 * @brief Destructor function. O(1).
 *
 * @param list Target to be destructed. If `NULL`, nothing will happen.
 */
void ListDestruct(List *const restrict list);

/**
 * @brief Release `list` in heap. O(1).
 *
 * @param list A pointer refers to the target to be deleted. The target will be
 * set to `NULL`. If `NULL`, nothing will happen.
 */
void ListDelete(List **const restrict list);

/**
 * @brief Get value of the element at specified `index`. O(1).
 * @attention The returned value is shallow copied from `list[index]`. Don't
 * free it.
 *
 * @param list `this`.
 * @param index Specified index.
 * @return void* If successful, the element will be returned. Otherwise, `NULL`
 * will be returned and `errno` will be set.
 */
void *ListGet(const List *const restrict list, const unsigned int index);

/**
 * @brief Set value of element at specified `index`. O(1).
 *
 * @param list `this`.
 * @param index Specified index.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ListSet(List *const restrict list, const unsigned int index,
            const void *const restrict value);

/**
 * @brief Get value of the last element. O(1).
 *
 * @param list `this`.
 * @return void* If `list` is empty, `NULL` will be returned. If error, `NULL`
 * will be returned and `errno` will be set.
 */
void *ListBack(List *const restrict list);

/**
 * @brief Get value of the first element. O(1).
 *
 * @param list `this`.
 * @return void* If `list` is empty, `NULL` will be returned. If error, `NULL`
 * will be returned and `errno` will be set.
 */
void *ListFront(List *const restrict list);

/**
 * @brief Add new element at the end of `list`. O(1).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ListPushBack(List *const restrict list, const void *const restrict value);

/**
 * @brief Remove the last element of `list`. O(n).
 *
 * @param list `this`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ListPopBack(List *const restrict list);

/**
 * @brief Add new element at the begin of `list`. O(n).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ListPushFront(List *const restrict list, const void *const restrict value);

/**
 * @brief Remove the first element of `list`. O(1).
 *
 * @param list `this`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ListPopFront(List *const restrict list);

/**
 * @brief Add new element at the specified index of `list`. After element
 * added, `list[index]` will be the new element. O(n).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int ListInsert(List *const restrict list, const unsigned int index,
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
int ListFind(List *const restrict list, const void *const restrict value);

#endif  // __COLLECTIONS_LIST__
