#include <stdio.h>

#include "common.h"
#include "linked-queue.h"

int main() {
    LinkedQueue *queue = LinkedQueueNew(sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        LinkedQueuePush(queue, &test);
    }
    for (unsigned int i = 0; i < 25; i++) {
        Test *temp = (Test *)LinkedQueueFront(queue);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&queue, i);
        LinkedQueuePop(queue);
    }
    LinkedQueueDelete(&queue);
    return 0;
}
