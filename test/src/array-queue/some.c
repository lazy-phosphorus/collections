#include <stdio.h>

#include "common.h"

static Bool test(const void *value) {
    Test *temp = (Test *)value;
    return temp->a == 0;
}

int main() {
    ArrayQueue *queue = ArrayQueueNew(10, sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayQueuePush(queue, &test);
    }
    if (ArrayQueueSome(queue, test) != TRUE) error(&queue, 0);
    ArrayQueueDelete(&queue);
    return 0;
}
