#include "common.h"

int main() {
    DelinkedList* list = DelinkedListNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        DelinkedListPushBack(list, &test);
    }
    for (int i = 0; i < 25; i++) {
        Test* temp = (Test*)DelinkedListBack(list);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&list, i);
        DelinkedListPopBack(list);
    }
    DelinkedListDelete(&list);
    return 0;
}
