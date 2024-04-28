#ifndef __ARRAY_TEST__
#define __ARRAY_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "test.h"

int error(List **const restrict list, const unsigned int i) {
    printf("Element Incorrect At [%d]\nList:\n", i);
    for (unsigned int i = 0; i < (*list)->Size; i++) {
        Test *temp = (Test *)ListGet(*list, i);
        printf("[%d]: { %d, %d, %d }\n", i, temp->a, temp->b, temp->c);
    }
    ListDelete(list);
    exit(-1);
}

#endif  // __ARRAY_TEST__