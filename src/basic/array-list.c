#include "array-list.h"

#include <assert.h>
#include <malloc.h>
#include <memory.h>

void ArrayListConstruct(ArrayList *const restrict list,
                        const unsigned int initialCapacity,
                        const unsigned long elementSize,
                        CompareFunction *const compare) {
    assert(list != NULL);
    assert(initialCapacity > 0);
    assert(elementSize > 0);
    assert(compare != NULL);

    list->array = calloc(initialCapacity, elementSize);
    assert(list->array != NULL);
    list->elementSize = elementSize;
    list->Capacity = initialCapacity;
    list->Size = 0;
    list->compare = compare;
}

ArrayList *ArrayListNew(const unsigned int initialCapacity,
                        const unsigned long elementSize,
                        CompareFunction *const compare) {
    ArrayList *list = (ArrayList *)malloc(sizeof(ArrayList));
    ArrayListConstruct(list, initialCapacity, elementSize, compare);
    return list;
}

void ArrayListDestruct(ArrayList *const restrict list) {
    if (list == NULL) return;

    free(list->array);
    list->array = NULL;
    list->elementSize = 0;
    list->Capacity = 0;
    list->Size = 0;
}

void ArrayListDelete(ArrayList **const restrict list) {
    if (list == NULL) return;

    ArrayListDestruct(*list);
    free(*list);
    *list = NULL;
}

void *ArrayListGet(const ArrayList *const restrict list,
                   const unsigned int index) {
    assert(list != NULL);
    assert(index < list->Size);
    return list->array + index * list->elementSize;
}

void ArrayListSet(ArrayList *const restrict list, const unsigned int index,
                  const void *const restrict value) {
    assert(list != NULL);
    assert(value != NULL);
    assert(index < list->Size);
    memcpy(list->array + index * list->elementSize, value, list->elementSize);
}

void *ArrayListBack(const ArrayList *const restrict list) {
    assert(list != NULL);
    if (list->Size == 0) return NULL;
    return list->array + list->elementSize * (list->Size - 1);
}

void *ArrayListFront(const ArrayList *const restrict list) {
    assert(list != NULL);
    if (list->Size == 0) return NULL;
    return list->array;
}

void ArrayListPushBack(ArrayList *const restrict list,
                       const void *const restrict value) {
    assert(list != NULL);
    assert(value != NULL);
    void *temp = NULL;

    if (list->Size == list->Capacity) {
        list->Capacity *= 2;
        temp = calloc(list->Capacity, list->elementSize);
        assert(temp != NULL);
        memcpy(temp, list->array, list->Size * list->elementSize);
        free(list->array);
        list->array = temp;
    }
    memcpy(list->array + list->Size * list->elementSize, value,
           list->elementSize);
    list->Size++;
}

void ArrayListPopBack(ArrayList *const restrict list) {
    assert(list != NULL);
    assert(list->Size > 0);
    list->Size--;
}

void ArrayListPushFront(ArrayList *const restrict list,
                        const void *const restrict value) {
    assert(list != NULL);
    assert(value != NULL);
    void *temp = NULL;

    if (list->Size == list->Capacity) {
        list->Capacity *= 2;
        temp = calloc(list->Capacity, list->elementSize);
        assert(temp != NULL);
        memcpy(temp + list->elementSize, list->array,
               list->Size * list->elementSize);
        free(list->array);
        list->array = temp;
    } else {
        memmove(list->array + list->elementSize, list->array,
                list->Size * list->elementSize);
    }
    memcpy(list->array, value, list->elementSize);
    list->Size++;
}

void ArrayListPopFront(ArrayList *const restrict list) {
    assert(list != NULL);
    assert(list->Size > 0);
    list->Size--;
    memmove(list->array, list->array + list->elementSize,
            list->elementSize * list->Size);
}

void ArrayListInsert(ArrayList *const restrict list, const unsigned int index,
                     const void *const restrict value) {
    assert(list != NULL);
    assert(value != NULL);
    assert(index <= list->Size);
    void *temp = NULL;

    if (list->Size == list->Capacity) {
        if (list->Size == list->Capacity) {
            list->Capacity *= 2;
            temp = calloc(list->Capacity, list->elementSize);
            assert(temp != NULL);
            memcpy(temp, list->array, index * list->elementSize);
            memcpy(temp + list->elementSize * (index + 1),
                   list->array + list->elementSize * index,
                   list->elementSize * (list->Size - index));
            free(list->array);
            list->array = temp;
        }
    } else {
        memmove(list->array + list->elementSize * (index + 1),
                list->array + list->elementSize * index,
                list->elementSize * (list->Size - index));
    }
    memcpy(list->array + list->elementSize * index, value, list->elementSize);
    list->Size++;
}

int ArrayListFind(const ArrayList *const restrict list,
                  const void *const restrict value) {
    assert(list != NULL);
    assert(value != NULL);
    for (unsigned int i = 0; i < list->Size; i++) {
        if (list->compare(list->array + list->elementSize * i, value) == 0)
            return i;
    }
    return -1;
}

ArrayList *ArrayListSlice(const ArrayList *const restrict list,
                          const unsigned int start, const unsigned int size) {
    assert(list != NULL);
    assert(start < list->Size);
    assert(size > 0);
    ArrayList *slice = ArrayListNew(size, list->elementSize, list->compare);
    memcpy(slice->array, list->array + list->elementSize * start,
           list->elementSize * size);
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
 * @brief Quick sort algorithm. Sort `list` from index `left`(contained) to
 * index `right`(contained). O(log₂n).
 *
 * @param list List to be sorted.
 * @param left Start index.
 * @param right End index.
 * @param cache Pointer refers to cache.
 */
static void __QuickSort(ArrayList *const restrict list, const unsigned int left,
                        const unsigned int right, void *cache) {
    unsigned int pivot = (left + right) / 2, i = left, j = right;
    while (i < j) {
        while (i < pivot &&
               list->compare(list->array + i * list->elementSize,
                             list->array + pivot * list->elementSize) <= 0) {
            i++;
        }
        __swap(list->array + i * list->elementSize,
               list->array + pivot * list->elementSize, cache,
               list->elementSize);
        pivot = i;
        while (pivot < j &&
               list->compare(list->array + j * list->elementSize,
                             list->array + pivot * list->elementSize) > 0) {
            j--;
        }
        __swap(list->array + j * list->elementSize,
               list->array + pivot * list->elementSize, cache,
               list->elementSize);
        pivot = j;
    }

    if (pivot != left) __QuickSort(list, left, pivot - 1, cache);
    if (pivot != right) __QuickSort(list, pivot + 1, right, cache);
}

void ArrayListQuickSort(ArrayList *const restrict list) {
    assert(list != NULL);
    void *cache = malloc(list->elementSize);
    assert(cache != NULL);
    __QuickSort(list, 0, list->Size - 1, cache);
    free(cache);
}

ArrayListIterator ArrayListGetIterator(ArrayList *const restrict list) {
    assert(list != NULL);
    ArrayListIterator iterator = {list->array, list->elementSize, 0,
                                  list->Size};
    return iterator;
}

ArrayListIterator ArrayListGetReverseIterator(ArrayList *const restrict list) {
    assert(list != NULL);
    ArrayListIterator iterator = {list->array, list->elementSize,
                                  list->Size - 1, list->Size};
    return iterator;
}

ArrayListIterator ArrayListIteratorNext(ArrayListIterator const iterator) {
    assert(iterator.current < iterator.size);
    ArrayListIterator i = {iterator.array, iterator.elementSize,
                           iterator.current + 1, iterator.size};
    return i;
}

ArrayListIterator ArrayListIteratorPrevious(ArrayListIterator const iterator) {
    assert(iterator.current != -1);
    ArrayListIterator i = {iterator.array, iterator.elementSize,
                           iterator.current - 1, iterator.size};
    return i;
}

void *ArrayListIteratorGetValue(ArrayListIterator const iterator) {
    assert(iterator.current < iterator.size && iterator.current != -1);
    return iterator.array + iterator.current * iterator.elementSize;
}

Bool ArrayListIteratorEnded(ArrayListIterator const iterator) {
    return iterator.current == iterator.size || iterator.current == -1;
}
