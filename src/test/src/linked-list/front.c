#include "common.h"

int main() {
    LinkedList* list = LinkedListNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        LinkedListPushBack(list, &test);
    }
    for (int i = 0; i < 25; i++) {
        Test* temp = (Test*)LinkedListFront(list);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&list, 0);
        LinkedListPopFront(list);
    }
    LinkedListDelete(&list);
    return 0;
}
