#ifndef __STACK_TEST__
#define __STACK_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "test.h"

int error(Stack **const restrict stack, const unsigned int i) {
    StackNode *node = (*stack)->tail;
    unsigned int j = i;
    printf("Element Incorrect At [%d]\nStack:\n", j);
    while (node != NULL) {
        Test *temp = (Test *)node->value;
        printf("[%d]: { %d, %d, %d }\n", j, temp->a, temp->b, temp->c);
        j++;
        node = node->previous;
    }
    StackDelete(stack);
    exit(-1);
}

#endif  // __STACK_TEST__