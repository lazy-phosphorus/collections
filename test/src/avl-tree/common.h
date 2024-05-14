#ifndef __LINKED_QUEUE_TEST__
#define __LINKED_QUEUE_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "array-queue.h"
#include "avl-tree.h"
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
            Test *test = (Test *)temp->value;
            printf("[%d,%u] ", test->a, temp->height);
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
    Test *temp = (Test *)node->value;
    printf("{ %d, %d, %d }\n", temp->a, temp->b, temp->c);
    travel(node->right);
}

int error(AvlTree **const restrict tree, const unsigned int i) {
    printf("Error at %d\nTree:", i);
    levelorder(*tree);
    travel((*tree)->root);
    AvlTreeDelete(tree);
    exit(-1);
}

#endif  // __LINKED_QUEUE_TEST__
