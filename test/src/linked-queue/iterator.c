#include "common.h"

int main() {
    LinkedQueue *queue = LinkedQueueNew(sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        LinkedQueuePush(queue, &test);
    }
    LinkedQueueIterator iterator = LinkedQueueGetIterator(queue);
    for (unsigned int i = 0; i < queue->Size; i++) {
        Test *temp = (Test *)LinkedQueueIteratorGetValue(iterator);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&queue, i);
        iterator = LinkedQueueIteratorNext(iterator);
    }
    LinkedQueueDelete(&queue);
    return 0;
}
