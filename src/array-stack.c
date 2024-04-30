#include "array-stack.h"

#include <errno.h>
#include <malloc.h>
#include <memory.h>

int ArrayStackConstruct(ArrayStack* const restrict stack,
                        const unsigned int initialCapacity,
                        const unsigned long elementSize) {
    if (stack == NULL || elementSize == 0 || initialCapacity == 0) {
        errno = EINVAL;
        return -1;
    }

    stack->array = calloc(initialCapacity, elementSize);
    if (stack->array == NULL) return -1;
    stack->Capacity = initialCapacity;
    stack->elementSize = elementSize;
    stack->Size = 0;
    return 0;
}

ArrayStack* ArrayStackNew(const unsigned int initialCapacity,
                          const unsigned long elementSize) {
    ArrayStack* stack = (ArrayStack*)malloc(sizeof(ArrayStack));
    if (ArrayStackConstruct(stack, initialCapacity, elementSize) == -1) {
        free(stack);
        return NULL;
    }
    return stack;
}

void ArrayStackDestruct(ArrayStack* const restrict stack) {
    if (stack == NULL) return;

    free(stack->array);
    stack->array = NULL;
    stack->Capacity = 0;
    stack->elementSize = 0;
    stack->Size = 0;
}

void ArrayStackDelete(ArrayStack** const restrict stack) {
    if (stack == NULL) return;
    ArrayStackDestruct(*stack);
    free(*stack);
    *stack = NULL;
}

void* ArrayStackTop(const ArrayStack* const restrict stack) {
    if (stack == NULL) {
        errno = EINVAL;
        return NULL;
    }

    if (stack->Size == 0) return NULL;
    return stack->array + stack->elementSize * (stack->Size - 1);
}

int ArrayStackPush(ArrayStack* const restrict stack,
                   const void* const restrict value) {
    void* temp = NULL;
    if (stack == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (stack->Size == stack->Capacity) {
        stack->Capacity *= 2;
        temp = calloc(stack->Capacity, stack->elementSize);
        if (temp == NULL) return -1;
        memcpy(temp, stack->array, stack->elementSize * stack->Size);
        free(stack->array);
        stack->array = temp;
    }
    memcpy(stack->array + stack->Size * stack->elementSize, value,
           stack->elementSize);
    stack->Size++;
    return 0;
}

int ArrayStackPop(ArrayStack* const restrict stack) {
    if (stack == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (stack->Size == 0) return 0;
    stack->Size--;
    return 0;
}