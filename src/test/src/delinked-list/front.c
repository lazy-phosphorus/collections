#include "common.h"

int main() {
    DelinkedList* list = DelinkedListNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        DelinkedListPushBack(list, &test);
    }
    for (int i = 0; i < 25; i++) {
        Test* temp = (Test*)DelinkedListFront(list);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&list, 0);
        DelinkedListPopFront(list);
    }
    DelinkedListDelete(&list);
    return 0;
}
