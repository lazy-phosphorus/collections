#include "array-queue.h"

#include <assert.h>
#include <malloc.h>
#include <memory.h>

#include "types.h"

void ArrayQueueConstruct(ArrayQueue *const restrict queue,
                         const unsigned int initialCapacity,
                         const unsigned long elementSize) {
    assert(queue != NULL);
    assert(initialCapacity > 0);
    assert(elementSize > 0);

    queue->array = calloc(initialCapacity, elementSize);
    assert(queue->array != NULL);
    queue->Capacity = initialCapacity;
    queue->elementSize = elementSize;
    queue->Size = 0;
}

ArrayQueue *ArrayQueueNew(const unsigned int initialCapacity,
                          const unsigned long elementSize) {
    ArrayQueue *queue = (ArrayQueue *)malloc(sizeof(ArrayQueue));
    ArrayQueueConstruct(queue, initialCapacity, elementSize);
    return queue;
}

void ArrayQueueDestruct(ArrayQueue *const restrict queue) {
    if (queue == NULL) return;

    free(queue->array);
    queue->Capacity = 0;
    queue->elementSize = 0;
    queue->Size = 0;
}

void ArrayQueueDelete(ArrayQueue **const restrict queue) {
    if (queue == NULL) return;
    ArrayQueueDestruct(*queue);
    free(*queue);
    *queue = NULL;
}

void *ArrayQueueFront(const ArrayQueue *const restrict queue) {
    assert(queue != NULL);
    if (queue->Size == 0) return NULL;
    return queue->array;
}

void ArrayQueuePush(ArrayQueue *const restrict queue,
                    const void *const restrict value) {
    assert(queue != NULL);
    assert(value != NULL);
    void *temp = NULL;
    if (queue->Size == queue->Capacity) {
        queue->Capacity *= 2;
        temp = calloc(queue->Capacity, queue->elementSize);
        assert(temp != NULL);
        memcpy(temp, queue->array, queue->Size * queue->elementSize);
        free(queue->array);
        queue->array = temp;
    }
    memcpy(queue->array + queue->Size * queue->elementSize, value,
           queue->elementSize);
    queue->Size++;
}

void ArrayQueuePop(ArrayQueue *const restrict queue) {
    assert(queue != NULL);
    assert(queue->Size > 0);

    queue->Size--;
    memmove(queue->array, queue->array + queue->elementSize,
            queue->Size * queue->elementSize);
}

Bool ArrayQueueSome(ArrayQueue *const restrict queue,
                    TestFunction *const test) {
    assert(queue != NULL);
    assert(test != NULL);

    void *temp = NULL;
    for (unsigned int i = 0; i < queue->Size; i++) {
        temp = queue->array + i * queue->elementSize;
        if (test(temp) == TRUE) return TRUE;
    }
    return FALSE;
}

Bool ArrayQueueAll(ArrayQueue *const restrict queue, TestFunction *const test) {
    assert(queue != NULL);
    assert(test != NULL);

    void *temp = NULL;
    for (unsigned int i = 0; i < queue->Size; i++) {
        temp = queue->array + i * queue->elementSize;
        if (test(temp) == FALSE) return FALSE;
    }
    return TRUE;
}
