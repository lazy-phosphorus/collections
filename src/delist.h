#ifndef __COLLECTIONS_DELIST__
#define __COLLECTIONS_DELIST__

#include "types.h"

/**
 * @brief Typeof element in `Delist`.
 * @attention It is no recommended to use this struct.
 */
typedef struct __DelistNode {
    /**
     * @private
     * @brief Pointer refers to the previous node.
     */
    struct __DelistNode *previous;
    /**
     * @private
     * @brief Value of this node.
     */
    void *value;
    /**
     * @private
     * @brief Pointer refers to the next node.
     */
    struct __DelistNode *next;
} DelistNode;

/**
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `DelistConstruct`, `DelistNew`, `DelistDestruct`, `DelistDelete`.
 */
typedef struct {
    /**
     * @private
     * @brief Pointer refers to the first element.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `DelistFront`, `DelistSet`, `DelistPushFront`, `DelistPopFront`.
     */
    DelistNode *head;
    /**
     * @private
     * @brief Pointer refers to the last element.
     * @warning Don't modify this member directly. Please use functions below.
     * @see `DelistBack`, `DelistSet`, `DelistPushBack`, `DelistPopBack`.
     */
    DelistNode *tail;
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
} Delist;

/**
 * @brief Construct function. O(1).
 *
 * @param node Target to be constructed.
 * @param value Value of `node`.
 * @param elementSize Size of `value`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelistNodeConstruct(DelistNode *const node,
                        const void *const restrict value,
                        unsigned long elementSize);

/**
 * @brief Allocate a new node in heap. O(1).
 *
 * @param value Value of node.
 * @param elementSize Size of `value`.
 * @return DelistNode* If successful,`0` will be returned. Otherwise, `-1` will
 * be returned and `errno` will be set.
 */
DelistNode *DelistNodeNew(const void *const restrict value,
                          unsigned long elementSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param node Target to be destructed. If `NULL`, nothing will happen.
 */
void DelistNodeDestruct(DelistNode *const node);

/**
 * @brief Release `node` in heap. O(1).
 *
 * @param node A pointer refers to the target to be deleted. The target will be
 * set to `NULL`. If `NULL`, nothing will happen.
 */
void DelistNodeDelete(DelistNode **const node);

/**
 * @brief Construct function. O(1).
 *
 * @param list Target to be constructed.
 * @param elementSize Element size of `list`
 * @param compare Function used in comparing two elements.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelistConstruct(Delist *const restrict list,
                    const unsigned long elementSize,
                    CompareFunction *const compare);

/**
 * @brief Allocate a new list in heap. O(1).
 *
 * @param initialCapacity Initial capacity of list.
 * @param elementSize Element size of list.
 * @param compare Function used in comparing two elements.
 * @return Delist* If successful, a pointer refering to a heap address will be
 * returned. Otherwise, `NULL` will be returned and `errno` will be set.
 */
Delist *DelistNew(const unsigned long elementSize,
                  CompareFunction *const compare);

/**
 * @brief Destructor function. O(1).
 *
 * @param list Target to be destructed. If `NULL`, nothing will happen.
 */
void DelistDestruct(Delist *const restrict list);

/**
 * @brief Release `list` in heap. O(1).
 *
 * @param list A pointer refers to the target to be deleted. The target will be
 * set to `NULL`. If `NULL`, nothing will happen.
 */
void DelistDelete(Delist **const restrict list);

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
void *DelistGet(const Delist *const restrict list, const unsigned int index);

/**
 * @brief Set value of element at specified `index`. O(n).
 *
 * @param list `this`.
 * @param index Specified index.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelistSet(Delist *const restrict list, const unsigned int index,
              const void *const restrict value);

/**
 * @brief Get value of the last element. O(1).
 *
 * @param list `this`.
 * @return void* If `list` is empty, `NULL` will be returned. If error, `NULL`
 * will be returned and `errno` will be set.
 */
void *DelistBack(Delist *const restrict list);

/**
 * @brief Get value of the first element. O(1).
 *
 * @param list `this`.
 * @return void* If `list` is empty, `NULL` will be returned. If error, `NULL`
 * will be returned and `errno` will be set.
 */
void *DelistFront(Delist *const restrict list);

/**
 * @brief Add new element at the end of `list`. O(1).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelistPushBack(Delist *const restrict list,
                   const void *const restrict value);

/**
 * @brief Remove the last element of `list`. O(1).
 *
 * @param list `this`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelistPopBack(Delist *const restrict list);

/**
 * @brief Add new element at the begin of `list`. O(1).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelistPushFront(Delist *const restrict list,
                    const void *const restrict value);

/**
 * @brief Remove the first element of `list`. O(1).
 *
 * @param list `this`.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelistPopFront(Delist *const restrict list);

/**
 * @brief Add new element at the specified index of `list`. After element
 * added, `list[index]` will be the new element. O(n).
 *
 * @param list `this`.
 * @param value Value of element. It will be DEEP copied.
 * @return int If successful, `0` will be returned. Otherwise, `-1` will be
 * returned and `errno` will be set.
 */
int DelistInsert(Delist *const restrict list, const unsigned int index,
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
int DelistFind(Delist *const restrict list, const void *const restrict value);

#endif  // __COLLECTIONS_DELIST__