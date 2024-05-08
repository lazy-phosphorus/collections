#include <stdio.h>

#include "common.h"

int main() {
    PriorityQueue *queue = PriorityQueueNew(10, sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        PriorityQueuePush(queue, i, &test);
    }
    for (unsigned int i = 0; i < 25; i++) {
        Test *temp = (Test *)PriorityQueueFront(queue);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&queue, i);
        PriorityQueuePop(queue);
    }
    PriorityQueueDelete(&queue);
    return 0;
}
