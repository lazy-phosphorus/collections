#ifndef __COLLECTIONS_AVL_MAP__
#define __COLLECTIONS_AVL_MAP__

#include "avl-tree.h"
#include "types.h"

/**
 * @brief Type of element in `AvlMap`.
 * @attention It is no recommended to use this struct.
 */
typedef struct {
    /**
     * @private
     * @brief Key of this node.
     */
    void *key;
    /**
     * @private
     * @brief Key size of this node.
     */
    unsigned long keySize;
    /**
     * @private
     * @brief Value of this node.
     */
    void *value;
} AvlMapPair;

/**
 * @brief This struct is implemented by `AvlTree`.
 * @warning Don't initialize or free instance of this struct directly. Please
 * use functions below.
 * @see `AvlMapConstruct()`, `AvlMapNew()`, `AvlMapDestruct()`,
 * `AvlMapDelete()`.
 */
typedef struct {
    /**
     * @private
     * @brief AVL tree.
     * @warning Don't modify this member directly. It is maintained
     * automatically.
     * @see `AvlMapSet()`, `AvlMapRemove()`.
     */
    AvlTree *tree;
    /**
     * @private
     * @brief Key size of every element.
     * @warning Don't modify this member directly.
     */
    unsigned long keySize;
    /**
     * @private
     * @brief Value size of every element.
     * @warning Don't modify this member directly.
     */
    unsigned long valueSize;

    /**
     * @public
     * @brief Current element quantity of this map.
     * @attention Don't modify the value of this member directly. It is
     * maintained automatically.
     */
    unsigned int Size;
} AvlMap;

/**
 * @brief Construct function. O(1).
 *
 * @param pair Target to be constructed.
 * @param key Key of `pair`.
 * @param keySize Key size of `pair`.
 * @param value Value of `pair`.
 * @param valueSize Value size of `pair`.
 * @param compare Function used in comparing two elements.
 */
void AvlMapPairConstruct(AvlMapPair *const restrict pair,
                         const void *const restrict key,
                         const unsigned long keySize,
                         const void *const restrict value,
                         const unsigned long valueSize);

/**
 * @brief Allocate a new pair in heap. O(1).
 *
 * @param key Key of `pair`.
 * @param keySize Key size of `pair`.
 * @param value Value of `pair`.
 * @param valueSize Value size of `pair`.
 * @return AvlMapPair* Pointer refering to a heap address.
 */
AvlMapPair *AvlMapPairNew(const void *const restrict key,
                          const unsigned long keySize,
                          const void *const restrict value,
                          const unsigned long valueSize);

/**
 * @brief Destruct function. O(1).
 *
 * @param map Target to be destructed. If `NULL`, nothing will happen.
 */
void AvlMapPairDestruct(AvlMapPair *const restrict pair);

/**
 * @brief Release `pair` in heap. O(1).
 *
 * @param map Pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void AvlMapPairDelete(AvlMapPair **const restrict pair);

/**
 * @brief Construct function. O(1).
 *
 * @param map Target to be constructed.
 * @param keySize Key size of `map`.
 * @param valueSize Value size of `map`.
 */
void AvlMapConstruct(AvlMap *const restrict map, const unsigned long keySize,
                     const unsigned long valueSize);

/**
 * @brief Allocate a new map in heap. O(1).
 *
 * @param keySize Key size of `map`.
 * @param valueSize Value size of `map`.
 * @return AvlMap* Pointer refering to a heap address.
 */
AvlMap *AvlMapNew(const unsigned long keySize, const unsigned long valueSize);

/**
 * @brief Destruct function. O(n).
 *
 * @param map Target to be destructed. If `NULL`, nothing will happen.
 */
void AvlMapDestruct(AvlMap *const restrict map);

/**
 * @brief Release `map` in heap. O(n).
 *
 * @param map Pointer refers to the target which is to be deleted. The target
 * will be set to `NULL`. If `NULL`, nothing will happen.
 */
void AvlMapDelete(AvlMap **const restrict map);

/**
 * @brief Get value of `key`. O(log₂n).
 *
 * @param map `this`.
 * @param key Specified key.
 * @return void* If not found, `NULL` will be returned.
 */
void *AvlMapGet(AvlMap *const restrict map, const void *const restrict key);

/**
 * @brief Set value of `key`, or add new key-value pair. O(log₂n).
 *
 * @param map `this`.
 * @param key Specified key.
 * @param value Specified value.
 */
void AvlMapSet(AvlMap *const restrict map, const void *const restrict key,
               const void *const restrict value);

/**
 * @brief Remove key-value pair. If not found, nothing will happen. O(log₂n).
 *
 * @param map `this`.
 * @param key Specified key.
 * @param value Specified value.
 */
void AvlMapRemove(AvlMap *const restrict map, const void *const restrict key);

/**
 * @brief Every pair in `map` will be passed into `test()`. If `test()` returns
 * `TRUE`, `TRUE` will be returned immediately. If `FALSE` is always returned by
 * `test()`, `FALSE` will be returned. O(n).
 *
 * @param map `this`.
 * @param test Function used in checking if some elements satisfy certain
 * conditions.
 * @return Bool
 */
Bool AvlMapSome(AvlMap *const restrict map, TestFunction *const test);

/**
 * @brief Every pair in `map` will be passed into `test()`. If `test()` returns
 * `FALSE`, `FALSE` will be returned immediately. If `TRUE` is always returned
 * by `test()`, `TRUE` will be returned. O(n).
 *
 * @param map `this`.
 * @param test Function used in checking if some elements satisfy certain
 * conditions.
 * @return Bool
 */
Bool AvlMapAll(AvlMap *const restrict map, TestFunction *const test);

#endif  // __COLLECTIONS_AVL_MAP__
