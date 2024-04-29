#ifndef __DELINKED_LIST_TEST__
#define __DELINKED_LIST_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "delinked-list.h"
#include "test.h"

int error(DelinkedList **const restrict list, const unsigned int i) {
    printf("Element Incorrect At [%d]\nDelinkedList:\n", i);
    for (unsigned int i = 0; i < (*list)->Size; i++) {
        Test *temp = (Test *)DelinkedListGet(*list, i);
        printf("[%d]: { %d, %d, %d }\n", i, temp->a, temp->b, temp->c);
    }
    DelinkedListDelete(list);
    exit(-1);
}

#endif  // __DELINKED_LIST_TEST__
