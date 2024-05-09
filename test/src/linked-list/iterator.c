#include "common.h"

int main() {
    LinkedList *list = LinkedListNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        LinkedListPushBack(list, &test);
    }
    LinkedListIterator iterator = LinkedListGetIterator(list);
    for (unsigned int i = 0; i < list->Size; i++) {
        Test *temp = (Test *)LinkedListIteratorGetValue(iterator);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&list, i);
        iterator = LinkedListIteratorNext(iterator);
    }
    LinkedListDelete(&list);
    return 0;
}
