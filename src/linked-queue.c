#include "linked-queue.h"

#include <asm-generic/errno-base.h>
#include <errno.h>
#include <malloc.h>
#include <memory.h>

int LinkedQueueNodeConstruct(LinkedQueueNode *const restrict node,
                             const void *const restrict value,
                             const unsigned int elementSize) {
    if (node == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }
    node->next = NULL;
    node->value = malloc(elementSize);
    if (node->value == NULL) return -1;
    memcpy(node->value, value, elementSize);
    return 0;
}

LinkedQueueNode *LinkedQueueNodeNew(const void *const restrict value,
                                    const unsigned int elementSize) {
    LinkedQueueNode *node = (LinkedQueueNode *)malloc(sizeof(LinkedQueueNode));
    if (node == NULL) return NULL;
    if (LinkedQueueNodeConstruct(node, value, elementSize) == -1) {
        free(node);
        return NULL;
    }
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

int LinkedQueueConstruct(LinkedQueue *const restrict queue,
                         const unsigned int elementSize) {
    if (queue == NULL || elementSize == 0) {
        errno = EINVAL;
        return -1;
    }

    queue->head = NULL;
    queue->tail = NULL;
    queue->elementSize = elementSize;
    queue->Size = 0;
    return 0;
}

LinkedQueue *LinkedQueueNew(const unsigned int elementSize) {
    LinkedQueue *queue = (LinkedQueue *)malloc(sizeof(LinkedQueue));
    if (LinkedQueueConstruct(queue, elementSize) == -1) {
        free(queue);
        return NULL;
    }
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
    if (queue == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (queue->Size == 0) return NULL;
    return queue->head->value;
}

int LinkedQueuePush(LinkedQueue *const restrict queue,
                    const void *const restrict value) {
    LinkedQueueNode *node = NULL;
    if (queue == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    node = LinkedQueueNodeNew(value, queue->elementSize);
    if (node == NULL) return -1;
    if (queue->Size > 0)
        queue->tail->next = node;
    else
        queue->head = node;
    queue->tail = node;
    queue->Size++;
    return 0;
}

int LinkedQueuePop(LinkedQueue *const restrict queue) {
    LinkedQueueNode *node = NULL;
    if (queue == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (queue->Size == 0)
        return 0;
    else if (queue->Size == 1)
        queue->tail = NULL;
    node = queue->head;
    queue->head = node->next;
    LinkedQueueNodeDelete(&node);
    queue->Size--;
    return 0;
}
