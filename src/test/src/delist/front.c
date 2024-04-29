#include "common.h"

int main() {
    Delist* list = DelistNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        DelistPushBack(list, &test);
    }
    for (int i = 0; i < 25; i++) {
        Test* temp = (Test*)DelistFront(list);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&list, 0);
        DelistPopFront(list);
    }
    DelistDelete(&list);
    return 0;
}