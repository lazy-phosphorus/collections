#include "common.h"

int main() {
    LinkedList *list = LinkedListNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        LinkedListPushBack(list, &test);
    }
    for (unsigned int i = 0; i < 25; i++) {
        Test test = *(Test *)LinkedListGet(list, i);
        test.a *= 2;
        test.b *= 2;
        test.c *= 2;
        LinkedListSet(list, i, &test);
    }
    for (unsigned int i = 0; i < list->Size; i++) {
        Test *temp = (Test *)LinkedListGet(list, i);
        if (temp->a != i * 2 || temp->b != (i + 1) * 2 ||
            temp->c != (i + 2) * 2)
            error(&list, i);
    }
    LinkedListDelete(&list);
    return 0;
}
