#include "linked-stack.h"

#include <assert.h>
#include <malloc.h>
#include <memory.h>

void LinkedStackNodeConstruct(LinkedStackNode *const restrict node,
                              const void *const restrict value,
                              const unsigned long elementSize) {
    assert(node != NULL);
    assert(value != NULL);
    assert(elementSize > 0);

    node->value = malloc(elementSize);
    memcpy(node->value, value, elementSize);
    node->previous = NULL;
}

LinkedStackNode *LinkedStackNodeNew(const void *const restrict value,
                                    const unsigned long elementSize) {
    LinkedStackNode *node = (LinkedStackNode *)malloc(sizeof(LinkedStackNode));
    LinkedStackNodeConstruct(node, value, elementSize);
    return node;
}

void LinkedStackNodeDestruct(LinkedStackNode *const restrict node) {
    if (node == NULL) return;

    free(node->value);
    node->value = NULL;
    node->previous = NULL;
}

void LinkedStackNodeDelete(LinkedStackNode **const restrict node) {
    if (node == NULL) return;

    LinkedStackNodeDestruct(*node);
    free(*node);
    *node = NULL;
}

void LinkedStackConstruct(LinkedStack *const restrict stack,
                          const unsigned long elementSize) {
    assert(stack != NULL);
    assert(elementSize > 0);

    stack->tail = NULL;
    stack->elementSize = elementSize;
    stack->Size = 0;
}

LinkedStack *LinkedStackNew(const unsigned long elementSize) {
    LinkedStack *stack = (LinkedStack *)malloc(sizeof(LinkedStack));
    LinkedStackConstruct(stack, elementSize);
    return stack;
}

void LinkedStackDestruct(LinkedStack *const restrict stack) {
    LinkedStackNode *temp = NULL;
    if (stack == NULL) return;
    while (stack->tail != NULL) {
        temp = stack->tail->previous;
        LinkedStackNodeDelete(&stack->tail);
        stack->tail = temp;
    }
    stack->elementSize = 0;
    stack->Size = 0;
}

void LinkedStackDelete(LinkedStack **const restrict stack) {
    if (stack == NULL) return;
    LinkedStackDestruct(*stack);
    free(*stack);
    *stack = NULL;
}

void *LinkedStackTop(const LinkedStack *const restrict stack) {
    assert(stack != NULL);
    assert(stack->Size > 0);
    return stack->tail->value;
}

void LinkedStackPush(LinkedStack *const restrict stack,
                     const void *const restrict value) {
    assert(stack != NULL);
    assert(value != NULL);
    LinkedStackNode *node = LinkedStackNodeNew(value, stack->elementSize);
    node->previous = stack->tail;
    stack->tail = node;
    stack->Size++;
}

void LinkedStackPop(LinkedStack *const restrict stack) {
    assert(stack != NULL);
    assert(stack->Size > 0);
    LinkedStackNode *node = stack->tail;
    stack->tail = node->previous;
    LinkedStackNodeDelete(&node);
    stack->Size--;
}

LinkedStackIterator LinkedStackGetIterator(LinkedStack *const restrict stack) {
    assert(stack != NULL);
    return stack->tail;
}

LinkedStackIterator LinkedStackIteratorPrevious(
    LinkedStackIterator const restrict iterator) {
    assert(iterator != NULL);
    return iterator->previous;
}

void *LinkedStackIteratorGetValue(LinkedStackIterator const restrict iterator) {
    assert(iterator != NULL);
    return iterator->value;
}

Bool LinkedStackIteratorEnded(LinkedStackIterator const restrict iterator) {
    return iterator == NULL;
}
