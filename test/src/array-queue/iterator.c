#include "common.h"

int main() {
    ArrayQueue *queue = ArrayQueueNew(10, sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayQueuePush(queue, &test);
    }
    ArrayQueueIterator iterator = ArrayQueueGetIterator(queue);
    for (unsigned int i = 0; i < queue->Size; i++) {
        Test *temp = (Test *)ArrayQueueIteratorGetValue(iterator);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&queue, i);
        iterator = ArrayQueueIteratorNext(iterator);
    }
    iterator = ArrayQueueGetReverseIterator(queue);
    for (unsigned int i = 0; i < queue->Size; i++) {
        Test *temp = (Test *)ArrayQueueIteratorGetValue(iterator);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&queue, i);
        iterator = ArrayQueueIteratorPrevious(iterator);
    }
    ArrayQueueDelete(&queue);
    return 0;
}
