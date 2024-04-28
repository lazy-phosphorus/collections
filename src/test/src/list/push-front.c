#include "common.h"

int main() {
    List *list = ListNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ListPushFront(list, &test);
    }
    for (unsigned int i = 0; i < list->Size; i++) {
        Test *temp = (Test *)ListGet(list, i);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&list, i);
    }
    ListDelete(&list);
    return 0;
}