#include "delinked-list.h"

#include <errno.h>
#include <malloc.h>
#include <memory.h>

int DelinkedListNodeConstruct(DelinkedListNode *const node,
                              const void *const restrict value,
                              unsigned long elementSize) {
    if (node == NULL || value == NULL || elementSize == 0) {
        errno = EINVAL;
        return -1;
    }
    node->value = malloc(elementSize);
    if (node->value == NULL) return -1;
    memcpy(node->value, value, elementSize);
    node->previous = NULL;
    node->next = NULL;
    return 0;
}

DelinkedListNode *DelinkedListNodeNew(const void *const restrict value,
                                      unsigned long elementSize) {
    DelinkedListNode *node =
        (DelinkedListNode *)malloc(sizeof(DelinkedListNode));
    if (node == NULL) return NULL;
    if (DelinkedListNodeConstruct(node, value, elementSize) == -1) {
        free(node);
        return NULL;
    }
    return node;
}

void DelinkedListNodeDestruct(DelinkedListNode *const node) {
    if (node == NULL) return;
    free(node->value);
    node->value = NULL;
    node->previous = NULL;
    node->next = NULL;
}

void DelinkedListNodeDelete(DelinkedListNode **const node) {
    if (node == NULL) return;
    DelinkedListNodeDestruct(*node);
    free(*node);
    *node = NULL;
}

int DelinkedListConstruct(DelinkedList *const restrict list,
                          const unsigned long elementSize,
                          CompareFunction *const compare) {
    if (list == NULL || compare == NULL || elementSize == 0 ||
        compare == NULL) {
        errno = EINVAL;
        return -1;
    }

    list->head = NULL;
    list->tail = NULL;
    list->elementSize = elementSize;
    list->compare = compare;
    list->Size = 0;
    return 0;
}

DelinkedList *DelinkedListNew(const unsigned long elementSize,
                              CompareFunction *const compare) {
    DelinkedList *list = (DelinkedList *)malloc(sizeof(DelinkedList));
    if (list == NULL) return NULL;
    if (DelinkedListConstruct(list, elementSize, compare) == -1) {
        free(list);
        return NULL;
    }
    return list;
}

void DelinkedListDestruct(DelinkedList *const restrict list) {
    DelinkedListNode *node = NULL, *temp = NULL;
    if (list == NULL) return;

    node = list->head;
    while (node != NULL) {
        temp = node->next;
        DelinkedListNodeDelete(&node);
        node = temp;
    }
    list->compare = NULL;
    list->elementSize = 0;
    list->Size = 0;
    list->head = NULL;
    list->tail = NULL;
}

void DelinkedListDelete(DelinkedList **const restrict list) {
    if (list == NULL) return;

    DelinkedListDestruct(*list);
    free(*list);
    *list = NULL;
}

void *DelinkedListGet(const DelinkedList *const restrict list,
                      const unsigned int index) {
    DelinkedListNode *node = NULL;
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (index > list->Size) {
        errno = EDOM;
        return NULL;
    }

    node = list->head;
    for (unsigned int i = 0; i < index; i++) {
        node = node->next;
    }
    return node->value;
}

int DelinkedListSet(DelinkedList *const restrict list, const unsigned int index,
                    const void *const restrict value) {
    DelinkedListNode *node = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (index > list->Size) {
        errno = EDOM;
        return -1;
    }

    node = list->head;
    for (unsigned int i = 0; i < index; i++) {
        node = node->next;
    }
    memcpy(node->value, value, list->elementSize);
    return 0;
}

void *DelinkedListBack(DelinkedList *const restrict list) {
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (list->Size == 0) return NULL;
    return list->tail->value;
}

void *DelinkedListFront(DelinkedList *const restrict list) {
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (list->Size == 0) return NULL;
    return list->head->value;
}

int DelinkedListPushBack(DelinkedList *const restrict list,
                         const void *const restrict value) {
    DelinkedListNode *node = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    node = DelinkedListNodeNew(value, list->elementSize);
    if (node == NULL) return -1;
    if (list->Size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        node->previous = list->tail;
        list->tail = node;
    }
    list->Size++;
    return 0;
}

int DelinkedListPopBack(DelinkedList *const restrict list) {
    DelinkedListNode *node = NULL;
    if (list == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (list->Size == 0) return 0;
    if (list->Size == 1) {
        DelinkedListNodeDelete(&list->tail);
        list->head = NULL;
        list->tail = NULL;
        list->Size = 0;
        return 0;
    }

    node = list->tail;
    list->tail = node->previous;
    list->tail->next = NULL;
    DelinkedListNodeDelete(&node);
    list->Size--;
    return 0;
}

int DelinkedListPushFront(DelinkedList *const restrict list,
                          const void *const restrict value) {
    DelinkedListNode *node = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    node = DelinkedListNodeNew(value, list->elementSize);
    if (node == NULL) return -1;
    if (list->Size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head->previous = node;
        list->head = node;
    }
    list->Size++;
    return 0;
}

int DelinkedListPopFront(DelinkedList *const restrict list) {
    DelinkedListNode *node = NULL;
    if (list == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (list->Size == 0) return 0;
    if (list->Size == 1) {
        DelinkedListNodeDelete(&list->head);
        list->head = NULL;
        list->tail = NULL;
        list->Size = 0;
        return 0;
    }

    node = list->head;
    list->head = node->next;
    list->head->previous = NULL;
    DelinkedListNodeDelete(&node);
    list->Size--;
    return 0;
}

int DelinkedListInsert(DelinkedList *const restrict list, const unsigned index,
                       const void *const restrict value) {
    DelinkedListNode *node = NULL, *temp = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (index > list->Size) {
        errno = EDOM;
        return -1;
    }

    if (index == 0)
        return DelinkedListPushFront(list, value);
    else if (index == list->Size)
        return DelinkedListPushBack(list, value);
    else {
        node = DelinkedListNodeNew(value, list->elementSize);
        if (node == NULL) return -1;
        temp = list->head;
        for (unsigned int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next->previous = node;
        temp->next = node;
        node->previous = temp;
        list->Size++;
        return 0;
    }
}

int DelinkedListFind(DelinkedList *const restrict list,
                     const void *const restrict value) {
    DelinkedListNode *node = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    node = list->head;
    for (int i = 0; i < list->Size; i++) {
        if (list->compare(node->value, value) == 0) return i;
        node = node->next;
    }
    return -1;
}

DelinkedList *DelinkedListSlice(DelinkedList *const restrict list,
                                const unsigned int start,
                                const unsigned int size) {
    DelinkedList *slice = NULL;
    DelinkedListNode *node = NULL;
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (start + size > list->Size) {
        errno = EDOM;
        return NULL;
    }

    slice = DelinkedListNew(list->elementSize, list->compare);
    if (slice == NULL) return NULL;
    node = list->head;
    for (unsigned int i = 0; i < start; i++) {
        node = node->next;
    }
    for (unsigned int i = 0; i < size; i++) {
        if (DelinkedListPushBack(slice, node->value) == -1) {
            DelinkedListDelete(&slice);
            return NULL;
        }
        node = node->next;
    }
    return slice;
}
