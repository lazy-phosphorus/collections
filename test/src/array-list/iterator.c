#include "common.h"

int main() {
    ArrayList *list = ArrayListNew(10, sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayListPushBack(list, &test);
    }
    ArrayListIterator iterator = ArrayListGetIterator(list);
    for (unsigned int i = 0; i < list->Size; i++) {
        Test *temp = (Test *)ArrayListIteratorGetValue(iterator);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&list, i);
        iterator = ArrayListIteratorNext(iterator);
    }
    iterator = ArrayListGetReverseIterator(list);
    for (unsigned int i = 0; i < list->Size; i++) {
        Test *temp = (Test *)ArrayListIteratorGetValue(iterator);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&list, i);
        iterator = ArrayListIteratorPrevious(iterator);
    }
    ArrayListDelete(&list);
    return 0;
}
