#include "array-stack.h"

#include <assert.h>
#include <malloc.h>
#include <memory.h>

void ArrayStackConstruct(ArrayStack *const restrict stack,
                         const unsigned int initialCapacity,
                         const unsigned long elementSize) {
    assert(stack != NULL);
    assert(elementSize > 0);
    assert(initialCapacity > 0);

    stack->array = calloc(initialCapacity, elementSize);
    assert(stack->array != NULL);
    stack->Capacity = initialCapacity;
    stack->elementSize = elementSize;
    stack->Size = 0;
}

ArrayStack *ArrayStackNew(const unsigned int initialCapacity,
                          const unsigned long elementSize) {
    ArrayStack *stack = (ArrayStack *)malloc(sizeof(ArrayStack));
    ArrayStackConstruct(stack, initialCapacity, elementSize);
    return stack;
}

void ArrayStackDestruct(ArrayStack *const restrict stack) {
    if (stack == NULL) return;

    free(stack->array);
    stack->array = NULL;
    stack->Capacity = 0;
    stack->elementSize = 0;
    stack->Size = 0;
}

void ArrayStackDelete(ArrayStack **const restrict stack) {
    if (stack == NULL) return;
    ArrayStackDestruct(*stack);
    free(*stack);
    *stack = NULL;
}

void *ArrayStackTop(const ArrayStack *const restrict stack) {
    assert(stack != NULL);
    if (stack->Size == 0) return NULL;
    return stack->array + stack->elementSize * (stack->Size - 1);
}

void ArrayStackPush(ArrayStack *const restrict stack,
                    const void *const restrict value) {
    assert(stack != NULL);
    assert(value != NULL);
    void *temp = NULL;
    if (stack->Size == stack->Capacity) {
        stack->Capacity *= 2;
        temp = calloc(stack->Capacity, stack->elementSize);
        assert(temp != NULL);
        memcpy(temp, stack->array, stack->elementSize * stack->Size);
        free(stack->array);
        stack->array = temp;
    }
    memcpy(stack->array + stack->Size * stack->elementSize, value,
           stack->elementSize);
    stack->Size++;
}

void ArrayStackPop(ArrayStack *const restrict stack) {
    assert(stack != NULL);
    assert(stack->Size > 0);
    stack->Size--;
}