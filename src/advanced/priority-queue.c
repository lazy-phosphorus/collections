#include "priority-queue.h"

#include <assert.h>
#include <malloc.h>
#include <memory.h>

void PriorityQueueNodeConstruct(PriorityQueueNode *const restrict node,
                                const int priority,
                                const void *const restrict value,
                                unsigned long elementSize) {
    assert(node != NULL);
    assert(value != NULL);
    assert(elementSize > 0);

    node->value = malloc(elementSize);
    assert(node->value != NULL);
    memcpy(node->value, value, elementSize);
    node->priority = priority;
}

PriorityQueueNode *PriorityQueueNodeNew(const int priority,
                                        const void *const restrict value,
                                        unsigned long elementSize) {
    PriorityQueueNode *node =
        (PriorityQueueNode *)malloc(sizeof(PriorityQueueNode));
    PriorityQueueNodeConstruct(node, priority, value, elementSize);
    return node;
}

void PriorityQueueNodeDestruct(PriorityQueueNode *const restrict node) {
    if (node == NULL) return;

    free(node->value);
    node->value = NULL;
    node->priority = 0;
}

void PriorityQueueNodeDelete(PriorityQueueNode **const restrict node) {
    if (node == NULL) return;

    PriorityQueueNodeDestruct(*node);
    free(*node);
    *node = NULL;
}

static inline int __compare(const void *a, const void *b) {
    const PriorityQueueNode *c = (PriorityQueueNode *)a,
                            *d = (PriorityQueueNode *)b;
    return c->priority - d->priority;
}

void PriorityQueueConstruct(PriorityQueue *const restrict queue,
                            const unsigned int initialCapacity,
                            const unsigned long elementSize) {
    assert(queue != NULL);
    assert(initialCapacity > 0);
    assert(elementSize > 0);

    queue->heap =
        ArrayHeapNew(initialCapacity, sizeof(PriorityQueueNode), __compare);
    queue->elementSize = elementSize;
    queue->Size = 0;
}

PriorityQueue *PriorityQueueNew(const unsigned int initialCapacity,
                                const unsigned long elementSize) {
    PriorityQueue *queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    PriorityQueueConstruct(queue, initialCapacity, elementSize);
    return queue;
}

void PriorityQueueDestruct(PriorityQueue *const restrict queue) {
    PriorityQueueNode *temp = NULL;
    if (queue == NULL) return;

    for (unsigned int i = 0; i < queue->Size; i++) {
        temp = (PriorityQueueNode *)(queue->heap->array +
                                     i * sizeof(PriorityQueueNode));
        PriorityQueueNodeDestruct(temp);
    }
    ArrayHeapDelete(&queue->heap);
    queue->elementSize = 0;
}

void PriorityQueueDelete(PriorityQueue **const restrict queue) {
    if (queue == NULL) return;

    PriorityQueueDestruct(*queue);
    free(*queue);
    *queue = NULL;
}

void *PriorityQueueFront(const PriorityQueue *const restrict queue) {
    assert(queue != NULL);

    PriorityQueueNode *temp = (PriorityQueueNode *)ArrayHeapTop(queue->heap);
    if (temp == NULL) return NULL;
    return temp->value;
}

void PriorityQueuePush(PriorityQueue *const restrict queue, const int priority,
                       const void *const restrict value) {
    assert(queue != NULL);
    assert(value != NULL);

    PriorityQueueNode node;
    PriorityQueueNodeConstruct(&node, priority, value, queue->elementSize);
    ArrayHeapPush(queue->heap, &node);
    queue->Size = queue->heap->Size;
}

void PriorityQueuePop(PriorityQueue *const restrict queue) {
    assert(queue != NULL);
    ArrayHeapPop(queue->heap);
    queue->Size = queue->heap->Size;
}

Bool PriorityQueueSome(PriorityQueue *const restrict queue,
                       TestFunction *const test) {
    assert(queue != NULL);
    assert(test != NULL);

    PriorityQueueNode *temp = NULL;
    for (unsigned int i = 0; i < queue->Size; i++) {
        temp = (PriorityQueueNode *)(queue->heap->array +
                                     i * sizeof(PriorityQueueNode));
        if (test(temp->value) == TRUE) return TRUE;
    }
    return FALSE;
}

Bool PriorityQueueAll(PriorityQueue *const restrict queue,
                      TestFunction *const test) {
    assert(queue != NULL);
    assert(test != NULL);

    PriorityQueueNode *temp = NULL;
    for (unsigned int i = 0; i < queue->Size; i++) {
        temp = (PriorityQueueNode *)(queue->heap->array +
                                     i * sizeof(PriorityQueueNode));
        if (test(temp->value) == FALSE) return FALSE;
    }
    return TRUE;
}

PriorityQueueIterator PriorityQueueGetIterator(
    PriorityQueue *const restrict queue) {
    assert(queue != NULL);
    PriorityQueueIterator iterator = {
        queue->heap->array, queue->heap->elementSize, 0, queue->heap->Size};
    return iterator;
}

PriorityQueueIterator PriorityQueueGetReverseIterator(
    PriorityQueue *const restrict queue) {
    assert(queue != NULL);
    PriorityQueueIterator iterator = {queue->heap->array,
                                      queue->heap->elementSize,
                                      queue->heap->Size - 1, queue->heap->Size};
    return iterator;
}

PriorityQueueIterator PriorityQueueIteratorNext(
    PriorityQueueIterator const iterator) {
    assert(iterator.current < iterator.size);
    PriorityQueueIterator i = {iterator.array, iterator.elementSize,
                               iterator.current + 1, iterator.size};
    return i;
}

PriorityQueueIterator PriorityQueueIteratorPrevious(
    PriorityQueueIterator const iterator) {
    assert(iterator.current != -1);
    PriorityQueueIterator i = {iterator.array, iterator.elementSize,
                               iterator.current - 1, iterator.size};
    return i;
}

void *PriorityQueueIteratorGetValue(PriorityQueueIterator const iterator) {
    assert(iterator.current < iterator.size && iterator.current != -1);
    PriorityQueueNode *node =
        (PriorityQueueNode *)(iterator.array +
                              iterator.current * iterator.elementSize);
    return node->value;
}

Bool PriorityQueueIteratorEnded(PriorityQueueIterator const iterator) {
    return iterator.current == iterator.size || iterator.current == -1;
}
