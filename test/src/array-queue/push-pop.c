#include <stdio.h>

#include "common.h"

int main() {
    ArrayQueue *queue = ArrayQueueNew(10, sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayQueuePush(queue, &test);
    }
    for (unsigned int i = 0; i < 25; i++) {
        Test *temp = (Test *)ArrayQueueFront(queue);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&queue, i);
        ArrayQueuePop(queue);
    }
    ArrayQueueDelete(&queue);
    return 0;
}
