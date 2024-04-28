#ifndef __ARRAY_TEST__
#define __ARRAY_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "test.h"

int error(Array **const array, unsigned int i) {
    printf("Element Incorrect At [%d]\nArray:\n", i);
    for (unsigned int i = 0; i < (*array)->Size; i++) {
        Test *temp = (Test *)ArrayGet(*array, i);
        printf("[%d]: { %d, %d, %d }\n", i, temp->a, temp->b, temp->c);
    }
    ArrayDelete(array);
    exit(-1);
}

#endif  // __ARRAY_TEST__