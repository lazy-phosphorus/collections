#ifndef __LINKED_STACK_TEST__
#define __LINKED_STACK_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "array-stack.h"
#include "test.h"

int error(ArrayStack **const restrict stack, const unsigned int i) {
    printf("Element Incorrect At [%d]\nArrayStack:\n", i);
    for (unsigned int j = 0; j < (*stack)->Size; j++) {
        Test *temp = (Test *)(*stack)->array + j * (*stack)->elementSize;
        printf("[%d]: { %d, %d, %d }\n", j, temp->a, temp->b, temp->c);
    }

    ArrayStackDelete(stack);
    exit(-1);
}

#endif  // __LINKED_STACK_TEST__
