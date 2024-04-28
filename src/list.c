#include "list.h"

#include <errno.h>
#include <malloc.h>
#include <memory.h>

int ListNodeConstruct(ListNode *const node, const void *const restrict value,
                      unsigned long elementSize) {
    if (node == NULL) {
        errno = EINVAL;
        return -1;
    }
    node->value = malloc(elementSize);
    if (node->value == NULL) return -1;
    memcpy(node->value, value, elementSize);
    node->next = NULL;
    return 0;
}

ListNode *ListNodeNew(const void *const restrict value,
                      unsigned long elementSize) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) return NULL;
    if (ListNodeConstruct(node, value, elementSize) == -1) {
        free(node);
        return NULL;
    }
    return node;
}

void ListNodeDestruct(ListNode *const node) {
    if (node == NULL) return;
    free(node->value);
}

void ListNodeDelete(ListNode **const node) {
    if (node == NULL) return;
    ListNodeDestruct(*node);
    free(*node);
    *node = NULL;
}

int ListConstruct(List *const restrict list, const unsigned long elementSize,
                  CompareFunction *const compare) {
    if (list == NULL || compare == NULL) {
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

List *ListNew(const unsigned long elementSize, CompareFunction *const compare) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) return NULL;
    if (ListConstruct(list, elementSize, compare) == -1) {
        free(list);
        return NULL;
    }
    return list;
}

void ListDestruct(List *const restrict list) {
    ListNode *node = NULL, *temp = NULL;
    if (list == NULL) return;

    node = list->head;
    while (node != NULL) {
        temp = node->next;
        ListNodeDelete(&node);
        node = temp;
    }
}

void ListDelete(List **const restrict list) {
    if (list == NULL) return;

    ListDestruct(*list);
    free(*list);
    *list = NULL;
}

void *ListGet(const List *const restrict list, const unsigned int index) {
    ListNode *node = NULL;
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

int ListSet(List *const restrict list, const unsigned int index,
            const void *const restrict value) {
    ListNode *node = NULL;
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

void *ListBack(List *const restrict list) {
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (list->Size == 0) return NULL;
    return list->tail->value;
}

void *ListFront(List *const restrict list) {
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (list->Size == 0) return NULL;
    return list->head->value;
}

int ListPushBack(List *const restrict list, const void *const restrict value) {
    ListNode *node = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    node = ListNodeNew(value, list->elementSize);
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

int ListPopBack(List *const restrict list) {
    ListNode *node = NULL;
    if (list == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (list->Size == 0) return 0;
    if (list->Size == 1) {
        ListNodeDelete(&list->tail);
        list->head = NULL;
        list->tail = NULL;
        list->Size = 0;
        return 0;
    }

    node = list->head;
    while (node->next != list->tail) {
        node = node->next;
    }
    ListNodeDelete(&list->tail);
    list->tail = node;
    list->Size--;
    return 0;
}

int ListPushFront(List *const restrict list, const void *const restrict value) {
    ListNode *node = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    node = ListNodeNew(value, list->elementSize);
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

int ListPopFront(List *const restrict list) {
    ListNode *node = NULL;
    if (list == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (list->Size == 0) return 0;

    node = list->head;
    list->head = node->next;
    ListNodeDelete(&node);
    if (list->Size == 1) list->tail = NULL;
    list->Size--;
    return 0;
}

int ListInsert(List *const restrict list, const unsigned index,
               const void *const restrict value) {
    ListNode *node = NULL, *temp = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (index > list->Size) {
        errno = EDOM;
        return -1;
    }

    if (index == 0)
        return ListPushFront(list, value);
    else if (index == list->Size)
        return ListPushBack(list, value);
    else {
        node = ListNodeNew(value, list->elementSize);
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

int ListFind(List *const restrict list, const void *const restrict value) {
    ListNode *node = NULL;
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
