#include "common.h"

int main() {
    DelinkedList *list = DelinkedListNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        DelinkedListPushBack(list, &test);
    }
    DelinkedListIterator iterator = DelinkedListGetIterator(list);
    for (unsigned int i = 0; i < list->Size; i++) {
        Test *temp = (Test *)DelinkedListIteratorGetValue(iterator);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&list, i);
        iterator = DelinkedListIteratorNext(iterator);
    }
    iterator = DelinkedListGetReverseIterator(list);
    for (unsigned int i = 0; i < list->Size; i++) {
        Test *temp = (Test *)DelinkedListIteratorGetValue(iterator);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&list, i);
        iterator = DelinkedListIteratorPrevious(iterator);
    }
    DelinkedListDelete(&list);
    return 0;
}
