#include "common.h"

int main() {
    Delist* list = DelistNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        DelistPushBack(list, &test);
    }
    for (int i = 0; i < 25; i++) {
        Test* temp = (Test*)DelistBack(list);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&list, i);
        DelistPopBack(list);
    }
    DelistDelete(&list);
    return 0;
}