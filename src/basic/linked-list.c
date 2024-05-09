#include "linked-list.h"

#include <assert.h>
#include <malloc.h>
#include <memory.h>

void LinkedListNodeConstruct(LinkedListNode *const node,
                             const void *const restrict value,
                             unsigned long elementSize) {
    assert(node != NULL);
    assert(value != NULL);
    assert(elementSize > 0);
    node->value = malloc(elementSize);
    assert(node->value != NULL);
    memcpy(node->value, value, elementSize);
    node->next = NULL;
}

LinkedListNode *LinkedListNodeNew(const void *const restrict value,
                                  unsigned long elementSize) {
    LinkedListNode *node = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    LinkedListNodeConstruct(node, value, elementSize);
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

void LinkedListConstruct(LinkedList *const restrict list,
                         const unsigned long elementSize,
                         CompareFunction *const compare) {
    assert(list != NULL);
    assert(compare != NULL);
    assert(elementSize > 0);

    list->head = NULL;
    list->tail = NULL;
    list->elementSize = elementSize;
    list->compare = compare;
    list->Size = 0;
}

LinkedList *LinkedListNew(const unsigned long elementSize,
                          CompareFunction *const compare) {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    LinkedListConstruct(list, elementSize, compare);
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
    assert(list != NULL);
    assert(index < list->Size);
    LinkedListNode *node = list->head;
    for (unsigned int i = 0; i < index; i++) {
        node = node->next;
    }
    return node->value;
}

void LinkedListSet(LinkedList *const restrict list, const unsigned int index,
                   const void *const restrict value) {
    assert(list != NULL);
    assert(value != NULL);
    assert(index < list->Size);
    LinkedListNode *node = list->head;
    for (unsigned int i = 0; i < index; i++) {
        node = node->next;
    }
    memcpy(node->value, value, list->elementSize);
}

void *LinkedListBack(LinkedList *const restrict list) {
    assert(list != NULL);
    if (list->Size == 0) return NULL;
    return list->tail->value;
}

void *LinkedListFront(LinkedList *const restrict list) {
    assert(list != NULL);
    if (list->Size == 0) return NULL;
    return list->head->value;
}

void LinkedListPushBack(LinkedList *const restrict list,
                        const void *const restrict value) {
    assert(list != NULL);
    assert(value != NULL);
    LinkedListNode *node = LinkedListNodeNew(value, list->elementSize);
    if (list->Size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->Size++;
}

void LinkedListPopBack(LinkedList *const restrict list) {
    assert(list != NULL);
    assert(list->Size > 0);
    LinkedListNode *node = NULL;
    if (list->Size == 1) {
        LinkedListNodeDelete(&list->tail);
        list->head = NULL;
        list->tail = NULL;
        list->Size = 0;
        return;
    }

    node = list->head;
    while (node->next != list->tail) {
        node = node->next;
    }
    LinkedListNodeDelete(&list->tail);
    list->tail = node;
    list->Size--;
}

void LinkedListPushFront(LinkedList *const restrict list,
                         const void *const restrict value) {
    assert(list != NULL);
    assert(value != NULL);
    LinkedListNode *node = LinkedListNodeNew(value, list->elementSize);
    if (list->Size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head = node;
    }
    list->Size++;
}

void LinkedListPopFront(LinkedList *const restrict list) {
    assert(list != NULL);
    assert(list->Size > 0);
    LinkedListNode *node = list->head;
    list->head = node->next;
    LinkedListNodeDelete(&node);
    if (list->Size == 1) list->tail = NULL;
    list->Size--;
}

void LinkedListInsert(LinkedList *const restrict list, const unsigned index,
                      const void *const restrict value) {
    assert(list != NULL);
    assert(value != NULL);
    assert(index <= list->Size);
    LinkedListNode *node = NULL, *temp = NULL;
    if (index == 0)
        LinkedListPushFront(list, value);
    else if (index == list->Size)
        LinkedListPushBack(list, value);
    else {
        node = LinkedListNodeNew(value, list->elementSize);
        temp = list->head;
        for (unsigned int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
        list->Size++;
    }
}

int LinkedListFind(LinkedList *const restrict list,
                   const void *const restrict value) {
    assert(list != NULL);
    assert(value != NULL);
    LinkedListNode *node = list->head;
    for (int i = 0; i < list->Size; i++) {
        if (list->compare(node->value, value) == 0) return i;
        node = node->next;
    }
    return -1;
}

LinkedList *LinkedListSlice(LinkedList *const restrict list,
                            const unsigned int start, const unsigned int size) {
    assert(list != NULL);
    assert(start < list->Size);
    assert(size > 0);
    LinkedList *slice = LinkedListNew(list->elementSize, list->compare);
    LinkedListNode *node = list->head;
    for (unsigned int i = 0; i < start; i++) {
        node = node->next;
    }
    for (unsigned int i = 0; i < size; i++) {
        LinkedListPushBack(slice, node->value);
        node = node->next;
    }
    return slice;
}

LinkedListIterator LinkedListGetIterator(LinkedList *const restrict list) {
    assert(list != NULL);
    return list->head;
}

LinkedListIterator LinkedListIteratorNext(
    LinkedListIterator const restrict iterator) {
    assert(iterator != NULL);
    return iterator->next;
}

void *LinkedListIteratorGetValue(LinkedListIterator const restrict iterator) {
    assert(iterator != NULL);
    return iterator->value;
}

Bool LinkedListIteratorEnded(LinkedListIterator const restrict iterator) {
    return iterator == NULL;
}
