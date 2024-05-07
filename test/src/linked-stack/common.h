#ifndef __LINKED_STACK_TEST__
#define __LINKED_STACK_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "linked-stack.h"
#include "test.h"

int error(LinkedStack **const restrict stack, const unsigned int i) {
    LinkedStackNode *node = (*stack)->tail;
    unsigned int j = i;
    printf("Element Incorrect At [%d]\nLinkedStack:\n", j);
    while (node != NULL) {
        Test *temp = (Test *)node->value;
        printf("[%d]: { %d, %d, %d }\n", j, temp->a, temp->b, temp->c);
        j++;
        node = node->previous;
    }
    LinkedStackDelete(stack);
    exit(-1);
}

#endif  // __LINKED_STACK_TEST__
