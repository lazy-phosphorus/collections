#include "delist.h"

#include <errno.h>
#include <malloc.h>
#include <memory.h>

int DelistNodeConstruct(DelistNode *const node,
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

DelistNode *DelistNodeNew(const void *const restrict value,
                          unsigned long elementSize) {
    DelistNode *node = (DelistNode *)malloc(sizeof(DelistNode));
    if (node == NULL) return NULL;
    if (DelistNodeConstruct(node, value, elementSize) == -1) {
        free(node);
        return NULL;
    }
    return node;
}

void DelistNodeDestruct(DelistNode *const node) {
    if (node == NULL) return;
    free(node->value);
}

void DelistNodeDelete(DelistNode **const node) {
    if (node == NULL) return;
    DelistNodeDestruct(*node);
    free(*node);
    *node = NULL;
}

int DelistConstruct(Delist *const restrict list,
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

Delist *DelistNew(const unsigned long elementSize,
                  CompareFunction *const compare) {
    Delist *list = (Delist *)malloc(sizeof(Delist));
    if (list == NULL) return NULL;
    if (DelistConstruct(list, elementSize, compare) == -1) {
        free(list);
        return NULL;
    }
    return list;
}

void DelistDestruct(Delist *const restrict list) {
    DelistNode *node = NULL, *temp = NULL;
    if (list == NULL) return;

    node = list->head;
    while (node != NULL) {
        temp = node->next;
        DelistNodeDelete(&node);
        node = temp;
    }
}

void DelistDelete(Delist **const restrict list) {
    if (list == NULL) return;

    DelistDestruct(*list);
    free(*list);
    *list = NULL;
}

void *DelistGet(const Delist *const restrict list, const unsigned int index) {
    DelistNode *node = NULL;
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

int DelistSet(Delist *const restrict list, const unsigned int index,
              const void *const restrict value) {
    DelistNode *node = NULL;
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

void *DelistBack(Delist *const restrict list) {
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (list->Size == 0) return NULL;
    return list->tail->value;
}

void *DelistFront(Delist *const restrict list) {
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (list->Size == 0) return NULL;
    return list->head->value;
}

int DelistPushBack(Delist *const restrict list,
                   const void *const restrict value) {
    DelistNode *node = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    node = DelistNodeNew(value, list->elementSize);
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

int DelistPopBack(Delist *const restrict list) {
    DelistNode *node = NULL;
    if (list == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (list->Size == 0) return 0;
    if (list->Size == 1) {
        DelistNodeDelete(&list->tail);
        list->head = NULL;
        list->tail = NULL;
        list->Size = 0;
        return 0;
    }

    node = list->tail;
    list->tail = node->previous;
    list->tail->next = NULL;
    DelistNodeDelete(&node);
    list->Size--;
    return 0;
}

int DelistPushFront(Delist *const restrict list,
                    const void *const restrict value) {
    DelistNode *node = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    node = DelistNodeNew(value, list->elementSize);
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

int DelistPopFront(Delist *const restrict list) {
    DelistNode *node = NULL;
    if (list == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (list->Size == 0) return 0;
    if (list->Size == 1) {
        DelistNodeDelete(&list->head);
        list->head = NULL;
        list->tail = NULL;
        list->Size = 0;
        return 0;
    }

    node = list->head;
    list->head = node->next;
    list->head->previous = NULL;
    DelistNodeDelete(&node);
    list->Size--;
    return 0;
}

int DelistInsert(Delist *const restrict list, const unsigned index,
                 const void *const restrict value) {
    DelistNode *node = NULL, *temp = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (index > list->Size) {
        errno = EDOM;
        return -1;
    }

    if (index == 0)
        return DelistPushFront(list, value);
    else if (index == list->Size)
        return DelistPushBack(list, value);
    else {
        node = DelistNodeNew(value, list->elementSize);
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

int DelistFind(Delist *const restrict list, const void *const restrict value) {
    DelistNode *node = NULL;
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
