#ifndef __ARRAY_LIST_TEST__
#define __ARRAY_LIST_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "array-list.h"
#include "test.h"

int error(ArrayList **const restrict list, const unsigned int i) {
    printf("Element Incorrect At [%d]\nArrayList:\n", i);
    for (unsigned int i = 0; i < (*list)->Size; i++) {
        Test *temp = (Test *)ArrayListGet(*list, i);
        printf("[%d]: { %d, %d, %d }\n", i, temp->a, temp->b, temp->c);
    }
    ArrayListDelete(list);
    exit(-1);
}

#endif  // __ARRAY_LIST_TEST__
