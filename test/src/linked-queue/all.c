#include "common.h"

static Bool test(const void *value) {
    Test *test = (Test *)value;
    return test->a > 0;
}

int main() {
    LinkedQueue *queue = LinkedQueueNew(sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        LinkedQueuePush(queue, &test);
    }
    if (LinkedQueueAll(queue, test) != FALSE) error(&queue, 0);
    LinkedQueueDelete(&queue);
    return 0;
}
