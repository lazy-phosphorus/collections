#include <stdio.h>

#include "common.h"

static Bool test(const void *value) {
    Test *temp = (Test *)value;
    return temp->a == 0;
}

int main() {
    LinkedQueue *queue = LinkedQueueNew(sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        LinkedQueuePush(queue, &test);
    }
    if (LinkedQueueSome(queue, test) != TRUE) error(&queue, 0);
    LinkedQueueDelete(&queue);
    return 0;
}
