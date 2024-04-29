#include "common.h"

int main() {
    List* list = ListNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ListPushBack(list, &test);
    }
    for (int i = 0; i < 25; i++) {
        Test* temp = (Test*)ListFront(list);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&list, 0);
        ListPopFront(list);
    }
    ListDelete(&list);
    return 0;
}