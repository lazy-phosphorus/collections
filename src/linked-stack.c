#include "linked-stack.h"

#include <errno.h>
#include <malloc.h>
#include <memory.h>

int LinkedStackNodeConstruct(LinkedStackNode* const restrict node,
                             const void* const restrict value,
                             const unsigned long elementSize) {
    if (node == NULL || value == NULL || elementSize == 0) {
        errno = EINVAL;
        return -1;
    }

    node->value = malloc(elementSize);
    if (node->value == NULL) return -1;
    memcpy(node->value, value, elementSize);
    node->previous = NULL;
    return 0;
}

LinkedStackNode* LinkedStackNodeNew(const void* const restrict value,
                                    const unsigned long elementSize) {
    LinkedStackNode* node = (LinkedStackNode*)malloc(sizeof(LinkedStackNode));
    if (node == NULL) return NULL;
    if (LinkedStackNodeConstruct(node, value, elementSize) == -1) {
        free(node);
        return NULL;
    }
    return node;
}

void LinkedStackNodeDestruct(LinkedStackNode* const restrict node) {
    if (node == NULL) return;

    free(node->value);
    node->value = NULL;
    node->previous = NULL;
}

void LinkedStackNodeDelete(LinkedStackNode** const restrict node) {
    if (node == NULL) return;

    LinkedStackNodeDestruct(*node);
    free(*node);
    *node = NULL;
}

int LinkedStackConstruct(LinkedStack* const restrict stack,
                         const unsigned long elementSize) {
    if (stack == NULL || elementSize == 0) {
        errno = EINVAL;
        return -1;
    }

    stack->tail = NULL;
    stack->elementSize = elementSize;
    stack->Size = 0;
    return 0;
}

LinkedStack* LinkedStackNew(const unsigned long elementSize) {
    LinkedStack* stack = (LinkedStack*)malloc(sizeof(LinkedStack));
    if (LinkedStackConstruct(stack, elementSize) == -1) {
        free(stack);
        return NULL;
    }
    return stack;
}

void LinkedStackDestruct(LinkedStack* const restrict stack) {
    LinkedStackNode* temp = NULL;
    if (stack == NULL) return;
    while (stack->tail != NULL) {
        temp = stack->tail->previous;
        LinkedStackNodeDelete(&stack->tail);
        stack->tail = temp;
    }
    stack->elementSize = 0;
    stack->Size = 0;
}

void LinkedStackDelete(LinkedStack** const restrict stack) {
    if (stack == NULL) return;
    LinkedStackDestruct(*stack);
    free(*stack);
    *stack = NULL;
}

void* LinkedStackTop(const LinkedStack* const restrict stack) {
    if (stack == NULL) {
        errno = EINVAL;
        return NULL;
    }

    if (stack->Size == 0) return NULL;
    return stack->tail->value;
}

int LinkedStackPush(LinkedStack* const restrict stack,
                    const void* const restrict value) {
    LinkedStackNode* node = NULL;
    if (stack == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    node = LinkedStackNodeNew(value, stack->elementSize);
    if (node == NULL) return -1;
    node->previous = stack->tail;
    stack->tail = node;
    stack->Size++;
    return 0;
}

int LinkedStackPop(LinkedStack* const restrict stack) {
    LinkedStackNode* node = NULL;
    if (stack == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (stack->Size == 0) return 0;
    node = stack->tail;
    stack->tail = node->previous;
    LinkedStackNodeDelete(&node);
    stack->Size--;
    return 0;
}
