#include "common.h"

static Bool test(const void *value) {
    Test *temp = (Test *)value;
    return temp->a == 0;
}

int main() {
    PriorityQueue *queue = PriorityQueueNew(10, sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        PriorityQueuePush(queue, i, &test);
    }
    if (PriorityQueueSome(queue, test) != TRUE) error(&queue, 0);
    PriorityQueueDelete(&queue);
    return 0;
}
