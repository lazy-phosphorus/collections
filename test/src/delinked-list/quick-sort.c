#include "common.h"

int main() {
    DelinkedList *list = DelinkedListNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        DelinkedListInsert(list, list->Size / 2, &test);
    }
    DelinkedListQuickSort(list);
    for (unsigned int i = 0; i < list->Size; i += 1) {
        Test *temp = (Test *)DelinkedListGet(list, i);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&list, i);
    }
    DelinkedListDelete(&list);
    return 0;
}