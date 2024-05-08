#ifndef __PRIORITY_QUEUE_TEST__
#define __PRIORITY_QUEUE_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "priority-queue.h"
#include "test.h"

int error(PriorityQueue **const restrict queue, const unsigned int i) {
    printf("Element Incorrect At [%d]\nPriorityQueue:\n", i);
    for (unsigned int j = 0; j < (*queue)->Size; j++) {
        PriorityQueueNode *node =
            (PriorityQueueNode *)((*queue)->heap->array +
                                  j * sizeof(PriorityQueueNode));
        Test *temp = (Test *)node->value;
        printf("[%d]: { %d, %d, %d }\n", j, temp->a, temp->b, temp->c);
    }
    PriorityQueueDelete(queue);
    exit(-1);
}

#endif  // __PRIORITY_QUEUE_TEST__
