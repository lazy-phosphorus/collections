#ifndef __LINKED_LIST_TEST__
#define __LINKED_LIST_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "linked-list.h"
#include "test.h"

int error(LinkedList **const restrict list, const unsigned int i) {
    printf("Element Incorrect At [%d]\nLinkedList:\n", i);
    for (unsigned int i = 0; i < (*list)->Size; i++) {
        Test *temp = (Test *)LinkedListGet(*list, i);
        printf("[%d]: { %d, %d, %d }\n", i, temp->a, temp->b, temp->c);
    }
    LinkedListDelete(list);
    exit(-1);
}

#endif  // __LINKED_LIST_TEST__
