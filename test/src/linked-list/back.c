#include "common.h"

int main() {
    LinkedList* list = LinkedListNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        LinkedListPushBack(list, &test);
    }
    for (int i = 0; i < 25; i++) {
        Test* temp = (Test*)LinkedListBack(list);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&list, i);
        LinkedListPopBack(list);
    }
    LinkedListDelete(&list);
    return 0;
}
