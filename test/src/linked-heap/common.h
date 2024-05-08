#ifndef __ARRAY_HEAP_TEST__
#define __ARRAY_HEAP_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "linked-heap.h"
#include "test.h"

int error(LinkedHeap **const restrict heap, const unsigned int i) {
    printf("Element Incorrect At [%d]\nLinkedHeap:\n", i);
    while ((*heap)->Size != 0) {
        Test *temp = (Test *)LinkedHeapTop(*heap);
        printf("{ %d, %d, %d }\n", temp->a, temp->b, temp->c);
        LinkedHeapPop(*heap);
    }
    LinkedHeapDelete(heap);
    exit(-1);
}

#endif  // __ARRAY_HEAP_TEST__
