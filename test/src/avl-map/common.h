#ifndef __LINKED_QUEUE_TEST__
#define __LINKED_QUEUE_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "array-queue.h"
#include "avl-map.h"
#include "test.h"

static void levelorder(AvlTree *const restrict tree) {
    ArrayQueue queue;
    AvlTreeNode node;
    node.value = NULL;
    ArrayQueueConstruct(&queue, 10, sizeof(AvlTreeNode));
    ArrayQueuePush(&queue, tree->root);
    ArrayQueuePush(&queue, &node);

    while (queue.Size > 1) {
        AvlTreeNode *temp = (AvlTreeNode *)ArrayQueueFront(&queue);
        if (temp->value != NULL) {
            AvlMapPair *pair = (AvlMapPair *)temp->value;
            Test *test = (Test *)pair->value;
            printf("%d -> { %d, %d, %d }\n", *(int *)pair->key, test->a,
                   test->b, test->c);
            if (temp->left != NULL) ArrayQueuePush(&queue, temp->left);
            if (temp->right != NULL) ArrayQueuePush(&queue, temp->right);
        } else {
            printf("\n");
            ArrayQueuePush(&queue, &node);
        }
        ArrayQueuePop(&queue);
    }
    printf("\n");
}

static void travel(AvlTreeNode *const restrict node) {
    if (node == NULL) return;
    travel(node->left);
    AvlMapPair *pair = (AvlMapPair *)node->value;
    Test *temp = (Test *)pair->value;
    printf("%d -> { %d, %d, %d }\n", *(int *)pair->key, temp->a, temp->b,
           temp->c);
    travel(node->right);
}

int error(AvlMap **const restrict map, const unsigned int i) {
    printf("Error at %d\nTree:", i);
    levelorder((*map)->tree);
    travel((*map)->tree->root);
    AvlMapDelete(map);
    exit(-1);
}

#endif  // __LINKED_QUEUE_TEST__
