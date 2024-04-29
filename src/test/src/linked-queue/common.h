#ifndef __LINKED_STACK_TEST__
#define __LINKED_STACK_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "linked-queue.h"
#include "test.h"

int error(LinkedQueue **const restrict queue, const unsigned int i) {
    LinkedQueueNode *node = (*queue)->head;
    unsigned int j = i;
    printf("Element Incorrect At [%d]\nLinkedQueue:\n", j);
    while (node != NULL) {
        Test *temp = (Test *)node->value;
        printf("[%d]: { %d, %d, %d }\n", j, temp->a, temp->b, temp->c);
        j++;
        node = node->next;
    }
    LinkedQueueDelete(queue);
    exit(-1);
}

#endif  // __LINKED_STACK_TEST__
