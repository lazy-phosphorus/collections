#include "common.h"

int main() {
    Delist *list = DelistNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        DelistPushBack(list, &test);
    }
    for (unsigned int i = 0; i < list->Size; i++) {
        Test temp = {i, i + 1, i + 2};
        if (DelistFind(list, &temp) != i) error(&list, i);
    }
    DelistDelete(&list);
    return 0;
}