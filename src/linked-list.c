#include "linked-list.h"

#include <errno.h>
#include <malloc.h>
#include <memory.h>

int LinkedListNodeConstruct(LinkedListNode *const node,
                            const void *const restrict value,
                            unsigned long elementSize) {
    if (node == NULL || value == NULL || elementSize == 0) {
        errno = EINVAL;
        return -1;
    }
    node->value = malloc(elementSize);
    if (node->value == NULL) return -1;
    memcpy(node->value, value, elementSize);
    node->next = NULL;
    return 0;
}

LinkedListNode *LinkedListNodeNew(const void *const restrict value,
                                  unsigned long elementSize) {
    LinkedListNode *node = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    if (node == NULL) return NULL;
    if (LinkedListNodeConstruct(node, value, elementSize) == -1) {
        free(node);
        return NULL;
    }
    return node;
}

void LinkedListNodeDestruct(LinkedListNode *const node) {
    if (node == NULL) return;
    free(node->value);
    node->value = NULL;
    node->next = NULL;
}

void LinkedListNodeDelete(LinkedListNode **const node) {
    if (node == NULL) return;
    LinkedListNodeDestruct(*node);
    free(*node);
    *node = NULL;
}

int LinkedListConstruct(LinkedList *const restrict list,
                        const unsigned long elementSize,
                        CompareFunction *const compare) {
    if (list == NULL || compare == NULL || elementSize == 0) {
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

LinkedList *LinkedListNew(const unsigned long elementSize,
                          CompareFunction *const compare) {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL) return NULL;
    if (LinkedListConstruct(list, elementSize, compare) == -1) {
        free(list);
        return NULL;
    }
    return list;
}

void LinkedListDestruct(LinkedList *const restrict list) {
    LinkedListNode *node = NULL, *temp = NULL;
    if (list == NULL) return;

    node = list->head;
    while (node != NULL) {
        temp = node->next;
        LinkedListNodeDelete(&node);
        node = temp;
    }
    list->compare = NULL;
    list->elementSize = 0;
    list->Size = 0;
    list->head = NULL;
    list->tail = NULL;
}

void LinkedListDelete(LinkedList **const restrict list) {
    if (list == NULL) return;

    LinkedListDestruct(*list);
    free(*list);
    *list = NULL;
}

void *LinkedListGet(const LinkedList *const restrict list,
                    const unsigned int index) {
    LinkedListNode *node = NULL;
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

int LinkedListSet(LinkedList *const restrict list, const unsigned int index,
                  const void *const restrict value) {
    LinkedListNode *node = NULL;
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

void *LinkedListBack(LinkedList *const restrict list) {
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (list->Size == 0) return NULL;
    return list->tail->value;
}

void *LinkedListFront(LinkedList *const restrict list) {
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (list->Size == 0) return NULL;
    return list->head->value;
}

int LinkedListPushBack(LinkedList *const restrict list,
                       const void *const restrict value) {
    LinkedListNode *node = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    node = LinkedListNodeNew(value, list->elementSize);
    if (node == NULL) return -1;
    if (list->Size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->Size++;
    return 0;
}

int LinkedListPopBack(LinkedList *const restrict list) {
    LinkedListNode *node = NULL;
    if (list == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (list->Size == 0) return 0;
    if (list->Size == 1) {
        LinkedListNodeDelete(&list->tail);
        list->head = NULL;
        list->tail = NULL;
        list->Size = 0;
        return 0;
    }

    node = list->head;
    while (node->next != list->tail) {
        node = node->next;
    }
    LinkedListNodeDelete(&list->tail);
    list->tail = node;
    list->Size--;
    return 0;
}

int LinkedListPushFront(LinkedList *const restrict list,
                        const void *const restrict value) {
    LinkedListNode *node = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    node = LinkedListNodeNew(value, list->elementSize);
    if (node == NULL) return -1;
    if (list->Size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head = node;
    }
    list->Size++;
    return 0;
}

int LinkedListPopFront(LinkedList *const restrict list) {
    LinkedListNode *node = NULL;
    if (list == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (list->Size == 0) return 0;

    node = list->head;
    list->head = node->next;
    LinkedListNodeDelete(&node);
    if (list->Size == 1) list->tail = NULL;
    list->Size--;
    return 0;
}

int LinkedListInsert(LinkedList *const restrict list, const unsigned index,
                     const void *const restrict value) {
    LinkedListNode *node = NULL, *temp = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (index > list->Size) {
        errno = EDOM;
        return -1;
    }

    if (index == 0)
        return LinkedListPushFront(list, value);
    else if (index == list->Size)
        return LinkedListPushBack(list, value);
    else {
        node = LinkedListNodeNew(value, list->elementSize);
        if (node == NULL) return -1;
        temp = list->head;
        for (unsigned int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
        list->Size++;
        return 0;
    }
}

int LinkedListFind(LinkedList *const restrict list,
                   const void *const restrict value) {
    LinkedListNode *node = NULL;
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
