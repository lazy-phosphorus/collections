#include "common.h"

int main() {
    DelinkedList *list = DelinkedListNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        DelinkedListPushBack(list, &test);
    }
    for (unsigned int i = 0; i < list->Size; i++) {
        Test temp = {i, i + 1, i + 2};
        if (DelinkedListFind(list, &temp) != i) error(&list, i);
    }
    DelinkedListDelete(&list);
    return 0;
}
