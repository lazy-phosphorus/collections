#include "common.h"

int main() {
    DelinkedList *list = DelinkedListNew(sizeof(Test), compare), *slice = NULL;
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        DelinkedListPushBack(list, &test);
    }
    slice = DelinkedListSlice(list, 10, list->Size - 10);
    for (unsigned int i = 0; i < slice->Size; i++) {
        Test *temp = (Test *)DelinkedListGet(slice, i);
        if (temp->a != i + 10 || temp->b != i + 11 || temp->c != i + 12) {
            DelinkedListDelete(&list);
            error(&slice, i);
        }
    }
    DelinkedListDelete(&slice);
    DelinkedListDelete(&list);
    return 0;
}
