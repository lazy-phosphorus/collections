#include "common.h"

int main() {
    List *list = ListNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ListPushBack(list, &test);
    }
    for (unsigned int i = 0; i < list->Size; i++) {
        Test temp = {i, i + 1, i + 2};
        if (ListFind(list, &temp) != i) error(&list, i);
    }
    ListDelete(&list);
    return 0;
}