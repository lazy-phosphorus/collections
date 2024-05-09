#include "common.h"

int main() {
    PriorityQueue *queue = PriorityQueueNew(10, sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        PriorityQueuePush(queue, i, &test);
    }
    PriorityQueueIterator iterator = PriorityQueueGetIterator(queue);
    for (unsigned int i = 0; i < queue->Size; i++) {
        Test *temp = (Test *)PriorityQueueIteratorGetValue(iterator);
        if (temp->a > 24 || temp->b > 25 || temp->c > 26) error(&queue, i);
        iterator = PriorityQueueIteratorNext(iterator);
    }
    iterator = PriorityQueueGetReverseIterator(queue);
    for (unsigned int i = 0; i < queue->Size; i++) {
        Test *temp = (Test *)PriorityQueueIteratorGetValue(iterator);
        if (temp->a > 24 || temp->b > 25 || temp->c > 26) error(&queue, i);
        iterator = PriorityQueueIteratorPrevious(iterator);
    }
    PriorityQueueDelete(&queue);
    return 0;
}
