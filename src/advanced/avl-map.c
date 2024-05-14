#include "avl-map.h"

#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "avl-tree.h"
#include "types.h"

void AvlMapPairConstruct(AvlMapPair *const restrict pair,
                         const void *const restrict key,
                         const unsigned long keySize,
                         const void *const restrict value,
                         const unsigned long valueSize) {
    assert(pair != NULL);
    assert(key != NULL);
    assert(keySize > 0);
    assert(value != NULL);
    assert(valueSize > 0);

    pair->key = malloc(keySize);
    assert(pair->key != NULL);
    memcpy(pair->key, key, keySize);
    pair->value = malloc(valueSize);
    assert(pair->value != NULL);
    memcpy(pair->value, value, valueSize);
    pair->keySize = keySize;
}

AvlMapPair *AvlMapPairNew(const void *const restrict key,
                          const unsigned long keySize,
                          const void *const restrict value,
                          const unsigned long valueSize) {
    AvlMapPair *pair = (AvlMapPair *)malloc(sizeof(AvlMapPair));
    AvlMapPairConstruct(pair, key, keySize, value, valueSize);
    return pair;
}

void AvlMapPairDestruct(AvlMapPair *const restrict pair) {
    if (pair == NULL) return;

    free(pair->key);
    pair->key = NULL;
    free(pair->value);
    pair->value = NULL;
}

void AvlMapPairDelete(AvlMapPair **const restrict pair) {
    if (pair == NULL) return;

    AvlMapPairDestruct(*pair);
    free(*pair);
    *pair = NULL;
}

static int __compare(const void *a, const void *b) {
    const AvlMapPair *i = (const AvlMapPair *)a, *j = (const AvlMapPair *)b;
    return strncmp((const char *)i->key, (const char *)j->key, i->keySize);
}

void AvlMapConstruct(AvlMap *const restrict map, const unsigned long keySize,
                     const unsigned long valueSize) {
    assert(map != NULL);
    assert(keySize > 0);
    assert(valueSize > 0);

    map->keySize = keySize;
    map->valueSize = valueSize;
    map->tree = AvlTreeNew(sizeof(AvlMapPair), __compare);
    map->Size = 0;
}

AvlMap *AvlMapNew(const unsigned long keySize, const unsigned long valueSize) {
    AvlMap *map = (AvlMap *)malloc(sizeof(AvlMap));
    AvlMapConstruct(map, keySize, valueSize);
    return map;
}

void __AvlMapDestruct(AvlTreeNode *const restrict node) {
    if (node == NULL) return;

    __AvlMapDestruct(node->left);
    __AvlMapDestruct(node->right);
    AvlMapPairDestruct((AvlMapPair *)node->value);
}

void AvlMapDestruct(AvlMap *const restrict map) {
    if (map == NULL) return;

    __AvlMapDestruct(map->tree->root);
    AvlTreeDelete(&map->tree);
    map->keySize = 0;
    map->valueSize = 0;
    map->Size = 0;
}

void AvlMapDelete(AvlMap **const restrict map) {
    if (map == NULL) return;

    AvlMapDestruct(*map);
    free(*map);
    *map = NULL;
}

void *AvlMapGet(AvlMap *const restrict map, const void *const restrict key) {
    assert(map != NULL);
    assert(key != NULL);

    AvlMapPair pair, *temp = NULL;
    pair.value = NULL;
    pair.keySize = map->keySize;
    pair.key = malloc(map->keySize);
    memcpy(pair.key, key, map->keySize);
    temp = (AvlMapPair *)AvlTreeFind(map->tree, &pair);
    AvlMapPairDestruct(&pair);
    if (temp == NULL)
        return NULL;
    else
        return temp->value;
}

void AvlMapSet(AvlMap *const restrict map, const void *const restrict key,
               const void *const restrict value) {
    assert(map != NULL);
    assert(key != NULL);
    assert(value != NULL);

    AvlMapPair pair;
    AvlMapPairConstruct(&pair, key, map->keySize, value, map->valueSize);
    AvlTreeInsert(map->tree, &pair);
    map->Size = map->tree->Size;
}

void AvlMapRemove(AvlMap *const restrict map, const void *const restrict key) {
    assert(map != NULL);
    assert(key != NULL);

    AvlMapPair pair, *temp = NULL;
    pair.value = NULL;
    pair.keySize = map->keySize;
    pair.key = malloc(map->keySize);
    memcpy(pair.key, key, map->keySize);
    AvlTreeRemove(map->tree, &pair);
    map->Size = map->tree->Size;
    AvlMapPairDestruct(&pair);
}

Bool AvlMapSome(AvlMap *const restrict map, TestFunction *const test) {
    assert(map != NULL);
    assert(test != NULL);

    return AvlTreeSome(map->tree, test);
}

Bool AvlMapAll(AvlMap *const restrict map, TestFunction *const test) {
    assert(map != NULL);
    assert(test != NULL);

    return AvlTreeAll(map->tree, test);
}
