#ifndef __LINKED_STACK_TEST__
#define __LINKED_STACK_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "array-queue.h"
#include "test.h"

int error(ArrayQueue **const restrict queue, const unsigned int i) {
    unsigned int j = i;
    printf("Element Incorrect At [%d]\nArrayQueue:\n", j);
    for (unsigned int j = 0; j < (*queue)->Size; j++) {
        Test *temp = (Test *)(*queue)->array + j * (*queue)->elementSize;
        printf("[%d]: { %d, %d, %d }\n", j, temp->a, temp->b, temp->c);
    }
    ArrayQueueDelete(queue);
    exit(-1);
}

#endif  // __LINKED_STACK_TEST__
