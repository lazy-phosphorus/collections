#include "array-heap.h"

#include <assert.h>
#include <malloc.h>
#include <memory.h>

void ArrayHeapConstruct(ArrayHeap *const restrict heap,
                        const unsigned int initialCapacity,
                        const unsigned long elementSize,
                        CompareFunction *const compare) {
    assert(heap != NULL);
    assert(initialCapacity > 0);
    assert(elementSize > 0);
    assert(compare != NULL);

    heap->array = calloc(initialCapacity, elementSize);
    assert(heap->array != NULL);
    heap->elementSize = elementSize;
    heap->Capacity = initialCapacity;
    heap->compare = compare;
    heap->Size = 0;
}

ArrayHeap *ArrayHeapNew(const unsigned int initialCapacity,
                        const unsigned long elementSize,
                        CompareFunction *const compare) {
    ArrayHeap *heap = (ArrayHeap *)malloc(sizeof(ArrayHeap));
    ArrayHeapConstruct(heap, initialCapacity, elementSize, compare);
    return heap;
}

void ArrayHeapDestruct(ArrayHeap *const restrict heap) {
    if (heap == NULL) return;
    free(heap->array);
    heap->array = NULL;
    heap->Capacity = 0;
    heap->Size = 0;
    heap->elementSize = 0;
    heap->compare = NULL;
}

void ArrayHeapDelete(ArrayHeap **const restrict heap) {
    if (heap == NULL) return;
    ArrayHeapDestruct(*heap);
    free(*heap);
    *heap = NULL;
}

void *ArrayHeapTop(const ArrayHeap *const restrict heap) {
    assert(heap != NULL);
    assert(heap->Size > 0);
    return heap->array;
}

void ArrayHeapPush(ArrayHeap *const restrict heap,
                   const void *const restrict value) {
    assert(heap != NULL);
    assert(value != NULL);
    void *temp = NULL;
    unsigned int current = heap->Size, parent = 0;
    if (heap->Size == heap->Capacity) {
        heap->Capacity *= 2;
        temp = calloc(heap->Capacity, heap->elementSize);
        assert(temp != NULL);
        memcpy(temp, heap->array, heap->Size * heap->elementSize);
        free(heap->array);
        heap->array = temp;
    }
    while (current != 0) {
        parent = current % 2 == 0 ? (current - 1) / 2 : current / 2;
        if (heap->compare(value, heap->array + parent * heap->elementSize) <= 0)
            break;
        memcpy(heap->array + current * heap->elementSize,
               heap->array + parent * heap->elementSize, heap->elementSize);
        current = parent;
    }
    memcpy(heap->array + current * heap->elementSize, value, heap->elementSize);
    heap->Size++;
}

void ArrayHeapPop(ArrayHeap *const restrict heap) {
    assert(heap != NULL);
    assert(heap->Size > 0);
    unsigned int current = 0;

    heap->Size--;
    while ((current * 2 + 1) < heap->Size) {
        if (heap->compare(
                heap->array + heap->elementSize * (current * 2 + 1),
                heap->array + heap->elementSize * (current * 2 + 2)) >= 0) {
            // left child is larger than or equal to right child
            if (heap->compare(
                    heap->array + heap->elementSize * (current * 2 + 1),
                    heap->array + heap->elementSize * heap->Size) > 0) {
                // less than left child
                memcpy(heap->array + heap->elementSize * current,
                       heap->array + heap->elementSize * (current * 2 + 1),
                       heap->elementSize);
                current = current * 2 + 1;
            } else
                break;
        } else {
            // left child is less than right child
            if (heap->compare(
                    heap->array + heap->elementSize * (current * 2 + 2),
                    heap->array + heap->elementSize * heap->Size) > 0) {
                // less than right child
                memcpy(heap->array + heap->elementSize * current,
                       heap->array + heap->elementSize * (current * 2 + 2),
                       heap->elementSize);
                current = current * 2 + 2;
            } else
                break;
        }
    }
    memcpy(heap->array + heap->elementSize * current,
           heap->array + heap->elementSize * heap->Size, heap->elementSize);
}

ArrayHeapIterator ArrayHeapGetIterator(ArrayHeap *const restrict heap) {
    assert(heap != NULL);
    ArrayHeapIterator iterator = {heap->array, heap->elementSize, 0,
                                  heap->Size};
    return iterator;
}

ArrayHeapIterator ArrayHeapGetReverseIterator(ArrayHeap *const restrict heap) {
    assert(heap != NULL);
    ArrayHeapIterator iterator = {heap->array, heap->elementSize,
                                  heap->Size - 1, heap->Size};
    return iterator;
}

ArrayHeapIterator ArrayHeapIteratorNext(ArrayHeapIterator const iterator) {
    assert(iterator.current < iterator.size);
    ArrayHeapIterator i = {iterator.array, iterator.elementSize,
                           iterator.current + 1, iterator.size};
    return i;
}

ArrayHeapIterator ArrayHeapIteratorPrevious(ArrayHeapIterator const iterator) {
    assert(iterator.current != -1);
    ArrayHeapIterator i = {iterator.array, iterator.elementSize,
                           iterator.current - 1, iterator.size};
    return i;
}

void *ArrayHeapIteratorGetValue(ArrayHeapIterator const iterator) {
    assert(iterator.current < iterator.size && iterator.current != -1);
    return iterator.array + iterator.current * iterator.elementSize;
}

Bool ArrayHeapIteratorEnded(ArrayHeapIterator const iterator) {
    return iterator.current == iterator.size || iterator.current == -1;
}
