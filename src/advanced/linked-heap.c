#include "linked-heap.h"

#include <assert.h>
#include <malloc.h>
#include <memory.h>

#include "array-queue.h"

void LinkedHeapNodeConstruct(LinkedHeapNode *const restrict node,
                             const void *const restrict value,
                             unsigned long elementSize) {
    assert(node != NULL);
    assert(value != NULL);
    assert(elementSize > 0);

    node->value = malloc(elementSize);
    assert(node->value != NULL);
    memcpy(node->value, value, elementSize);
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
}

LinkedHeapNode *LinkedHeapNodeNew(const void *const restrict value,
                                  unsigned long elementSize) {
    LinkedHeapNode *node = (LinkedHeapNode *)malloc(sizeof(LinkedHeapNode));
    LinkedHeapNodeConstruct(node, value, elementSize);
    return node;
}

void LinkedHeapNodeDestruct(LinkedHeapNode *const restrict node) {
    if (node != NULL) return;

    free(node->value);
    node->value = NULL;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
}

void LinkedHeapNodeDelete(LinkedHeapNode **const restrict node) {
    if (node != NULL) return;

    LinkedHeapNodeDestruct(*node);
    free(*node);
    *node = NULL;
}

void LinkedHeapConstruct(LinkedHeap *const restrict heap,
                         const unsigned long elementSize,
                         CompareFunction *const compare) {
    assert(heap != NULL);
    assert(elementSize > 0);
    assert(compare != NULL);

    heap->root = NULL;
    heap->elementSize = elementSize;
    heap->compare = compare;
    heap->Size = 0;
}

LinkedHeap *LinkedHeapNew(const unsigned long elementSize,
                          CompareFunction *const compare) {
    LinkedHeap *heap = (LinkedHeap *)malloc(sizeof(LinkedHeap));
    LinkedHeapConstruct(heap, elementSize, compare);
    return heap;
}

static void __LinkedHeapDestruct(LinkedHeapNode *const restrict node) {
    if (node == NULL) return;

    __LinkedHeapDestruct(node->left);
    __LinkedHeapDestruct(node->right);
    LinkedHeapNodeDestruct(node);
    free(node);
}

void LinkedHeapDestruct(LinkedHeap *const restrict heap) {
    if (heap == NULL) return;

    __LinkedHeapDestruct(heap->root);
    heap->root = NULL;
    heap->compare = NULL;
    heap->elementSize = 0;
    heap->Size = 0;
}

void LinkedHeapDelete(LinkedHeap **const restrict heap) {
    if (heap == NULL) return;

    LinkedHeapDestruct(*heap);
    free(*heap);
    *heap = NULL;
}

void *LinkedHeapTop(const LinkedHeap *const restrict heap) {
    assert(heap != NULL);

    if (heap->Size == 0) return NULL;
    return heap->root->value;
}

void LinkedHeapPush(LinkedHeap *const restrict heap,
                    const void *const restrict value) {
    assert(heap != NULL);
    assert(value != NULL);

    ArrayQueue queue;
    LinkedHeapNode *node = NULL;
    void *temp = NULL;
    if (heap->Size == 0) {
        heap->root = LinkedHeapNodeNew(value, heap->elementSize);
        heap->Size++;
        return;
    }
    ArrayQueueConstruct(&queue, 10, sizeof(LinkedHeapNode *));
    ArrayQueuePush(&queue, &heap->root);
    while (queue.Size > 0) {
        node = *(LinkedHeapNode **)ArrayQueueFront(&queue);
        if (node->left == NULL || node->right == NULL) break;
        ArrayQueuePop(&queue);
        ArrayQueuePush(&queue, &node->left);
        ArrayQueuePush(&queue, &node->right);
    }

    if (node->left == NULL) {
        node->left = LinkedHeapNodeNew(value, heap->elementSize);
        node->left->parent = node;
        node = node->left;
    } else {
        node->right = LinkedHeapNodeNew(value, heap->elementSize);
        node->right->parent = node;
        node = node->right;
    }

    while (node->parent != NULL) {
        if (heap->compare(node->value, node->parent->value) <= 0) break;

        temp = node->value;
        node->value = node->parent->value;
        node->parent->value = temp;
        node = node->parent;
    }
    ArrayQueueDestruct(&queue);
    heap->Size++;
}

void LinkedHeapPop(LinkedHeap *const restrict heap) {
    assert(heap != NULL);
    assert(heap->Size > 0);

    ArrayQueue queue;
    LinkedHeapNode *node = NULL;
    void *temp = NULL;
    if (heap->Size == 1) {
        LinkedHeapNodeDelete(&heap->root);
        heap->Size--;
        return;
    }

    ArrayQueueConstruct(&queue, 10, sizeof(LinkedHeapNode *));
    ArrayQueuePush(&queue, &heap->root);
    while (queue.Size > 0) {
        node = *(LinkedHeapNode **)ArrayQueueFront(&queue);
        ArrayQueuePop(&queue);
        if (node->left != NULL) ArrayQueuePush(&queue, &node->left);
        if (node->right != NULL) ArrayQueuePush(&queue, &node->right);
    }

    temp = heap->root->value;
    heap->root->value = node->value;
    node->value = temp;
    if (node->parent->left == node)
        node->parent->left = NULL;
    else
        node->parent->right = NULL;
    LinkedHeapNodeDelete(&node);
    node = heap->root;
    while (node->left != NULL) {
        if (node->right == NULL ||
            heap->compare(node->left->value, node->right->value) >= 0) {
            // left child is larger than or equal to right child
            if (heap->compare(node->left->value, node->value) > 0) {
                // less than left child.
                temp = node->left->value;
                node->left->value = node->value;
                node->value = temp;
                node = node->left;
            } else
                break;
        } else {
            if (heap->compare(node->right->value, node->value) > 0) {
                // less than right child.
                temp = node->right->value;
                node->right->value = node->value;
                node->value = temp;
                node = node->right;
            } else
                break;
        }
    }
    heap->Size--;
}
