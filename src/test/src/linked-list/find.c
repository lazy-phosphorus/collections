#include "common.h"

int main() {
    LinkedList *list = LinkedListNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        LinkedListPushBack(list, &test);
    }
    for (unsigned int i = 0; i < list->Size; i++) {
        Test temp = {i, i + 1, i + 2};
        if (LinkedListFind(list, &temp) != i) error(&list, i);
    }
    LinkedListDelete(&list);
    return 0;
}
