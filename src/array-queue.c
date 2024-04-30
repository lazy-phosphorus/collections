#include "array-queue.h"

#include <errno.h>
#include <malloc.h>
#include <memory.h>

int ArrayQueueConstruct(ArrayQueue *const restrict queue,
                        const unsigned int initialCapacity,
                        const unsigned long elementSize) {
    if (queue == NULL || elementSize == 0 || initialCapacity == 0) {
        errno = EINVAL;
        return -1;
    }

    queue->array = calloc(initialCapacity, elementSize);
    if (queue->array == NULL) return -1;
    queue->Capacity = initialCapacity;
    queue->elementSize = elementSize;
    queue->Size = 0;
    return 0;
}

ArrayQueue *ArrayQueueNew(const unsigned int initialCapacity,
                          const unsigned long elementSize) {
    ArrayQueue *queue = (ArrayQueue *)malloc(sizeof(ArrayQueue));
    if (ArrayQueueConstruct(queue, initialCapacity, elementSize) == -1) {
        free(queue);
        return NULL;
    }
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
    if (queue == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (queue->Size == 0) return NULL;
    return queue->array;
}

int ArrayQueuePush(ArrayQueue *const restrict queue,
                   const void *const restrict value) {
    void *temp = NULL;
    if (queue == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (queue->Size == queue->Capacity) {
        queue->Capacity *= 2;
        temp = calloc(queue->Capacity, queue->elementSize);
        if (temp == NULL) return -1;
        memcpy(temp, queue->array, queue->Size * queue->elementSize);
        free(queue->array);
        queue->array = temp;
    }
    memcpy(queue->array + queue->Size * queue->elementSize, value,
           queue->elementSize);
    queue->Size++;
    return 0;
}

int ArrayQueuePop(ArrayQueue *const restrict queue) {
    if (queue == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (queue->Size == 0) return 0;
    queue->Size--;
    memmove(queue->array, queue->array + queue->elementSize,
            queue->Size * queue->elementSize);
    return 0;
}
