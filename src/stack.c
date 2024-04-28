#include "stack.h"

#include <asm-generic/errno-base.h>
#include <errno.h>
#include <malloc.h>
#include <memory.h>

int StackNodeConstruct(StackNode* const restrict node,
                       const void* const restrict value,
                       const unsigned int elementSize) {
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

StackNode* StackNodeNew(const void* const restrict value,
                        const unsigned int elementSize) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    if (node == NULL) return NULL;
    if (StackNodeConstruct(node, value, elementSize) == -1) {
        free(node);
        return NULL;
    }
    return node;
}

void StackNodeDestruct(StackNode* const restrict node) {
    if (node == NULL) return;

    free(node->value);
}

void StackNodeDelete(StackNode** const restrict node) {
    if (node == NULL) return;

    StackNodeDestruct(*node);
    free(*node);
    *node = NULL;
}

int StackConstruct(Stack* const restrict stack,
                   const unsigned int elementSize) {
    if (stack == NULL || elementSize == 0) {
        errno = EINVAL;
        return -1;
    }
    stack->tail = NULL;
    stack->elementSize = elementSize;
    stack->Size = 0;
    return 0;
}

Stack* StackNew(const unsigned int elementSize) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (StackConstruct(stack, elementSize) == -1) {
        free(stack);
        return NULL;
    }
    return stack;
}

void StackDestruct(Stack* const restrict stack) {
    StackNode* temp = NULL;
    if (stack == NULL) return;
    while (stack->tail != NULL) {
        temp = stack->tail->previous;
        StackNodeDelete(&stack->tail);
        stack->tail = temp;
    }
}

void StackDelete(Stack** const restrict stack) {
    if (stack == NULL) return;
    StackDestruct(*stack);
    free(*stack);
    *stack = NULL;
}

void* StackTop(const Stack* const restrict stack);

int StackPush(Stack* const restrict stack);

int StackPop(Stack* const restrict stack);