#include "common.h"

int main() {
    List* list = ListNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ListPushBack(list, &test);
    }
    for (int i = 0; i < 25; i++) {
        Test* temp = (Test*)ListBack(list);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&list, i);
        ListPopBack(list);
    }
    ListDelete(&list);
}