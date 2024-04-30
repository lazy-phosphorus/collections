#ifndef __ARRAY_HEAP_TEST__
#define __ARRAY_HEAP_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "array-heap.h"
#include "test.h"

int error(ArrayHeap **const restrict heap, const unsigned int i) {
    printf("Element Incorrect At [%d]\nArrayHeap:\n", i);
    for (unsigned int j = 0; j < (*heap)->Size; j++) {
        Test *temp = (Test *)((*heap)->array + j * (*heap)->elementSize);
        printf("[%d]: { %d, %d, %d }\n", j, temp->a, temp->b, temp->c);
    }
    ArrayHeapDelete(heap);
    exit(-1);
}

#endif  // __ARRAY_HEAP_TEST__
