#ifndef __DELIST_TEST__
#define __DELIST_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "delist.h"
#include "test.h"

int error(Delist **const restrict list, const unsigned int i) {
    printf("Element Incorrect At [%d]\nDelist:\n", i);
    for (unsigned int i = 0; i < (*list)->Size; i++) {
        Test *temp = (Test *)DelistGet(*list, i);
        printf("[%d]: { %d, %d, %d }\n", i, temp->a, temp->b, temp->c);
    }
    DelistDelete(list);
    exit(-1);
}

#endif  // __DELIST_TEST__