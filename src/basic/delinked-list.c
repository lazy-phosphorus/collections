#include "delinked-list.h"

#include <assert.h>
#include <malloc.h>
#include <memory.h>

void DelinkedListNodeConstruct(DelinkedListNode *const node,
                               const void *const restrict value,
                               unsigned long elementSize) {
    assert(node != NULL);
    assert(value != NULL);
    assert(elementSize > 0);
    node->value = malloc(elementSize);
    assert(node->value != NULL);
    memcpy(node->value, value, elementSize);
    node->previous = NULL;
    node->next = NULL;
}

DelinkedListNode *DelinkedListNodeNew(const void *const restrict value,
                                      unsigned long elementSize) {
    DelinkedListNode *node =
        (DelinkedListNode *)malloc(sizeof(DelinkedListNode));
    DelinkedListNodeConstruct(node, value, elementSize);
    return node;
}

void DelinkedListNodeDestruct(DelinkedListNode *const node) {
    if (node == NULL) return;

    free(node->value);
    node->value = NULL;
    node->previous = NULL;
    node->next = NULL;
}

void DelinkedListNodeDelete(DelinkedListNode **const node) {
    if (node == NULL) return;

    DelinkedListNodeDestruct(*node);
    free(*node);
    *node = NULL;
}

void DelinkedListConstruct(DelinkedList *const restrict list,
                           const unsigned long elementSize,
                           CompareFunction *const compare) {
    assert(list != NULL);
    assert(compare != NULL);
    assert(elementSize > 0);

    list->head = NULL;
    list->tail = NULL;
    list->elementSize = elementSize;
    list->compare = compare;
    list->Size = 0;
}

DelinkedList *DelinkedListNew(const unsigned long elementSize,
                              CompareFunction *const compare) {
    DelinkedList *list = (DelinkedList *)malloc(sizeof(DelinkedList));
    DelinkedListConstruct(list, elementSize, compare);
    return list;
}

void DelinkedListDestruct(DelinkedList *const restrict list) {
    DelinkedListNode *node = NULL, *temp = NULL;
    if (list == NULL) return;

    node = list->head;
    while (node != NULL) {
        temp = node->next;
        DelinkedListNodeDelete(&node);
        node = temp;
    }
    list->compare = NULL;
    list->elementSize = 0;
    list->Size = 0;
    list->head = NULL;
    list->tail = NULL;
}

void DelinkedListDelete(DelinkedList **const restrict list) {
    if (list == NULL) return;

    DelinkedListDestruct(*list);
    free(*list);
    *list = NULL;
}

void *DelinkedListGet(const DelinkedList *const restrict list,
                      const unsigned int index) {
    assert(list != NULL);
    assert(index < list->Size);
    DelinkedListNode *node = list->head;
    for (unsigned int i = 0; i < index; i++) {
        node = node->next;
    }
    return node->value;
}

void DelinkedListSet(DelinkedList *const restrict list,
                     const unsigned int index,
                     const void *const restrict value) {
    assert(list != NULL);
    assert(index < list->Size);
    assert(value != NULL);
    DelinkedListNode *node = list->head;
    for (unsigned int i = 0; i < index; i++) {
        node = node->next;
    }
    memcpy(node->value, value, list->elementSize);
}

void *DelinkedListBack(DelinkedList *const restrict list) {
    assert(list != NULL);
    if (list->Size == 0) return NULL;
    return list->tail->value;
}

void *DelinkedListFront(DelinkedList *const restrict list) {
    assert(list != NULL);
    if (list->Size == 0) return NULL;
    return list->head->value;
}

void DelinkedListPushBack(DelinkedList *const restrict list,
                          const void *const restrict value) {
    assert(list != NULL);
    assert(value != NULL);
    DelinkedListNode *node = DelinkedListNodeNew(value, list->elementSize);
    if (list->Size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        node->previous = list->tail;
        list->tail = node;
    }
    list->Size++;
}

void DelinkedListPopBack(DelinkedList *const restrict list) {
    assert(list != NULL);
    assert(list->Size > 0);
    DelinkedListNode *node = NULL;
    if (list->Size == 1) {
        DelinkedListNodeDelete(&list->tail);
        list->head = NULL;
        list->tail = NULL;
        list->Size = 0;
        return;
    }

    node = list->tail;
    list->tail = node->previous;
    list->tail->next = NULL;
    DelinkedListNodeDelete(&node);
    list->Size--;
}

void DelinkedListPushFront(DelinkedList *const restrict list,
                           const void *const restrict value) {
    assert(list != NULL);
    assert(value != NULL);
    DelinkedListNode *node = DelinkedListNodeNew(value, list->elementSize);
    if (list->Size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head->previous = node;
        list->head = node;
    }
    list->Size++;
}

void DelinkedListPopFront(DelinkedList *const restrict list) {
    assert(list != NULL);
    assert(list->Size > 0);
    DelinkedListNode *node = NULL;
    if (list->Size == 1) {
        DelinkedListNodeDelete(&list->head);
        list->head = NULL;
        list->tail = NULL;
        list->Size = 0;
        return;
    }

    node = list->head;
    list->head = node->next;
    list->head->previous = NULL;
    DelinkedListNodeDelete(&node);
    list->Size--;
}

void DelinkedListInsert(DelinkedList *const restrict list, const unsigned index,
                        const void *const restrict value) {
    assert(list != NULL);
    assert(value != NULL);
    assert(index <= list->Size);
    DelinkedListNode *node = NULL, *temp = NULL;
    if (index == 0)
        DelinkedListPushFront(list, value);
    else if (index == list->Size)
        DelinkedListPushBack(list, value);
    else {
        node = DelinkedListNodeNew(value, list->elementSize);
        temp = list->head;
        for (unsigned int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next->previous = node;
        temp->next = node;
        node->previous = temp;
        list->Size++;
    }
}

int DelinkedListFind(DelinkedList *const restrict list,
                     const void *const restrict value) {
    assert(list != NULL);
    assert(value != NULL);
    DelinkedListNode *node = list->head;
    for (int i = 0; i < list->Size; i++) {
        if (list->compare(node->value, value) == 0) return i;
        node = node->next;
    }
    return -1;
}

DelinkedList *DelinkedListSlice(DelinkedList *const restrict list,
                                const unsigned int start,
                                const unsigned int size) {
    assert(list != NULL);
    assert(start < list->Size);
    assert(size > 0);
    DelinkedList *slice = DelinkedListNew(list->elementSize, list->compare);
    DelinkedListNode *node = list->head;
    for (unsigned int i = 0; i < start; i++) {
        node = node->next;
    }
    for (unsigned int i = 0; i < size; i++) {
        DelinkedListPushBack(slice, node->value);
        node = node->next;
    }
    return slice;
}

/**
 * @brief Swap values of two specified elements. O(1).
 *
 * @param a Pointer refers to one element.
 * @param b Pointer refers to the other element.
 * @param cache Pointer refers to cache.
 * @param elementSize Element size of list.
 */
static inline void __swap(void *const restrict a, void *const restrict b,
                          void *const restrict cache,
                          const unsigned long elementSize) {
    memcpy(cache, a, elementSize);
    memcpy(a, b, elementSize);
    memcpy(b, cache, elementSize);
}

/**
 * @brief Quick sort algorithm. Sort `list` from node `left`(contained) to
 * node `right`(contained). O(log₂n).
 *
 * @param list List to be sorted.
 * @param left Start index.
 * @param right End index.
 * @param cache Pointer refers to cache.
 */
static void __QuickSort(DelinkedList *const restrict list,
                        DelinkedListNode *const restrict left,
                        DelinkedListNode *const restrict right, void *cache) {
    DelinkedListNode *pivot = left, *i = left, *j = right;
    while (i != j) {
        while (i != pivot && list->compare(i->value, pivot->value) <= 0) {
            i = i->next;
        }
        __swap(i->value, pivot->value, cache, list->elementSize);
        pivot = i;
        while (pivot != j && list->compare(j->value, pivot->value) > 0) {
            j = j->previous;
        }
        __swap(j->value, pivot->value, cache, list->elementSize);
        pivot = j;
    }

    if (left != pivot) __QuickSort(list, left, pivot->previous, cache);
    if (right != pivot) __QuickSort(list, pivot->next, right, cache);
}

void DelinkedListQuickSort(DelinkedList *const restrict list) {
    assert(list != NULL);
    void *cache = malloc(list->elementSize);
    assert(cache != NULL);
    __QuickSort(list, list->head, list->tail, cache);
    free(cache);
}

DelinkedListIterator DelinkedListGetIterator(
    DelinkedList *const restrict list) {
    assert(list != NULL);
    return list->head;
}

DelinkedListIterator DelinkedListGetReverseIterator(
    DelinkedList *const restrict list) {
    assert(list != NULL);
    return list->tail;
}

DelinkedListIterator DelinkedListIteratorNext(
    DelinkedListIterator const restrict iterator) {
    assert(iterator != NULL);
    return iterator->next;
}

DelinkedListIterator DelinkedListIteratorPrevious(
    DelinkedListIterator const restrict iterator) {
    assert(iterator != NULL);
    return iterator->previous;
}

void *DelinkedListIteratorGetValue(
    DelinkedListIterator const restrict iterator) {
    assert(iterator != NULL);
    return iterator->value;
}

Bool DelinkedListIteratorEnded(DelinkedListIterator const restrict iterator) {
    return iterator == NULL;
}
