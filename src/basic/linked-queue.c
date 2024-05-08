#include "linked-queue.h"

#include <assert.h>
#include <malloc.h>
#include <memory.h>

#include "types.h"

void LinkedQueueNodeConstruct(LinkedQueueNode *const restrict node,
                              const void *const restrict value,
                              const unsigned long elementSize) {
    assert(node != NULL);
    assert(value != NULL);
    node->value = malloc(elementSize);
    assert(node->value != NULL);
    node->next = NULL;
    memcpy(node->value, value, elementSize);
}

LinkedQueueNode *LinkedQueueNodeNew(const void *const restrict value,
                                    const unsigned long elementSize) {
    LinkedQueueNode *node = (LinkedQueueNode *)malloc(sizeof(LinkedQueueNode));
    LinkedQueueNodeConstruct(node, value, elementSize);
    return node;
}

void LinkedQueueNodeDestruct(LinkedQueueNode *const restrict node) {
    if (node == NULL) return;

    free(node->value);
    node->value = NULL;
    node->next = NULL;
}

void LinkedQueueNodeDelete(LinkedQueueNode **const restrict node) {
    if (node == NULL) return;

    LinkedQueueNodeDestruct(*node);
    free(*node);
    *node = NULL;
}

void LinkedQueueConstruct(LinkedQueue *const restrict queue,
                          const unsigned long elementSize) {
    assert(queue != NULL);
    assert(elementSize > 0);

    queue->head = NULL;
    queue->tail = NULL;
    queue->elementSize = elementSize;
    queue->Size = 0;
}

LinkedQueue *LinkedQueueNew(const unsigned long elementSize) {
    LinkedQueue *queue = (LinkedQueue *)malloc(sizeof(LinkedQueue));
    LinkedQueueConstruct(queue, elementSize);
    return queue;
}

void LinkedQueueDestruct(LinkedQueue *const restrict queue) {
    LinkedQueueNode *temp = NULL;
    if (queue == NULL) return;
    while (queue->head != NULL) {
        temp = queue->head;
        queue->head = temp->next;
        LinkedQueueNodeDelete(&temp);
    }
    queue->tail = NULL;
    queue->elementSize = 0;
    queue->Size = 0;
}

void LinkedQueueDelete(LinkedQueue **const restrict queue) {
    if (queue == NULL) return;
    LinkedQueueDestruct(*queue);
    free(*queue);
    *queue = NULL;
}

void *LinkedQueueFront(const LinkedQueue *const restrict queue) {
    assert(queue != NULL);
    if (queue->Size == 0) return NULL;
    return queue->head->value;
}

void LinkedQueuePush(LinkedQueue *const restrict queue,
                     const void *const restrict value) {
    assert(queue != NULL);
    assert(value != NULL);
    LinkedQueueNode *node = LinkedQueueNodeNew(value, queue->elementSize);
    if (queue->Size > 0)
        queue->tail->next = node;
    else
        queue->head = node;
    queue->tail = node;
    queue->Size++;
}

void LinkedQueuePop(LinkedQueue *const restrict queue) {
    assert(queue != NULL);
    assert(queue->Size > 0);
    LinkedQueueNode *node = NULL;
    if (queue->Size == 1) queue->tail = NULL;
    node = queue->head;
    queue->head = node->next;
    LinkedQueueNodeDelete(&node);
    queue->Size--;
}

Bool LinkedQueueSome(LinkedQueue *const restrict queue,
                     TestFunction *const test) {
    assert(queue != NULL);
    assert(test != NULL);

    LinkedQueueNode *temp = queue->head;
    while (temp != NULL) {
        if (test(temp->value) == TRUE) return TRUE;
        temp = temp->next;
    }
    return FALSE;
}

Bool LinkedQueueAll(LinkedQueue *const restrict queue,
                    TestFunction *const test) {
    assert(queue != NULL);
    assert(test != NULL);

    LinkedQueueNode *temp = queue->head;
    while (temp != NULL) {
        if (test(temp->value) == FALSE) return FALSE;
        temp = temp->next;
    }
    return TRUE;
}
